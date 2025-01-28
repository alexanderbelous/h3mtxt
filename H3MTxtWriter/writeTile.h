#pragma once

#include <h3mtxt/Map/Tile.h>
#include <h3mtxt/H3MTxtWriter/getEnumString.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>

namespace Util_NS
{
  template<>
  struct StructWriter<h3m::Tile>
  {
    void operator()(FieldsWriter& out, const h3m::Tile& value) const
    {
      out.writeField("terrain_type", value.terrain_type);
      const std::string_view terrain_type_name = h3m::getEnumString(value.terrain_type);
      if (!terrain_type_name.empty())
      {
        out.writeComma();
        out.writeComment(terrain_type_name, false);
      }
      out.writeField("terrain_sprite", value.terrain_sprite);
      out.writeField("river_type", value.river_type);
      out.writeField("river_sprite", value.river_sprite);
      out.writeField("road_type", value.road_type);
      out.writeField("road_sprite", value.road_sprite);
      out.writeField("mirroring", value.mirroring);
    }
  };
}