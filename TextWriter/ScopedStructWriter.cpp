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

  void ScopedStructWriter::writeFieldName(std::string_view field_name)
  {
    static constexpr std::string_view kSeparator = ": ";
    out_.writeNewlineIfNeeded();
    out_.stream_.write(field_name.data(), field_name.size());
    out_.stream_.write(kSeparator.data(), kSeparator.size());
  }
}
