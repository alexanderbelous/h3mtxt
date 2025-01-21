#include <h3mtxt/TextWriter/ScopedArrayWriter.h>

#include <ostream>

namespace Util_NS
{
  ScopedArrayWriterBase::ScopedArrayWriterBase(IndentedTextWriter& out, bool one_element_per_line):
    out_(out),
    one_element_per_line_(one_element_per_line)
  {
    out_.writeNewlineIfNeeded();
    out_.stream_.put('[');
    // This is not quite accurate - if last_token_ == Token::Nothing in ~ScopedArrayWriter(),
    // no newline will be written between the brackets.
    if (one_element_per_line_)
    {
      out_.needs_newline_ = true;
    }
    out_.increaseIndent();
  }

  ScopedArrayWriterBase::~ScopedArrayWriterBase()
  {
    try
    {
      out_.decreaseIndent();
      // A newline is needed if:
      // a) The last token was a comment.
      // b) The last token was an element and there should be 1 element per line.
      if ((last_token_ == Token::Comment) || (last_token_ == Token::Element && one_element_per_line_))
      {
        out_.needs_newline_ = true;
        out_.writeNewlineIfNeeded();
      }      
      out_.stream_.put(']');
      out_.needs_newline_ = true;
    }
    catch (...)
    {
    }
  }

  void ScopedArrayWriterBase::writeComment(std::string_view comment)
  {
    // Write a comma if needed.
    if (last_token_ == Token::Element)
    {
      out_.stream_.put(',');
    }
    else if (last_token_ != Token::Nothing)
    {
      out_.needs_newline_ = true;
    }
    out_.writeComment(comment);
    last_token_ = Token::Comment;
  }

  void ScopedArrayWriterBase::beforeWriteElement()
  {
    // Write a comma if needed.
    if (last_token_ == Token::Element)
    {
      out_.stream_.put(',');
      // Append a space if the next element will be written on the same line.
      if (!one_element_per_line_)
      {
        out_.stream_.put(' ');
      }
    }
    // Write/suppress a newline if needed.
    if (!one_element_per_line_)
    {
      if (last_token_ == Token::Comment)
      {
        // Write a newline anyway if the previous line was a comment.
        out_.writeNewlineIfNeeded();
      }
      out_.needs_newline_ = false;
    }
  }

  void ScopedArrayWriterBase::afterWriteElement()
  {
    last_token_ = Token::Element;
    if (!one_element_per_line_)
    {
      out_.needs_newline_ = false;
    }
  }
}
