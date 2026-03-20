#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/Tile.h>

namespace h3m
{
  void H3MWriter::writeData(const Tile& value) const
  {
    writeData(value.terrain_type);
    writeData(value.terrain_sprite);
    writeData(value.river_type);
    writeData(value.river_sprite);
    writeData(value.road_type);
    writeData(value.road_sprite);
    writeData(value.flags);
  }
}
