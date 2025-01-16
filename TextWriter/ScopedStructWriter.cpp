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

  void ScopedStructWriter::writeComment(std::string_view comment)
  {
    out_.writeComment(comment);
  }
}
