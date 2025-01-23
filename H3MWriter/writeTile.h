#pragma once

#include <h3mtxt/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/Tile.h>

namespace h3m
{
  template<>
  struct H3MWriter<Tile>
  {
    void operator()(std::ostream& stream, const Tile& value) const
    {
      writeData(stream, value.terrain_type);
      writeData(stream, value.terrain_sprite);
      writeData(stream, value.river_type);
      writeData(stream, value.river_sprite);
      writeData(stream, value.road_type);
      writeData(stream, value.road_sprite);
      writeData(stream, value.mirroring);
    }
  };
}
