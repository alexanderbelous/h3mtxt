#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>
#include <h3mtxt/JsonWriter/JsonWriterContext.h>
#include <h3mtxt/JsonWriter/writeValue.h>

#include <string_view>

namespace Medea_NS
{
  // Class for serializing elements of a JSON array.
  template<class T>
  class ScopedArrayWriter
  {
  public:
    explicit ScopedArrayWriter(Detail_NS::JsonWriterContext& context, bool one_element_per_line = true);

    ~ScopedArrayWriter() = default;

    // Non-copyable, non-movable.
    ScopedArrayWriter(const ScopedArrayWriter&) = delete;
    ScopedArrayWriter(ScopedArrayWriter&&) = delete;
    ScopedArrayWriter& operator=(const ScopedArrayWriter&) = delete;
    ScopedArrayWriter& operator=(ScopedArrayWriter&&) = delete;

    // Writes a single element.
    void writeElement(const T& value);

    // Write a comment line.
    void writeComment(std::string_view comment)
    {
      context_.writeComment(comment, true);
    }

  private:
    Detail_NS::JsonWriterContext& context_;
    // True if each element should be a written on a new line, false otherwise.
    bool one_element_per_line_ = true;
  };

  template<class T>
  ScopedArrayWriter<T>::ScopedArrayWriter(Detail_NS::JsonWriterContext& context, bool one_element_per_line):
    context_(context),
    one_element_per_line_(one_element_per_line)
  {}

  template<class T>
  void ScopedArrayWriter<T>::writeElement(const T& value)
  {
    context_.beforeWriteValue(one_element_per_line_);
    Detail_NS::writeValueRaw(context_, value);
  }
}
