#pragma once

#include <h3mtxt/JsonWriter/JsonWriterContext.h>

#include <cstdint>
#include <iosfwd>
#include <string_view>
#include <type_traits>

namespace Util_NS
{
  // Class for writing a JSON document.
  // This class only allows writing a single JSON value.
  class JsonDocumentWriter
  {
  public:
    explicit constexpr JsonDocumentWriter(std::ostream& stream, unsigned int initial_indent = 0) noexcept:
      context_(stream, initial_indent)
    {}

    // Constructs a JsonDocumentWriter with the given context.
    // This constructor cannot be used directly because the constructor of JsonWriterContext is private.
    explicit constexpr JsonDocumentWriter(const Detail_NS::JsonWriterContext& context) noexcept :
      context_(context)
    {}

    // \return true if a value has already been written, false otherwise.
    constexpr bool isDone() const noexcept
    {
      return is_done_;
    }

    // Writes a boolean value.
    // isDone() will return true after this call.
    // \param value - value to write.
    // \throw std::runtime_error if isDone().
    void writeBool(bool value);

    template<class T>
    std::enable_if_t<std::is_integral_v<T>> writeInteger(T value);

    void writeString(std::string_view value);

    // Start writing a structure.
    //
    // Note that ScopedStructWriter is non-copyable and non-movable, but we can still return it
    // by value from this function thanks to guaranteed copy elision.
    //
    // \return a ScopedStructWriter object that can be used to write the fields of the structure.
    ScopedStructWriter writeStruct();

    // Start writing an array.
    //
    // Note that ScopedArrayWriter is non-copyable and non-movable, but we can still return it
    // by value from this function thanks to guaranteed copy elision.
    //
    // \return a ScopedArrayWriter object that can be used to write elements of the array.
    template<class T>
    ScopedArrayWriter<T> writeArray(bool one_element_per_line = true);

  private:
    // \throw std::runtime_error if isDone().
    void checkNotDone() const;

    void writeInt(std::intmax_t value);

    void writeUInt(std::uintmax_t value);

    // Ideally, this should be std::optional, but the constructor of JsonWriterContext is private.
    Detail_NS::JsonWriterContext context_;
    bool is_done_ = false;
  };

  template<class T>
  std::enable_if_t<std::is_integral_v<T>> JsonDocumentWriter::writeInteger(T value)
  {
    if constexpr (std::is_signed_v<T>)
    {
      writeInt(static_cast<std::intmax_t>(value));
    }
    else
    {
      writeUInt(static_cast<std::uintmax_t>(value));
    }
  }

  template<class T>
  ScopedArrayWriter<T> JsonDocumentWriter::writeArray(bool one_element_per_line)
  {
    checkNotDone();
    is_done_ = true;
    return ScopedArrayWriter<T>(context_, one_element_per_line);
  }
}
