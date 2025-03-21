#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/JsonWriter/ScopedObjectWriter.h>
#include <h3mtxt/Map/Resources.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::Resources>::operator()(FieldsWriter& out, const h3m::Resources& resources) const
  {
    using Fields = h3m::FieldNames<h3m::Resources>;
    out.writeField(Fields::kWood, resources[h3m::ResourceType::Wood]);
    out.writeField(Fields::kMercury, resources[h3m::ResourceType::Mercury]);
    out.writeField(Fields::kOre, resources[h3m::ResourceType::Ore]);
    out.writeField(Fields::kSulfur, resources[h3m::ResourceType::Sulfur]);
    out.writeField(Fields::kCrystal, resources[h3m::ResourceType::Crystal]);
    out.writeField(Fields::kGems, resources[h3m::ResourceType::Gems]);
    out.writeField(Fields::kGold, resources[h3m::ResourceType::Gold]);
  }
}
