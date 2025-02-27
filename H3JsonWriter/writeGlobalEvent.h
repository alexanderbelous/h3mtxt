#pragma once

#include <h3mtxt/Map/GlobalEvent.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/writeTimedEventBase.h>

namespace Medea_NS
{
  template<>
  struct JsonObjectWriter<h3m::GlobalEvent>
  {
    void operator()(FieldsWriter& out, const h3m::GlobalEvent& global_event) const
    {
      printTimedEventBase(out, global_event);
    }
  };
}
