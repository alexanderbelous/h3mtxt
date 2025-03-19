#include <h3mtxt/JsonWriter/ScopedArrayWriter.h>

#include <ostream>

namespace Medea_NS
{
  ScopedArrayWriterBase::ScopedArrayWriterBase(Detail_NS::JsonWriterContext& context, bool one_element_per_line):
    context_(context),
    one_element_per_line_(one_element_per_line)
  {
    context_.beginAggregate('[');
    context_.needs_newline_ = one_element_per_line_;
  }

  ScopedArrayWriterBase::~ScopedArrayWriterBase()
  {
    try
    {
      // A newline is needed if:
      // a) The last token was a comment.
      // b) The last token was an element and there should be 1 element per line.
      context_.needs_newline_ = context_.hasUnflushedComment() ||
                                (has_elements_ && one_element_per_line_);
      context_.endAggregate(']');
      // TODO: remove?
      context_.needs_newline_ = true;
    }
    catch (...)
    {
    }
  }

  void ScopedArrayWriterBase::writeComment(std::string_view comment)
  {
    context_.lazyWriteComment(comment, true);
  }

  void ScopedArrayWriterBase::beforeWriteElement()
  {
    // True if this element is printed after a comment, false otherwise.
    const bool after_comment = context_.hasUnflushedComment();
    // Write a comma if needed.
    if (has_elements_)
    {
      context_.stream_.put(',');
      // Append a space if the next element will be written on the same line.
      if (!one_element_per_line_ && !after_comment)
      {
        context_.stream_.put(' ');
      }
    }
    // Flush comments.
    context_.flushComments();
    // Write/suppress a newline if needed.
    if (!one_element_per_line_)
    {
      if (after_comment)
      {
        // Write a newline anyway if the previous line was a comment.
        context_.needs_newline_ = true;
        context_.writeNewlineIfNeeded();
      }
      context_.needs_newline_ = false;
    }
  }

  void ScopedArrayWriterBase::afterWriteElement()
  {
    context_.needs_newline_ = one_element_per_line_;
    has_elements_ = true;
  }
}
