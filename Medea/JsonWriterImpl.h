#pragma once

#include <h3mtxt/Medea/MedeaFwd.h>

#include <cstdint>
#include <iosfwd>
#include <memory>
#include <string>
#include <string_view>
#include <type_traits>

namespace Medea_NS
{
  namespace Detail_NS
  {
    // Internal class for writing formatted JSON.
    //
    // Note that the constructor is private; only the static member function writeJson()
    // can be used directly.
    class JsonWriterImpl
    {
    public:
      // Non-copyable, non-movable.
      constexpr JsonWriterImpl(const JsonWriterImpl&) = delete;
      constexpr JsonWriterImpl(JsonWriterImpl&&) = delete;
      JsonWriterImpl& operator=(const JsonWriterImpl&) = delete;
      JsonWriterImpl& operator=(JsonWriterImpl&&) = delete;

      constexpr ~JsonWriterImpl() = default;

      // Serializes the given value into the specified stream as JSON.
      // \param stream - output stream.
      // \param value - value to serialize.
      // \param initial_indent - the initial indent (number of spaces).
      // \param single_line - if true, @value will be written on a single line
      //        (unless it's serialized as an object/array and one or more comments will be printed for it),
      //        otherwise over multiple lines.
      template<class T>
      static void writeJson(std::ostream& stream,
                            const T& value,
                            unsigned int initial_indent = 0,
                            bool single_line = kIsSingleLineByDefault<std::remove_cvref_t<T>>);

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
      void writeArrayElement(const T& value, bool single_line);

      template<class T>
      void writeField(std::string_view field_name, const T& value, bool single_line);

    private:
      // Type-erased version of JsonArrayWriter<T>.
      using ArrayWriterPtr = void(*)(const ArrayElementsWriter&, const void*);
      // Type-erased version of JsonObjectWriter<T>.
      using ObjectWriterPtr = void(*)(FieldsWriter&, const void*);

      explicit constexpr JsonWriterImpl(std::ostream& stream, unsigned int initial_indent = 0) noexcept :
        stream_(stream),
        indent_(initial_indent)
      {}

      void beforeWriteElementOrField();

      // Writes a boolean value to the output stream.
      void writeBool(bool value);

      // Writes a signed integer value to the output stream.
      void writeInt(std::intmax_t value);

      // Writes an unsigned integer value to the output stream.
      void writeUInt(std::uintmax_t value);

      // Writes a string value to the output stream.
      void writeString(std::string_view value);

      void writeArray(ArrayWriterPtr array_writer, const void* value, bool single_line);

      void writeObject(ObjectWriterPtr object_writer, const void* value, bool single_line);

      void beginAggregate(char bracket);

      void endAggregate(char bracket);

      template<class T>
      void writeValueRaw(const T& value, bool single_line);

      void writeFieldName(std::string_view field_name);

      void writeNewline();

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
      // True if the current value is being serialized on a single line, false otherwise.
      bool is_single_line_ = false;
    };

    template<class T>
    void JsonWriterImpl::writeValueRaw(const T& value, bool single_line)
    {
      using Traits = JsonWriterTraits<T>;

      if constexpr (Traits::kDataType == JsonDataType::Bool)
      {
        static_assert(std::is_same_v<decltype(Traits::getValue(value)), bool>,
                      "JsonWriterTraits<T>::getValue(value) must return bool.");
        writeBool(Traits::getValue(value));
      }
      else if constexpr (Traits::kDataType == JsonDataType::Int)
      {
        static_assert(std::is_integral_v<decltype(Traits::getValue(value))> &&
                      std::is_signed_v<decltype(Traits::getValue(value))>,
                      "JsonWriterTraits<T>::getValue(value) must return a signed integer.");
        writeInt(static_cast<std::intmax_t>(Traits::getValue(value)));
      }
      else if constexpr (Traits::kDataType == JsonDataType::UInt)
      {
        static_assert(std::is_integral_v<decltype(Traits::getValue(value))> &&
                      std::is_unsigned_v<decltype(Traits::getValue(value))>,
                      "JsonWriterTraits<T>::getValue(value) must return an unsigned integer.");
        writeUInt(static_cast<std::uintmax_t>(Traits::getValue(value)));
      }
      else if constexpr (Traits::kDataType == JsonDataType::String)
      {
        static_assert(std::is_convertible_v<decltype(Traits::getValue(value)), std::string_view>,
                      "JsonWriterTraits<T>::getValue(value) must be convertible to std::string_view.");
        writeString(Traits::getValue(value));
      }
      else if constexpr (Traits::kDataType == JsonDataType::Array)
      {
        writeArray([](const ArrayElementsWriter& elements_writer, const void* value_ptr)
                   {
                     JsonArrayWriter<T>{}(elements_writer, *static_cast<const T*>(value_ptr));
                   },
                   std::addressof(value),
                   single_line);
      }
      else if constexpr (Traits::kDataType == JsonDataType::Object)
      {
        writeObject([](FieldsWriter& fields_writer, const void* value_ptr)
                    {
                      JsonObjectWriter<T>{}(fields_writer, *static_cast<const T*>(value_ptr));
                    },
                    static_cast<const void*>(std::addressof(value)),
                    single_line);
      }
      else
      {
        static_assert(false, "Invalid JsonWriterTraits<T>::kDataType.");
      }
    }

    template<class T>
    void JsonWriterImpl::writeArrayElement(const T& value, bool single_line)
    {
      beforeWriteElementOrField();
      writeValueRaw(value, single_line);
    }

    template<class T>
    void JsonWriterImpl::writeField(std::string_view field_name, const T& value, bool single_line)
    {
      writeFieldName(field_name);
      writeValueRaw(value, single_line);
    }

    template<class T>
    void JsonWriterImpl::writeJson(std::ostream& stream, const T& value, unsigned int initial_indent, bool single_line)
    {
      JsonWriterImpl context(stream, initial_indent);
      // TODO: write initial indent.
      context.writeValueRaw(value, single_line);
    }
  }
}
