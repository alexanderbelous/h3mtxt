#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>
#include <h3mtxt/JsonWriter/writeValue.h>

#include <string>
#include <string_view>

namespace Medea_NS
{
  // Class for writing fields of a JSON object.
  class ScopedObjectWriter
  {
  public:
    // Writes an opening brace '{' and increases the indent.
    // Note that the constructor of JsonWriterContext is private, so you won't be able to
    // construct ScopedObjectWriter manually; use JsonDocumentWriter::writeObject() instead.
    explicit ScopedObjectWriter(Detail_NS::JsonWriterContext& context);

    // Decreases the indent of the underlying JsonDocumentWriter and writes the closing brace '}'.
    ~ScopedObjectWriter();

    // Non-copyable, non-movable.
    ScopedObjectWriter(const ScopedObjectWriter&) = delete;
    ScopedObjectWriter(ScopedObjectWriter&&) = delete;
    ScopedObjectWriter& operator=(const ScopedObjectWriter&) = delete;
    ScopedObjectWriter& operator=(ScopedObjectWriter&&) = delete;

    // Writes a single field.
    template<class T>
    void writeField(std::string_view field_name, const T& value);

    // Write a comment line.
    // \param comment - comment text. Empty comments are ignored.
    // \param newline - if true, the comment will be written on a new line,
    //        otherwise it will be written on the current line.
    void writeComment(std::string_view comment, bool newline = true);

  private:
    // Appends a comma after the last written field, if needed,
    // calls flushComments(),
    // and prints the name of the field.
    void writeFieldName(std::string_view field_name);

    // Actually writes the comments to the underlying stream.
    void flushComments();

    Detail_NS::JsonWriterContext& context_;
    // Comment(s) to print after the last printed field, or an empty string if no comments should be printed.
    // Comments are concatenated into a single string (newline-delimited).
    std::string comment_;
    bool is_inline_comment_ = false;
    // True if 1 or more comments have been written, false otherwise.
    bool has_comments_ = false;
    // True if 1 or more fields have been written, false otherwise.
    bool has_fields_ = false;
  };

  template<class T>
  void ScopedObjectWriter::writeField(std::string_view field_name, const T& value)
  {
    writeFieldName(field_name);
    Detail_NS::writeValue(context_, value);
    context_.needs_newline_ = true;
  }
}
