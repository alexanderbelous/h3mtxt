#pragma once

#include <h3mtxt/Map/Tile.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>

namespace Util_NS
{
  template<>
  struct StructWriter<h3m::Tile>
  {
    void operator()(FieldsWriter& out, const h3m::Tile& value) const
    {
      out.writeField("terrain_type", value.terrain_type);
      out.writeField("terrain_sprite", value.terrain_sprite);
      out.writeField("river_type", value.river_type);
      out.writeField("river_sprite", value.river_sprite);
      out.writeField("road_type", value.road_type);
      out.writeField("road_sprite", value.road_sprite);
      out.writeField("mirroring", value.mirroring);
    }
  };
}