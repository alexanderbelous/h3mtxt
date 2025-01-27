#include <h3mtxt/TextWriter/TextWriter.h>

#include <h3mtxt/TextWriter/ScopedStructWriter.h>

#include <iterator>
#include <ostream>
#include <ranges>

namespace Util_NS
{
  IndentedTextWriter::IndentedTextWriter(std::ostream& stream, std::size_t initial_indent):
    stream_(stream),
    indent_(initial_indent)
  {}

  void IndentedTextWriter::writeComment(std::string_view comment)
  {
    constexpr std::string_view kCommentPrefix = "# ";

    if (comment.empty())
    {
      writeNewlineIfNeeded();
      stream_.put('#');
      needs_newline_ = true;
      return;
    }
    for (auto part : std::views::split(comment, '\n'))
    {
      writeNewlineIfNeeded();
      const std::string_view part_str(part.begin(), part.end());
      stream_.write(kCommentPrefix.data(), kCommentPrefix.size());
      stream_.write(part_str.data(), part_str.size());
      needs_newline_ = true;
    }
  }

  void IndentedTextWriter::writeString(std::string_view value)
  {
    writeNewlineIfNeeded();
    // TODO: escape some characters.
    stream_ << '"' << value << '"';
    needs_newline_ = true;
  }

  void IndentedTextWriter::writeBool(bool value)
  {
    writeNewlineIfNeeded();
    stream_ << (value ? "true" : "false");
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
