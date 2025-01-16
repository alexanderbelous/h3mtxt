#pragma once

#include <h3mtxt/TextWriter/TextWriter.h>
#include <h3mtxt/TextWriter/TextWriterFwd.h>
#include <h3mtxt/TextWriter/ValueWriter.h>

#include <string_view>

namespace Util_NS
{
  // Class for writing *fields* with indent.
  // You cannot construct it manually; use TextWriter::writeStruct() instead.
  class ScopedStructWriter
  {
  public:
    // Decreases the indent of the underlying IndentedTextWriter and writes the closing brace '}'.
    ~ScopedStructWriter();

    // Non-copyable, non-movable.
    ScopedStructWriter(const ScopedStructWriter&) = delete;
    ScopedStructWriter(ScopedStructWriter&&) = delete;
    ScopedStructWriter& operator=(const ScopedStructWriter&) = delete;
    ScopedStructWriter& operator=(ScopedStructWriter&&) = delete;

    // Writes a single field.
    template<class T>
    void writeField(std::string_view field_name, const T& value);

    // Write a comment line.
    void writeComment(std::string_view comment);

  private:
    friend IndentedTextWriter;

    // Writes an opening brace '{' and increases the indent of the given IndentedTextWriter.
    explicit ScopedStructWriter(IndentedTextWriter& out);

    IndentedTextWriter& out_;
  };

  template<class T>
  void ScopedStructWriter::writeField(std::string_view field_name, const T& value)
  {
    out_.writeNewlineIfNeeded();
    out_.writeUnquoted(field_name);
    out_.writeUnquoted(": ");
    ValueWriter<T> value_writer{};
    value_writer(out_, value);
  }
}
