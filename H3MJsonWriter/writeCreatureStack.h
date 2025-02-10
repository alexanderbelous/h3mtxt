#pragma once

#include <h3mtxt/H3MJsonWriter/getEnumString.h>
#include <h3mtxt/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/Map/CreatureStack.h>

namespace Medea_NS
{
  template<>
  struct JsonObjectWriter<h3m::CreatureStack>
  {
    void operator()(FieldsWriter& out, const h3m::CreatureStack& creature_stack) const
    {
      out.writeField("type", creature_stack.type);
      if (auto enum_str = h3m::getEnumString(creature_stack.type); !enum_str.empty())
      {
        out.writeComma();
        out.writeComment(enum_str, false);
      }
      out.writeField("count", creature_stack.count);
    }
  };
}
