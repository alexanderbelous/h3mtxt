#pragma once

#include <h3mtxt/TextWriter/TextWriterFwd.h>

#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <map>
#include <span>
#include <string_view>

namespace Util_NS
{
  // Class for writing values with indent.
  //
  // This is low-level shit; you only need this to pass to ValueWriter or FieldsWriter.
  class IndentedTextWriter
  {
  public:
    explicit IndentedTextWriter(std::ostream& stream, std::size_t initial_indent = 0);

    void writeComment(std::string_view comment);

    void writeString(std::string_view value);

    template<class T>
    std::enable_if_t<std::is_integral_v<T>> writeInteger(T value);

    // Writes an array of elements.
    // Individual elements are written via ValueWriter<T>.
    // TODO: add a scope guard that allows writing individual elements.
    //       This can be useful for specializations of ValueWriter which
    //       also provide comments for the elements.
    template<class T>
    void writeArray(std::span<const T> values);

    // TODO: I think this could be implemented entirely in ValueWriter.
    template<class Key, class Value, class Cmp, class Alloc>
    void writeMap(const std::map<Key, Value, Cmp, Alloc>& map);

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

  private:
    friend ScopedStructWriter;

    void writeNewlineIfNeeded();

    void writeUnquoted(std::string_view str);

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
  void IndentedTextWriter::writeArray(std::span<const T> values)
  {
    writeNewlineIfNeeded();
    if (values.empty())
    {
      writeUnquoted("[]");
      needs_newline_ = true;
    }
    else
    {
      writeUnquoted("[");
      needs_newline_ = true;
      increaseIndent();
      const std::size_t num_elements = values.size();
      for (std::size_t i = 0; i < num_elements; ++i)
      {
        ValueWriter<T> value_writer {};
        value_writer(*this, values[i]);
        // If this is not the last element, append a comma.
        if (i + 1 != num_elements)
        {
          writeUnquoted(",");
        }
      }
      decreaseIndent();
      writeNewlineIfNeeded();
      writeUnquoted("]");
      needs_newline_ = true;
    }
  }

  template<class Key, class Value, class Cmp, class Alloc>
  void IndentedTextWriter::writeMap(const std::map<Key, Value, Cmp, Alloc>& map)
  {
    writeNewlineIfNeeded();
    if (map.empty())
    {
      writeUnquoted("[]");
      needs_newline_ = true;
      return;
    }
    writeUnquoted("[");
    needs_newline_ = true;
    increaseIndent();
    for (auto iter = map.begin(); iter != map.end(); ++iter)
    {
      {
        ScopedStructWriter fields_writer = writeStruct();
        fields_writer.writeField("key", iter->first);
        fields_writer.writeField("value", iter->second);
      }
      if (std::next(iter) != map.end())
      {
        writeUnquoted(",");
      }
    }
    decreaseIndent();
    writeNewlineIfNeeded();
    writeUnquoted("]");
    needs_newline_ = true;
  }
}
