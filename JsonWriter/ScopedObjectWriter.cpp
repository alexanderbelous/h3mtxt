#include <h3mtxt/JsonWriter/ScopedObjectWriter.h>

#include <ostream>

namespace Medea_NS
{
  ScopedObjectWriter::ScopedObjectWriter(Detail_NS::JsonWriterContext& context):
    context_(context)
  {
    context_.beginAggregate('{');
  }

  ScopedObjectWriter::~ScopedObjectWriter()
  {
    try
    {
      context_.needs_newline_ = has_fields_ || context_.hasUnflushedComment();
      context_.endAggregate('}');
    }
    catch (...)
    {
    }
  }

  void ScopedObjectWriter::writeComment(std::string_view comment, bool newline)
  {
    context_.lazyWriteComment(comment, newline);
  }

  void ScopedObjectWriter::writeFieldName(std::string_view field_name)
  {
    static constexpr std::string_view kSeparator = ": ";

    if (has_fields_)
    {
      context_.stream_.put(',');
    }
    context_.flushComments();
    context_.writeString(field_name);
    context_.stream_.write(kSeparator.data(), kSeparator.size());
    context_.needs_newline_ = false;
    has_fields_ = true;
    // FIXME: hack
    context_.has_members_in_scope_ = true;
  }
}
