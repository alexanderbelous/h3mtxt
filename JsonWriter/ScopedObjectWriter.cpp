#include <h3mtxt/JsonWriter/ScopedObjectWriter.h>

#include <ostream>

namespace Medea_NS
{
  ScopedObjectWriter::ScopedObjectWriter(const Detail_NS::JsonWriterContext& context):
    context_(context)
  {
    context_.writeNewlineIfNeeded();
    context_.stream_.put('{');
    context_.increaseIndent();
    context_.needs_newline_ = true;
  }

  ScopedObjectWriter::~ScopedObjectWriter()
  {
    try
    {
      flushComments();
      context_.decreaseIndent();
      if (has_fields_ || has_comments_)
      {
        context_.writeNewlineIfNeeded();
      }
      context_.stream_.put('}');
    }
    catch (...)
    {
    }
  }

  void ScopedObjectWriter::writeComment(std::string_view comment, bool newline)
  {
    if (comment.empty())
    {
      return;
    }
    if (!comment_.empty())
    {
      comment_.push_back('\n');
    }
    else
    {
      is_inline_comment_ = !newline;
    }
    comment_.append(comment);
  }

  void ScopedObjectWriter::writeFieldName(std::string_view field_name)
  {
    static constexpr std::string_view kSeparator = ": ";

    if (has_fields_)
    {
      context_.stream_.put(',');
    }
    flushComments();
    context_.writeString(field_name);
    context_.stream_.write(kSeparator.data(), kSeparator.size());
    context_.needs_newline_ = false;
    has_fields_ = true;
  }

  void ScopedObjectWriter::flushComments()
  {
    if (comment_.empty())
    {
      return;
    }
    // Append a space unless no field has been written for this object yet.
    if (is_inline_comment_ && has_fields_)
    {
      context_.stream_.put(' ');
      // Instruct JsonWriterContext not to write a newline character.
      context_.needs_newline_ = false;
    }
    context_.writeComment(comment_);
    comment_.clear();
    is_inline_comment_ = false;
    has_comments_ = true;
  }
}
