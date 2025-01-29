#include <h3mtxt/TextWriter/ScopedArrayWriter.h>

#include <ostream>

namespace Util_NS
{
  ScopedArrayWriterBase::ScopedArrayWriterBase(const Detail_NS::JsonWriterContext& context, bool one_element_per_line):
    context_(context),
    one_element_per_line_(one_element_per_line)
  {
    context_.writeNewlineIfNeeded();
    context_.stream_.put('[');
    // This is not quite accurate - if last_token_ == Token::Nothing in ~ScopedArrayWriter(),
    // no newline will be written between the brackets.
    if (one_element_per_line_)
    {
      context_.needs_newline_ = true;
    }
    context_.increaseIndent();
  }

  ScopedArrayWriterBase::~ScopedArrayWriterBase()
  {
    try
    {
      context_.decreaseIndent();
      // A newline is needed if:
      // a) The last token was a comment.
      // b) The last token was an element and there should be 1 element per line.
      if ((last_token_ == Token::Comment) || (last_token_ == Token::Element && one_element_per_line_))
      {
        context_.needs_newline_ = true;
        context_.writeNewlineIfNeeded();
      }      
      context_.stream_.put(']');
      context_.needs_newline_ = true;
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
      context_.stream_.put(',');
    }
    else if (last_token_ != Token::Nothing)
    {
      context_.needs_newline_ = true;
    }
    context_.writeComment(comment);
    last_token_ = Token::Comment;
  }

  void ScopedArrayWriterBase::beforeWriteElement()
  {
    // Write a comma if needed.
    if (last_token_ == Token::Element)
    {
      context_.stream_.put(',');
      // Append a space if the next element will be written on the same line.
      if (!one_element_per_line_)
      {
        context_.stream_.put(' ');
      }
    }
    // Write/suppress a newline if needed.
    if (!one_element_per_line_)
    {
      if (last_token_ == Token::Comment)
      {
        // Write a newline anyway if the previous line was a comment.
        context_.writeNewlineIfNeeded();
      }
      context_.needs_newline_ = false;
    }
  }

  void ScopedArrayWriterBase::afterWriteElement()
  {
    last_token_ = Token::Element;
    context_.needs_newline_ = one_element_per_line_;
  }
}
