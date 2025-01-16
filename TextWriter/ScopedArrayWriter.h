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
    explicit ScopedArrayWriterBase(IndentedTextWriter& out);

    void writeCommaIfNeeded();

    IndentedTextWriter& out_;
    // True if at least 1 element or comment has been written, false otherwise.
    bool has_elements_or_comments_ = false;
    // True if a comma needs to be written before writing another element or comment, false otherwise.
    bool need_comma_ = false;
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

    // Writes an opening bracket '[' and increases the indent of the given IndentedTextWriter.
    explicit ScopedArrayWriter(IndentedTextWriter& out);
  };

  template<class T>
  ScopedArrayWriter<T>::ScopedArrayWriter(IndentedTextWriter & out):
    ScopedArrayWriterBase(out)
  {}

  template<class T>
  void ScopedArrayWriter<T>::writeElement(const T& value)
  {
    writeCommaIfNeeded();
    ValueWriter<T> value_writer{};
    value_writer(out_, value);
    has_elements_or_comments_ = true;
    need_comma_ = true;
  }
}
