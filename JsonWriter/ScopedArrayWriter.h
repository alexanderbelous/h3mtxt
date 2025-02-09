#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>
#include <h3mtxt/JsonWriter/JsonValueWriter.h>

#include <string_view>

namespace Util_NS
{
  // Non-template base of ScopedArrayWriter.
  class ScopedArrayWriterBase
  {
  public:
    // Decreases the indent of the underlying JsonDocumentWriter and writes the closing bracket ']'.
    ~ScopedArrayWriterBase();

    // Non-copyable, non-movable.
    ScopedArrayWriterBase(const ScopedArrayWriterBase&) = delete;
    ScopedArrayWriterBase(ScopedArrayWriterBase&&) = delete;
    ScopedArrayWriterBase& operator=(const ScopedArrayWriterBase&) = delete;
    ScopedArrayWriterBase& operator=(ScopedArrayWriterBase&&) = delete;

    // Write a comment line.
    void writeComment(std::string_view comment);

  protected:
    // Writes an opening bracket '[' and increases the indent of the given JsonDocumentWriter.
    explicit ScopedArrayWriterBase(const Detail_NS::JsonWriterContext& context, bool one_element_per_line = true);

    void beforeWriteElement();

    void afterWriteElement();

    enum class Token
    {
      Nothing,
      Element,
      Comment
    };

    Detail_NS::JsonWriterContext context_;
    // The last token written via this object.
    Token last_token_ = Token::Nothing;
    // True if each element should be a written on a new line, false otherwise.
    bool one_element_per_line_ = true;
  };

  // Class for writing an array of values with indent.
  // You cannot construct it manually; use TextWriter::writeArray() instead.
  template<class T>
  class ScopedArrayWriter : public ScopedArrayWriterBase
  {
  public:
    explicit ScopedArrayWriter(const Detail_NS::JsonWriterContext& context, bool one_element_per_line = true);

    // Writes a single element.
    void writeElement(const T& value);

  private:
    [[no_unique_address]] JsonValueWriter<T> value_writer_ {};
  };

  template<class T>
  ScopedArrayWriter<T>::ScopedArrayWriter(const Detail_NS::JsonWriterContext& context, bool one_element_per_line):
    ScopedArrayWriterBase(context, one_element_per_line)
  {}

  template<class T>
  void ScopedArrayWriter<T>::writeElement(const T& value)
  {
    beforeWriteElement();
    JsonDocumentWriter document_writer(context_);
    value_writer_(document_writer, value);
    afterWriteElement();
  }
}
