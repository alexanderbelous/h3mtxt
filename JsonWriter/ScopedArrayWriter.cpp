#include <h3mtxt/JsonWriter/ScopedArrayWriter.h>

namespace Medea_NS
{
  ScopedArrayWriterBase::ScopedArrayWriterBase(Detail_NS::JsonWriterContext& context, bool one_element_per_line):
    context_(context),
    one_element_per_line_(one_element_per_line)
  {
    context_.beginAggregate('[');
  }

  ScopedArrayWriterBase::~ScopedArrayWriterBase()
  {
    try
    {
      context_.endAggregate(']', one_element_per_line_);
    }
    catch (...)
    {
    }
  }

  void ScopedArrayWriterBase::writeComment(std::string_view comment)
  {
    context_.writeComment(comment, true);
  }
}