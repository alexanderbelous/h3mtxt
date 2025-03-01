#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/Map/GlobalEvent.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::GlobalEvent>::operator()(FieldsWriter& out, const h3m::GlobalEvent& global_event) const
  {
    printTimedEventBase(out, global_event);
  }
}
