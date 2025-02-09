#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>
#include <h3mtxt/JsonWriter/JsonValueWriter.h>

#include <string_view>

namespace Medea_NS
{
  // Class for writing fields of a JSON object.
  class ScopedStructWriter
  {
  public:
    // Writes an opening brace '{' and increases the indent.
    // Note that the constructor of JsonWriterContext is private, so you won't be able to
    // construct ScopedStructWriter manually; use JsonDocumentWriter::writeStruct() instead.
    explicit ScopedStructWriter(const Detail_NS::JsonWriterContext& context);

    // Decreases the indent of the underlying JsonDocumentWriter and writes the closing brace '}'.
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

    void writeFieldName(std::string_view field_name);

    Detail_NS::JsonWriterContext context_;
    Token last_token_ = Token::None;
    // True if a comma needs to be appended before writing another field, false otherwise.
    bool needs_comma_ = false;
  };

  template<class T>
  void ScopedStructWriter::writeField(std::string_view field_name, const T& value)
  {
    writeFieldName(field_name);
    JsonDocumentWriter document_writer(context_);
    JsonValueWriter<T> value_writer{};
    value_writer(document_writer, value);
    context_.needs_newline_ = true;
    needs_comma_ = true;
    last_token_ = Token::Field;
  }
}
