#pragma once

#include <h3mtxt/Map/CreatureStack.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>

namespace Util_NS
{
  template<>
  struct StructWriter<h3m::CreatureStack>
  {
    void operator()(FieldsWriter& out, const h3m::CreatureStack& guardians) const
    {
      out.writeField("type", guardians.type);
      out.writeField("count", guardians.count);
    }
  };
}
