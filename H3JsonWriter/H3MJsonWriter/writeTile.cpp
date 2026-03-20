#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/Tile.h>
#include <h3mtxt/Medea/Medea.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::Tile>::operator()(FieldsWriter& out, const h3m::Tile& value) const
  {
    using Fields = h3json::FieldNames<h3m::Tile>;
    out.writeField(Fields::kTerrainType, value.terrain_type);
    if (std::string_view enum_str = h3m::getEnumString(value.terrain_type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kTerrainSprite, value.terrain_sprite);
    out.writeField(Fields::kRiverType, value.river_type);
    if (std::string_view enum_str = h3m::getEnumString(value.river_type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kRiverSprite, value.river_sprite);
    out.writeField(Fields::kRoadType, value.road_type);
    if (std::string_view enum_str = h3m::getEnumString(value.road_type); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kRoadSprite, value.road_sprite);
    out.writeField(Fields::kFlags, value.flags);
  }
}
