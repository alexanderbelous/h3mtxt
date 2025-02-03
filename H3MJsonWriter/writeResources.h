#pragma once

#include <h3mtxt/Map/Resources.h>
#include <h3mtxt/H3MJsonWriter/H3MJsonWriter.h>

namespace Util_NS
{
  template<class T>
  struct JsonObjectWriter<h3m::Resources<T>>
  {
    void operator()(FieldsWriter& out, const h3m::Resources<T>& resources) const
    {
      out.writeField("wood", resources[h3m::ResourceType::Wood]);
      out.writeField("mercury", resources[h3m::ResourceType::Mercury]);
      out.writeField("ore", resources[h3m::ResourceType::Ore]);
      out.writeField("sulfur", resources[h3m::ResourceType::Sulfur]);
      out.writeField("crystal", resources[h3m::ResourceType::Crystal]);
      out.writeField("gems", resources[h3m::ResourceType::Gems]);
      out.writeField("gold", resources[h3m::ResourceType::Gold]);
    }
  };
}
