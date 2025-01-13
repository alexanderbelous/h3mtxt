#pragma once

#include <h3mparser/Map/Constants/TerrainType.h>
#include <h3mparser/Map/Constants/RoadType.h>
#include <h3mparser/Map/Constants/RiverType.h>

#include <cstdint>

namespace h3m
{

struct Tile
{
  TerrainType terrain_type {};
  // Object subclass.
  // TODO: h3mlib claims that there are some unused tiles, see
  //     homm3tools/h3m/h3mlib/h3m_structures/tiles/h3m_tile.h
  std::uint8_t terrain_sprite {};
  RiverType river_type {};
  // (0-3 corners, 4 + , 5 6 T, 7 8 |-, 9 10 | , 11 12--)
  std::uint8_t river_sprite {};
  RoadType road_type {};
  // (0-5 corners, 6 7 |-, 8 9 T, 10 11 | , 12 13 --, 14 ', 15 -, 16 +)
  std::uint8_t road_sprite {};
  // Bitfield: horizontal terrain, vertical terrain, horizontal river, vertical river,
  //           horizontal road, vertical road, coast, favorable winds
  std::uint8_t mirroring {};
};

}