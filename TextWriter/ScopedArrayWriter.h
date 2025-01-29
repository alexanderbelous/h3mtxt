#pragma once

#include <h3mtxt/TextWriter/TextWriter.h>
#include <h3mtxt/TextWriter/TextWriterFwd.h>
#include <h3mtxt/TextWriter/ValueWriter.h>

#include <string_view>

namespace Util_NS
{
  // Non-template base of ScopedArrayWriter.
  class ScopedArrayWriterBase
  {
  public:
    // Decreases the indent of the underlying IndentedTextWriter and writes the closing bracket ']'.
    ~ScopedArrayWriterBase();

    // Non-copyable, non-movable.
    ScopedArrayWriterBase(const ScopedArrayWriterBase&) = delete;
    ScopedArrayWriterBase(ScopedArrayWriterBase&&) = delete;
    ScopedArrayWriterBase& operator=(const ScopedArrayWriterBase&) = delete;
    ScopedArrayWriterBase& operator=(ScopedArrayWriterBase&&) = delete;

    // Write a comment line.
    void writeComment(std::string_view comment);

  protected:
    // Writes an opening bracket '[' and increases the indent of the given IndentedTextWriter.
    explicit ScopedArrayWriterBase(IndentedTextWriter& out, bool one_element_per_line = true);

    void beforeWriteElement();

    void afterWriteElement();

    enum class Token
    {
      Nothing,
      Element,
      Comment
    };

    IndentedTextWriter& out_;
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
    // Writes a single element.
    void writeElement(const T& value);

  private:
    friend IndentedTextWriter;

    explicit ScopedArrayWriter(IndentedTextWriter& out, bool one_element_per_line = true);

    [[no_unique_address]] JsonValueWriter<T> value_writer_ {};
  };

  template<class T>
  ScopedArrayWriter<T>::ScopedArrayWriter(IndentedTextWriter & out, bool one_element_per_line):
    ScopedArrayWriterBase(out, one_element_per_line)
  {}

  template<class T>
  void ScopedArrayWriter<T>::writeElement(const T& value)
  {
    beforeWriteElement();
    value_writer_(out_, value);
    afterWriteElement();
  }
}
