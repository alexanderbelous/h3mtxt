#pragma once

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Resources.h>
#include <h3mtxt/H3MJsonWriter/H3MJsonWriter.h>

namespace Util_NS
{
  template<class T>
  struct JsonObjectWriter<h3m::Resources<T>>
  {
    void operator()(FieldsWriter& out, const h3m::Resources<T>& resources) const
    {
      using Fields = h3m::FieldNames<h3m::Resources<T>>;
      out.writeField(Fields::kWood, resources[h3m::ResourceType::Wood]);
      out.writeField(Fields::kMercury, resources[h3m::ResourceType::Mercury]);
      out.writeField(Fields::kOre, resources[h3m::ResourceType::Ore]);
      out.writeField(Fields::kSulfur, resources[h3m::ResourceType::Sulfur]);
      out.writeField(Fields::kCrystal, resources[h3m::ResourceType::Crystal]);
      out.writeField(Fields::kGems, resources[h3m::ResourceType::Gems]);
      out.writeField(Fields::kGold, resources[h3m::ResourceType::Gold]);
    }
  };
}
