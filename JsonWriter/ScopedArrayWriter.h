#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>
#include <h3mtxt/JsonWriter/JsonWriterContext.h>
#include <h3mtxt/JsonWriter/writeValue.h>

#include <string_view>

namespace Medea_NS
{
  class ScopedArrayWriterBase
  {
  public:
    ~ScopedArrayWriterBase();

    // Non-copyable, non-movable.
    ScopedArrayWriterBase(const ScopedArrayWriterBase&) = delete;
    ScopedArrayWriterBase(ScopedArrayWriterBase&&) = delete;
    ScopedArrayWriterBase& operator=(const ScopedArrayWriterBase&) = delete;
    ScopedArrayWriterBase& operator=(ScopedArrayWriterBase&&) = delete;

    // Write a comment line.
    void writeComment(std::string_view comment);

  protected:
    explicit ScopedArrayWriterBase(Detail_NS::JsonWriterContext& context, bool one_element_per_line = true);

    Detail_NS::JsonWriterContext& context_;
    // True if each element should be a written on a new line, false otherwise.
    bool one_element_per_line_ = true;
  };

  // Class for writing an array of values with indent.
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
    context_.beforeWriteValue(one_element_per_line_);
    Detail_NS::writeValueRaw(context_, value);
  }
}
