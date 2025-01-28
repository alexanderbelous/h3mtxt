#pragma once

#include <h3mtxt/TextWriter/TextWriter.h>
#include <h3mtxt/TextWriter/TextWriterFwd.h>
#include <h3mtxt/TextWriter/ValueWriter.h>

#include <string_view>

namespace Util_NS
{
  // Class for writing *fields* with indent.
  // You cannot construct it manually; use TextWriter::writeStruct() instead.
  class ScopedStructWriter
  {
  public:
    // Decreases the indent of the underlying IndentedTextWriter and writes the closing brace '}'.
    ~ScopedStructWriter();

    // Non-copyable, non-movable.
    ScopedStructWriter(const ScopedStructWriter&) = delete;
    ScopedStructWriter(ScopedStructWriter&&) = delete;
    ScopedStructWriter& operator=(const ScopedStructWriter&) = delete;
    ScopedStructWriter& operator=(ScopedStructWriter&&) = delete;

    // Writes a single field.
    template<class T>
    void writeField(std::string_view field_name, const T& value);

    // Write a comment line.
    // \param comment - comment text.
    // \param newline - if true, the comment will be written on a new line,
    //        otherwise it will be written on the current line.
    void writeComment(std::string_view comment, bool newline = true);

    // Appends a comma after the last written field, if needed.
    void writeComma();

  private:
    enum class Token
    {
      None,
      Field,
      Comment,
      Comma
    };

    friend IndentedTextWriter;

    // Writes an opening brace '{' and increases the indent of the given IndentedTextWriter.
    explicit ScopedStructWriter(IndentedTextWriter& out);

    void writeFieldName(std::string_view field_name);

    IndentedTextWriter& out_;
    Token last_token_ = Token::None;
    // True if a comma needs to be appended before writing another field, false otherwise.
    bool needs_comma_ = false;
  };

  template<class T>
  void ScopedStructWriter::writeField(std::string_view field_name, const T& value)
  {
    writeFieldName(field_name);
    ValueWriter<T> value_writer{};
    value_writer(out_, value);
    needs_comma_ = true;
    last_token_ = Token::Field;
  }
}
