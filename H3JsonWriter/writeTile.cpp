#include <h3mtxt/H3JsonWriter/API.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Tile.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::Tile>::operator()(FieldsWriter& out, const h3m::Tile& value) const
  {
    using Fields = h3m::FieldNames<h3m::Tile>;
    out.writeField(Fields::kTerrainType, value.terrain_type);
    const std::string_view terrain_type_name = h3m::getEnumString(value.terrain_type);
    if (!terrain_type_name.empty())
    {
      out.writeComma();
      out.writeComment(terrain_type_name, false);
    }
    out.writeField(Fields::kTerrainSprite, value.terrain_sprite);
    out.writeField(Fields::kRiverType, value.river_type);
    const std::string_view river_type_name = h3m::getEnumString(value.river_type);
    if (!river_type_name.empty())
    {
      out.writeComma();
      out.writeComment(river_type_name, false);
    }
    out.writeField(Fields::kRiverSprite, value.river_sprite);
    out.writeField(Fields::kRoadType, value.road_type);
    const std::string_view road_type_name = h3m::getEnumString(value.road_type);
    if (!road_type_name.empty())
    {
      out.writeComma();
      out.writeComment(road_type_name, false);
    }
    out.writeField(Fields::kRoadSprite, value.road_sprite);
    out.writeField(Fields::kMirroring, value.mirroring);
  }
}
