#include <h3mtxt/TextWriter/TextWriter.h>

#include <h3mtxt/TextWriter/ScopedStructWriter.h>

#include <iterator>
#include <ostream>

namespace Util_NS
{
  IndentedTextWriter::IndentedTextWriter(std::ostream& stream, std::size_t initial_indent):
    stream_(stream),
    indent_(initial_indent)
  {}

  void IndentedTextWriter::writeComment(std::string_view comment)
  {
    writeNewlineIfNeeded();
    // TODO: take care of newline characters in comments.
    stream_ << "# " << comment;
    needs_newline_ = true;
  }

  void IndentedTextWriter::writeString(std::string_view value)
  {
    writeNewlineIfNeeded();
    // TODO: escape some characters.
    stream_ << '"' << value << '"';
    needs_newline_ = true;
  }

  void IndentedTextWriter::increaseIndent()
  {
    indent_ += 2;
  }

  void IndentedTextWriter::decreaseIndent()
  {
    // This should never happen.
    if (indent_ < 2)
    {
      return;
    }
    indent_ -= 2;
  }

  void IndentedTextWriter::writeNewlineIfNeeded()
  {
    if (needs_newline_)
    {
      stream_ << '\n';
      std::fill_n(std::ostream_iterator<char>(stream_), indent_, ' ');
      needs_newline_ = false;
    }
  }

  void IndentedTextWriter::writeInt(std::intmax_t value)
  {
    writeNewlineIfNeeded();
    stream_ << value;
    needs_newline_ = true;
  }

  void IndentedTextWriter::writeUInt(std::uintmax_t value)
  {
    writeNewlineIfNeeded();
    stream_ << value;
    needs_newline_ = true;
  }

  ScopedStructWriter IndentedTextWriter::writeStruct()
  {
    return ScopedStructWriter{*this};
  }
}
