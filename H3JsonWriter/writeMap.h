#pragma once

#include <h3mtxt/JsonWriter/JsonValueWriter.h>
#include <h3mtxt/Map/Map.h>

namespace Medea_NS
{
  template<>
  struct JsonObjectWriter<h3m::Map>
  {
    void operator()(FieldsWriter& out, const h3m::Map& value) const;
  };
}
