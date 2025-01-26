#pragma once

#include <h3mtxt/TextWriter/TextWriterFwd.h>

#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <string_view>
#include <type_traits>

namespace Util_NS
{
  // Class for writing values with indent.
  //
  // This is low-level shit; you only need this to pass it to ValueWriter.
  class IndentedTextWriter
  {
  public:
    explicit IndentedTextWriter(std::ostream& stream, std::size_t initial_indent = 0);

    void writeComment(std::string_view comment);

    void writeString(std::string_view value);

    void writeBool(bool value);

    template<class T>
    std::enable_if_t<std::is_integral_v<T>> writeInteger(T value);

    // Start writing a structure.
    //
    // Note that ScopedStructWriter is non-copyable and non-movable, but we can still return it
    // by value from this function thanks to guaranteed copy elision.
    //
    // TODO: maybe this shouldn't even be public: only the default implementation of ValueWriter
    // actually needs it.
    //
    // \return a ScopedStructWriter object that can be used to write the fields of the structure.
    ScopedStructWriter writeStruct();

    // Start writing an array.
    //
    // Note that ScopedArrayWriter is non-copyable and non-movable, but we can still return it
    // by value from this function thanks to guaranteed copy elision.
    //
    // This function is public to support writing comments when printing elements of an array.
    //
    // TODO: ideally, other functions should become "unavailable" during the lifetime of the
    // returned ScopedArrayWriter - it should be an error to write into the underlying stream
    // via anything other than the returned ScopedArrayWriter. This can be achieved, for example,
    // by making stream_ a pointer and setting it to nullptr in the constructor of ScopedArrayWriter,
    // then restoring the original value in the destructor.
    //
    // \return a ScopedArrayWriter object that can be used to write elements of the array.
    template<class T>
    ScopedArrayWriter<T> writeArray(bool one_element_per_line = true);

  private:
    friend ScopedArrayWriterBase;
    friend ScopedStructWriter;

    void writeNewlineIfNeeded();

    void writeInt(std::intmax_t value);

    void writeUInt(std::uintmax_t value);

    // TODO: Implement a scope guard instead.
    void increaseIndent();

    void decreaseIndent();

    std::ostream& stream_;
    std::size_t indent_ = 0;
    bool needs_newline_ = false;
  };

  template<class T>
  std::enable_if_t<std::is_integral_v<T>> IndentedTextWriter::writeInteger(T value)
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
  ScopedArrayWriter<T> IndentedTextWriter::writeArray(bool one_element_per_line)
  {
    return ScopedArrayWriter<T>(*this, one_element_per_line);
  }
}
