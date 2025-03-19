#include <h3mtxt/JsonWriter/ScopedObjectWriter.h>

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
      context_.endAggregate('}', true);
    }
    catch (...)
    {
    }
  }
}