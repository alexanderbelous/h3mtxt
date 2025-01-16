#include <h3mtxt/TextWriter/ScopedArrayWriter.h>

#include <ostream>

namespace Util_NS
{
  ScopedArrayWriterBase::ScopedArrayWriterBase(IndentedTextWriter& out):
    out_(out)
  {
    out_.writeNewlineIfNeeded();
    out_.stream_.put('[');
    // This is not quite accurate - if has_elements_or_comments_ == false in ~ScopedArrayWriter(),
    // no newline will be written between the brackets.
    out_.needs_newline_ = true;
    out_.increaseIndent();
  }

  ScopedArrayWriterBase::~ScopedArrayWriterBase()
  {
    try
    {
      out_.decreaseIndent();
      if (has_elements_or_comments_)
      {
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
    writeCommaIfNeeded();
    out_.writeComment(comment);
    has_elements_or_comments_ = true;
  }

  void ScopedArrayWriterBase::writeCommaIfNeeded()
  {
    if (need_comma_)
    {
      out_.stream_.put(',');
      need_comma_ = false;
    }
  }
}
