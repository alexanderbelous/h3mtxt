#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>
#include <h3mtxt/JsonWriter/JsonWriterContext.h>
#include <h3mtxt/JsonWriter/JsonWriterTraits.h>
#include <h3mtxt/JsonWriter/writeValue.h>

#include <string_view>

namespace Medea_NS
{
  // Class for serializing elements of a JSON array.
  template<class T>
  class ScopedArrayWriter
  {
  public:
    explicit constexpr ScopedArrayWriter(Detail_NS::JsonWriterContext& context) noexcept;

    ~ScopedArrayWriter() = default;

    // Non-copyable, non-movable.
    ScopedArrayWriter(const ScopedArrayWriter&) = delete;
    ScopedArrayWriter(ScopedArrayWriter&&) = delete;
    ScopedArrayWriter& operator=(const ScopedArrayWriter&) = delete;
    ScopedArrayWriter& operator=(ScopedArrayWriter&&) = delete;

    // Writes a single element.
    void writeElement(const T& value) const;

    // Write a comment line.
    void writeComment(std::string_view comment) const;

  private:
    Detail_NS::JsonWriterContext& context_;
  };

  template<class T>
  constexpr ScopedArrayWriter<T>::ScopedArrayWriter(Detail_NS::JsonWriterContext& context) noexcept:
    context_(context)
  {}

  template<class T>
  void ScopedArrayWriter<T>::writeElement(const T& value) const
  {
    context_.beforeWriteValue(!IsSingleLineArray<T>::value);
    Detail_NS::writeValueRaw(context_, value);
  }

  template<class T>
  void ScopedArrayWriter<T>::writeComment(std::string_view comment) const
  {
    context_.writeComment(comment, true);
  }
}
