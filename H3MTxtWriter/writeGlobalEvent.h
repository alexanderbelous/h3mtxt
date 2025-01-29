#pragma once

#include <h3mtxt/Map/GlobalEvent.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>
#include <h3mtxt/H3MTxtWriter/writeTimedEventBase.h>

namespace Util_NS
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
