#include <h3mtxt/TextWriter/ScopedStructWriter.h>

#include <ostream>

namespace Util_NS
{
  ScopedStructWriter::ScopedStructWriter(IndentedTextWriter& out):
    out_(out)
  {
    out_.writeNewlineIfNeeded();
    out_.stream_.put('{');
    out_.increaseIndent();
    out_.needs_newline_ = true;
  }

  ScopedStructWriter::~ScopedStructWriter()
  {
    try
    {
      out_.decreaseIndent();
      // TODO: don't write a newline if no fields have been written.
      out_.writeNewlineIfNeeded();
      out_.stream_.put('}');
      out_.needs_newline_ = true;
    }
    catch (...)
    {
    }
  }

  void ScopedStructWriter::writeComment(std::string_view comment, bool newline)
  {
    // If the last token was a comment, write a newline anyway.
    if (!newline && (last_token_ != Token::Comment))
    {
      // Otherwise, append a space and instruct IndentedTextWriter not to write a newline character.
      out_.stream_.put(' ');
      out_.needs_newline_ = false;
    }
    out_.writeComment(comment);
    last_token_ = Token::Comment;
  }

  void ScopedStructWriter::writeComma()
  {
    static constexpr std::string_view kCommaStr = ", ";
    if (needs_comma_)
    {
      if (last_token_ == Token::Comment)
      {
        out_.writeNewlineIfNeeded();
        out_.stream_.write(kCommaStr.data(), kCommaStr.size());
      }
      else
      {
        // last_token_ can only be Token::Field.
        out_.stream_.put(',');
      }
      needs_comma_ = false;
      last_token_ = Token::Comma;
    }
  }

  void ScopedStructWriter::writeFieldName(std::string_view field_name)
  {
    
    static constexpr std::string_view kSeparator = ": ";
    // Write a comma, if needed.
    writeComma();
    out_.writeString(field_name);
    out_.stream_.write(kSeparator.data(), kSeparator.size());
    out_.needs_newline_ = false;
  }
}
