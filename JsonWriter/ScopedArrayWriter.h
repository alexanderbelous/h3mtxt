#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>
#include <h3mtxt/JsonWriter/writeValue.h>

#include <string_view>

namespace Medea_NS
{
  // Non-template base of ScopedArrayWriter.
  class ScopedArrayWriterBase
  {
  public:
    // Decreases the indent of the underlying JsonWriterContext and writes the closing bracket ']'.
    ~ScopedArrayWriterBase();

    // Non-copyable, non-movable.
    ScopedArrayWriterBase(const ScopedArrayWriterBase&) = delete;
    ScopedArrayWriterBase(ScopedArrayWriterBase&&) = delete;
    ScopedArrayWriterBase& operator=(const ScopedArrayWriterBase&) = delete;
    ScopedArrayWriterBase& operator=(ScopedArrayWriterBase&&) = delete;

    // Write a comment line.
    void writeComment(std::string_view comment);

  protected:
    // Writes an opening bracket '[' and increases the indent of the given JsonWriterContext.
    explicit ScopedArrayWriterBase(Detail_NS::JsonWriterContext& context, bool one_element_per_line = true);

    void beforeWriteElement();

    void afterWriteElement();

    Detail_NS::JsonWriterContext& context_;
    // True if each element should be a written on a new line, false otherwise.
    bool one_element_per_line_ = true;
    // True if 1 or more elements have been written, false otherwise.
    bool has_elements_ = false;
  };

  // Class for writing an array of values with indent.
  // You cannot construct it manually; use TextWriter::writeArray() instead.
  template<class T>
  class ScopedArrayWriter : public ScopedArrayWriterBase
  {
  public:
    explicit ScopedArrayWriter(Detail_NS::JsonWriterContext& context, bool one_element_per_line = true);

    // Writes a single element.
    void writeElement(const T& value);
  };

  template<class T>
  ScopedArrayWriter<T>::ScopedArrayWriter(Detail_NS::JsonWriterContext& context, bool one_element_per_line):
    ScopedArrayWriterBase(context, one_element_per_line)
  {}

  template<class T>
  void ScopedArrayWriter<T>::writeElement(const T& value)
  {
    beforeWriteElement();
    Detail_NS::writeValue(context_, value);
    afterWriteElement();
  }
}
