#pragma once

#include <h3mtxt/Medea/IJsonSerializer.h>

#include <cstdint>
#include <iosfwd>
#include <string>
#include <type_traits>

namespace Medea_NS
{
  namespace Detail_NS
  {
    // Implementation of IJsonSerializer that writes formatted JSON to std::ostream.
    //
    // Note that the constructor is private; only the static member function writeJson()
    // can be used directly.
    class JsonWriterImpl final : private IJsonSerializer
    {
    public:
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

    private:
      explicit constexpr JsonWriterImpl(std::ostream& stream, unsigned int initial_indent = 0) noexcept :
        stream_(stream),
        indent_(initial_indent)
      {}

      void beforeWriteElementOrField() override;

      // Writes a boolean value to the output stream.
      void writeBool(bool value) override;

      // Writes a signed integer value to the output stream.
      void writeInt(std::intmax_t value) override;

      // Writes an unsigned integer value to the output stream.
      void writeUInt(std::uintmax_t value) override;

      // Writes a string value to the output stream.
      void writeString(std::string_view value) override;

      void writeArray(ArrayWriterPtr array_writer, const void* value, bool single_line) override;

      void writeObject(ObjectWriterPtr object_writer, const void* value, bool single_line) override;

      void writeFieldName(std::string_view field_name) override;

      // Queues a comment.
      void writeComment(std::string_view comment, bool newline) override;

      void beginAggregate(char bracket);

      void endAggregate(char bracket);

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
    void JsonWriterImpl::writeJson(std::ostream& stream, const T& value, unsigned int initial_indent, bool single_line)
    {
      JsonWriterImpl writer(stream, initial_indent);
      // TODO: write initial indent.
      writer.writeValueRaw(value, single_line);
    }
  }
}
