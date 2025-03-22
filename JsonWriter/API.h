#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>
#include <h3mtxt/JsonWriter/JsonWriterContext.h>

#include <string_view>
#include <type_traits>

namespace Medea_NS
{
  // Class for serializing elements of a JSON array.
  //
  // The class is CopyConstructible and MoveConstructible, but neither CopyAssignable nor MoveAssignable.
  class ScopedArrayWriter
  {
  public:
    explicit constexpr ScopedArrayWriter(Detail_NS::JsonWriterContext& context,
                                         bool one_element_per_line = true) noexcept;

    // Writes a single element.
    template<class T>
    void writeElement(const T& value) const;

    // Writes a comment line.
    inline void writeComment(std::string_view comment) const;

  private:
    Detail_NS::JsonWriterContext& context_;
    bool one_element_per_line_ {};
  };

  // Class for writing fields of a JSON object.
  //
  // The class is CopyConstructible and MoveConstructible, but neither CopyAssignable nor MoveAssignable.
  class ScopedObjectWriter
  {
  public:
    explicit constexpr ScopedObjectWriter(Detail_NS::JsonWriterContext& context) noexcept;

    // Writes a single field.
    template<class T>
    void writeField(std::string_view field_name, const T& value) const;

    // Writes a comment line.
    // \param comment - comment text. Empty comments are ignored.
    // \param newline - if true, the comment will be written on a new line,
    //        otherwise it will be written on the current line.
    inline void writeComment(std::string_view comment, bool newline = true);

  private:
    Detail_NS::JsonWriterContext& context_;
  };

  // ========== IMPLEMENTATION ==========
  namespace Detail_NS
  {
    template<class T, class Enable = void>
    struct OneElementPerLineImpl : std::true_type {};

    // Specialization for types for which JsonArrayWriter<T>
    // has a static data member kOneElementPerLine of type const bool.
    template<class T>
    struct OneElementPerLineImpl<T, std::enable_if_t<std::is_same_v<decltype(JsonArrayWriter<T>::kOneElementPerLine),
                                                                    const bool>>>
      : std::bool_constant<JsonArrayWriter<T>::kOneElementPerLine>
    {};

    // Serializes the given value as JSON.
    // \param context - output JsonWriterContext.
    // \param value - input value.
    template<class T>
    void writeValueRaw(JsonWriterContext& context, const T& value)
    {
      using Traits = JsonWriterTraits<T>;

      if constexpr (Traits::kValueType == JsonValueType::Bool)
      {
        static_assert(std::is_same_v<decltype(Traits::getValue(value)), bool>,
                      "JsonWriterTraits<T>::getValue(value) must return bool.");
        context.writeBool(Traits::getValue(value));
      }
      else if constexpr (Traits::kValueType == JsonValueType::Int)
      {
        static_assert(std::is_integral_v<decltype(Traits::getValue(value))> &&
                      std::is_signed_v<decltype(Traits::getValue(value))>,
                      "JsonWriterTraits<T>::getValue(value) must return a signed integer.");
        context.writeInt(static_cast<std::intmax_t>(Traits::getValue(value)));
      }
      else if constexpr (Traits::kValueType == JsonValueType::UInt)
      {
        static_assert(std::is_integral_v<decltype(Traits::getValue(value))> &&
                      std::is_unsigned_v<decltype(Traits::getValue(value))>,
                      "JsonWriterTraits<T>::getValue(value) must return an unsigned integer.");
        context.writeUInt(static_cast<std::uintmax_t>(Traits::getValue(value)));
      }
      else if constexpr (Traits::kValueType == JsonValueType::String)
      {
        static_assert(std::is_convertible_v<decltype(Traits::getValue(value)), std::string_view>,
                      "JsonWriterTraits<T>::getValue(value) must be convertible to std::string_view.");
        context.writeString(Traits::getValue(value));
      }
      else if constexpr (Traits::kValueType == JsonValueType::Array)
      {
        constexpr bool kOneElementPerLine = OneElementPerLineImpl<T>::value;
        JsonArrayWriter<T> array_writer {};
        ScopedArrayWriter elements_writer{ context, kOneElementPerLine };
        context.beginAggregate('[');
        array_writer(elements_writer, value);
        context.endAggregate(']', kOneElementPerLine);
      }
      else if constexpr (Traits::kValueType == JsonValueType::Object)
      {
        JsonObjectWriter<T> object_writer {};
        ScopedObjectWriter fields_writer{ context };
        context.beginAggregate('{');
        object_writer(fields_writer, value);
        context.endAggregate('}', true);
      }
      else
      {
        static_assert(false, "Invalid JsonWriterTraits<T>::kValueType.");
      }
    }
  }

  constexpr ScopedObjectWriter::ScopedObjectWriter(Detail_NS::JsonWriterContext& context) noexcept :
    context_(context)
  {}

  template<class T>
  void ScopedObjectWriter::writeField(std::string_view field_name, const T& value) const
  {
    context_.beforeWriteValue(true);
    context_.writeFieldName(field_name);
    Detail_NS::writeValueRaw(context_, value);
  }

  void ScopedObjectWriter::writeComment(std::string_view comment, bool newline)
  {
    context_.writeComment(comment, newline);
  }

  constexpr ScopedArrayWriter::ScopedArrayWriter(Detail_NS::JsonWriterContext& context,
                                                 bool one_element_per_line) noexcept:
    context_(context),
    one_element_per_line_(one_element_per_line)
  {}

  template<class T>
  void ScopedArrayWriter::writeElement(const T& value) const
  {
    context_.beforeWriteValue(one_element_per_line_);
    Detail_NS::writeValueRaw(context_, value);
  }

  void ScopedArrayWriter::writeComment(std::string_view comment) const
  {
    context_.writeComment(comment, true);
  }
}
