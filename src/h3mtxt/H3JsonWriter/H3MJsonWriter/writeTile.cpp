#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/Tile.h>
#include <h3mtxt/Medea/Medea.h>

namespace Medea_NS
{
  template<>
  void JsonObjectWriter<h3m::Tile>::operator()(FieldsWriter& out, const h3m::Tile& value) const
  {
    using Fields = h3json::FieldNames<h3m::Tile>;
    out.writeField(Fields::kTerrainType, value.terrain_type);
    out.writeField(Fields::kTerrainSprite, value.terrain_sprite);
    out.writeField(Fields::kRiverType, value.river_type);
    out.writeField(Fields::kRiverSprite, value.river_sprite);
    out.writeField(Fields::kRoadType, value.road_type);
    out.writeField(Fields::kRoadSprite, value.road_sprite);
    out.writeField(Fields::kFlags, value.flags);
  }
}
