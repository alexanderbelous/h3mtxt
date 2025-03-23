#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>

#include <cstdint>
#include <iosfwd>
#include <memory>
#include <string>
#include <string_view>
#include <type_traits>

namespace Medea_NS
{
  // Forward declaration of writeJson().
  template<class T>
  void writeJson(std::ostream& stream, const T& value, unsigned int initial_indent);

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

    // Internal class for writing formatted JSON.
    //
    // This class cannot be used directly because only writeJson() has access to the constructor.
    class JsonWriterContext
    {
    public:
      // writeJson() is a friend because it needs to construct JsonWriterContext.
      template<class T>
      friend void ::Medea_NS::writeJson(std::ostream& stream, const T& value, unsigned int initial_indent);

      // Non-copyable, non-movable.
      constexpr JsonWriterContext(const JsonWriterContext&) noexcept = delete;
      constexpr JsonWriterContext(JsonWriterContext&&) noexcept = delete;
      JsonWriterContext& operator=(const JsonWriterContext&) = delete;
      JsonWriterContext& operator=(JsonWriterContext&&) = delete;

      constexpr ~JsonWriterContext() = default;

      // Queues a comment.
      //
      // Comments are not written immediately in order to avoid trailing commas in printing objects/arrays.
      // \param comment - comment to write. Empty comments are ignored.
      // \param newline - if true, the comment will be written on a new line,
      //        otherwise on the same line as the last printed entry.
      //        This parameter is ignored if !comment_.empty() - in that case @comment will be appended to
      //        comment_ after a newline character.
      void writeComment(std::string_view comment, bool newline);

      template<class T>
      void writeValue(const T& value, bool newline);

      template<class T>
      void writeField(std::string_view field_name, const T& value);

    private:
      using ArrayWriterPtr = void(*)(ArrayElementsWriter&, const void*);
      using ObjectWriterPtr = void(*)(FieldsWriter&, const void*);

      explicit constexpr JsonWriterContext(std::ostream& stream, unsigned int initial_indent = 0) noexcept :
        stream_(stream),
        indent_(initial_indent)
      {}

      void beforeWriteValue(bool newline);

      // Writes a boolean value to the output stream.
      void writeBool(bool value);

      // Writes a signed integer value to the output stream.
      void writeInt(std::intmax_t value);

      // Writes an unsigned integer value to the output stream.
      void writeUInt(std::uintmax_t value);

      // Writes a string value to the output stream.
      void writeString(std::string_view value);

      void writeArray(ArrayWriterPtr array_writer, const void* value, bool one_element_per_line);

      void writeObject(ObjectWriterPtr object_writer, const void* value);

      void beginAggregate(char bracket);

      void endAggregate(char bracket, bool newline);

      template<class T>
      void writeValueRaw(const T& value);

      void writeFieldName(std::string_view field_name);

      void writeNewline();

      // \return true if there's an unflushed comment, false otherwise.
      constexpr bool hasUnflushedComment() const noexcept
      {
        return !comment_.empty();
      }

      void flushComments();

      std::ostream& stream_;
      // Comment(s) to print after the last printed entry (i.e. value or field),
      // or an empty string if no comments should be printed.
      // Comments are concatenated into a single string (newline-delimited). Comments are only written
      // to @stream_ when the next entry is printed or when the scope ends, to avoid trailing commas.
      std::string comment_;
      // Indicates whether @comment_ should be printed on the same line as the last printed entry.
      bool is_inline_comment_ = false;
      // The number of spaces to indent entries by.
      unsigned int indent_ = 0;
      // True if one or more entries (i.e. values or fields) have been printed in the current scope, false otherwise.
      bool has_members_in_scope_ = false;
    };

    template<class T>
    void JsonWriterContext::writeValueRaw(const T& value)
    {
      using Traits = JsonWriterTraits<T>;

      if constexpr (Traits::kValueType == JsonValueType::Bool)
      {
        static_assert(std::is_same_v<decltype(Traits::getValue(value)), bool>,
                      "JsonWriterTraits<T>::getValue(value) must return bool.");
        writeBool(Traits::getValue(value));
      }
      else if constexpr (Traits::kValueType == JsonValueType::Int)
      {
        static_assert(std::is_integral_v<decltype(Traits::getValue(value))> &&
                      std::is_signed_v<decltype(Traits::getValue(value))>,
                      "JsonWriterTraits<T>::getValue(value) must return a signed integer.");
        writeInt(static_cast<std::intmax_t>(Traits::getValue(value)));
      }
      else if constexpr (Traits::kValueType == JsonValueType::UInt)
      {
        static_assert(std::is_integral_v<decltype(Traits::getValue(value))> &&
                      std::is_unsigned_v<decltype(Traits::getValue(value))>,
                      "JsonWriterTraits<T>::getValue(value) must return an unsigned integer.");
        writeUInt(static_cast<std::uintmax_t>(Traits::getValue(value)));
      }
      else if constexpr (Traits::kValueType == JsonValueType::String)
      {
        static_assert(std::is_convertible_v<decltype(Traits::getValue(value)), std::string_view>,
                      "JsonWriterTraits<T>::getValue(value) must be convertible to std::string_view.");
        writeString(Traits::getValue(value));
      }
      else if constexpr (Traits::kValueType == JsonValueType::Array)
      {
        constexpr bool kOneElementPerLine = OneElementPerLineImpl<T>::value;
        writeArray([](ArrayElementsWriter& elements_writer, const void* value_ptr)
                   {
                     JsonArrayWriter<T>{}(elements_writer, *static_cast<const T*>(value_ptr));
                   },
                   static_cast<const void*>(std::addressof(value)),
                   kOneElementPerLine);
      }
      else if constexpr (Traits::kValueType == JsonValueType::Object)
      {
        writeObject([](FieldsWriter& fields_writer, const void* value_ptr)
                    {
                      JsonObjectWriter<T>{}(fields_writer, *static_cast<const T*>(value_ptr));
                    },
                    static_cast<const void*>(std::addressof(value)));
      }
      else
      {
        static_assert(false, "Invalid JsonWriterTraits<T>::kValueType.");
      }
    }

    template<class T>
    void JsonWriterContext::writeValue(const T& value, bool newline)
    {
      beforeWriteValue(newline);
      writeValueRaw(value);
    }

    template<class T>
    void JsonWriterContext::writeField(std::string_view field_name, const T& value)
    {
      writeFieldName(field_name);
      writeValueRaw(value);
    }
  }
}
