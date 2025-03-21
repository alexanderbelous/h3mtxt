#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>

#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <string>
#include <string_view>

namespace Medea_NS
{
  // Forward declaration of writeJson().
  template<class T>
  void writeJson(std::ostream& stream, const T& value, unsigned int initial_indent);

  namespace Detail_NS
  {
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

      // Writes a boolean value to the output stream.
      void writeBool(bool value);

      // Writes a signed integer value to the output stream.
      void writeInt(std::intmax_t value);

      // Writes an unsigned integer value to the output stream.
      void writeUInt(std::uintmax_t value);

      // Writes a string value to the output stream.
      void writeString(std::string_view value);

      void beginAggregate(char bracket);

      void endAggregate(char bracket, bool newline);

      void writeFieldName(std::string_view field_name);

      // Queues a comment.
      //
      // Comments are not written immediately in order to avoid trailing commas in printing objects/arrays.
      // \param comment - comment to write. Empty comments are ignored.
      // \param newline - if true, the comment will be written on a new line,
      //        otherwise on the same line as the last printed entry.
      //        This parameter is ignored if !comment_.empty() - in that case @comment will be appended to
      //        comment_ after a newline character.
      void writeComment(std::string_view comment, bool newline);

      void beforeWriteValue(bool newline);

    private:
      explicit constexpr JsonWriterContext(std::ostream& stream, unsigned int initial_indent = 0) noexcept :
        stream_(stream),
        indent_(initial_indent)
      {}

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
      // True if one or more comments have been printed in the current scope, false otherwise.
      bool has_comments_in_scope_ = false;
    };
  }
}
