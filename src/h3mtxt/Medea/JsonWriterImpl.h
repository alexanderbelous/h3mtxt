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
    //
    // TODO: interestingly, this can be made into an interface, allowing multiple implementations:
    // * Printing formatted JSON into a stream.
    // * Printing minified JSON into a stream (no comments, no idents).
    // * Constructing a JsonCpp object.
    // * ...
    //
    // This will likely have some overhead from virtual functions, but maybe the compiler is smart
    // enough to devirtualize them in simple cases.
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
      constexpr JsonDataType kDataType = kJsonDataTypeFor<std::remove_cvref_t<T>>;

      if constexpr (kDataType == JsonDataType::Bool)
      {
        using ScalarGetter = JsonScalarGetter<std::remove_cvref_t<T>>;
        static_assert(std::is_invocable_v<ScalarGetter, const T&>,
                      "This type should be serialized as JsonDataType::Bool, but "
                      "JsonScalarGetter is not invokable for this type. Have you forgotten to specialize it?");
        static_assert(std::is_same_v<std::remove_cvref_t<std::invoke_result_t<ScalarGetter, const T&>>, bool>,
                      "This type should be serialized as JsonDataType::Bool, but "
                      "JsonScalarGetter returns a value that isn't bool.");
        writeBool(ScalarGetter{}(value));
      }
      else if constexpr (kDataType == JsonDataType::Int)
      {
        using ScalarGetter = JsonScalarGetter<std::remove_cvref_t<T>>;
        static_assert(std::is_invocable_v<ScalarGetter, const T&>,
                      "This type should be serialized as JsonDataType::Int, but "
                      "JsonScalarGetter is not invokable for this type. Have you forgotten to specialize it?");
        using ScalarGetterResult = std::remove_cvref_t<std::invoke_result_t<ScalarGetter, const T&>>;
        static_assert(std::is_integral_v<ScalarGetterResult> && std::is_signed_v<ScalarGetterResult>,
                      "This type should be serialized as JsonDataType::Int, but "
                      "JsonScalarGetter returns a value that isn't a signed integer.");
        writeInt(static_cast<std::intmax_t>(ScalarGetter{}(value)));
      }
      else if constexpr (kDataType == JsonDataType::UInt)
      {
        using ScalarGetter = JsonScalarGetter<std::remove_cvref_t<T>>;
        static_assert(std::is_invocable_v<ScalarGetter, const T&>,
                      "This type should be serialized as JsonDataType::UInt, but "
                      "JsonScalarGetter is not invokable for this type. Have you forgotten to specialize it?");
        using ScalarGetterResult = std::remove_cvref_t<std::invoke_result_t<ScalarGetter, const T&>>;
        static_assert(std::is_integral_v<ScalarGetterResult> && std::is_unsigned_v<ScalarGetterResult>,
                      "This type should be serialized as JsonDataType::UInt, but "
                      "JsonScalarGetter returns a value that isn't a unsigned integer.");
        writeUInt(static_cast<std::uintmax_t>(ScalarGetter{}(value)));
      }
      else if constexpr (kDataType == JsonDataType::String)
      {
        using ScalarGetter = JsonScalarGetter<std::remove_cvref_t<T>>;
        static_assert(std::is_invocable_v<ScalarGetter, const T&>,
                      "This type should be serialized as JsonDataType::String, but "
                      "JsonScalarGetter is not invokable for this type. Have you forgotten to specialize it?");
        using ScalarGetterResult = std::invoke_result_t<ScalarGetter, const T&>;
        static_assert(std::is_convertible_v<ScalarGetterResult, std::string_view>,
                      "This type should be serialized as JsonDataType::String, but "
                      "JsonScalarGetter returns a value that isn't convertible to std::string_view.");
        writeString(ScalarGetter{}(value));
      }
      else if constexpr (kDataType == JsonDataType::Array)
      {
        writeArray([](const ArrayElementsWriter& elements_writer, const void* value_ptr)
                   {
                     JsonArrayWriter<T>{}(elements_writer, *static_cast<const T*>(value_ptr));
                   },
                   std::addressof(value),
                   single_line);
      }
      else if constexpr (kDataType == JsonDataType::Object)
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
        static_assert(false, "Invalid kJsonDataTypeFor<T>.");
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
