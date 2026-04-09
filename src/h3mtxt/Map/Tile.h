#pragma once

#include <h3mtxt/Map/Constants/TerrainType.h>
#include <h3mtxt/Map/Constants/TileFlag.h>
#include <h3mtxt/Map/Constants/RoadType.h>
#include <h3mtxt/Map/Constants/RiverType.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>

#include <cstdint>

namespace h3m
{
  // Represents a tile on the Adventure Map.
  struct Tile
  {
    constexpr bool operator==(const Tile&) const noexcept = default;

    TerrainType terrain_type {};
    std::uint8_t terrain_sprite {};
    RiverType river_type = RiverType::None;
    // 0-3 corners, 4 + , 5 6 T, 7 8 |-, 9 10 | , 11 12--
    std::uint8_t river_sprite = 0;
    RoadType road_type = RoadType::None;
    // 0-5 corners, 6 7 |-, 8 9 T, 10 11 | , 12 13 --, 14 ', 15 -, 16 +
    // Note that road sprites are rendered "half-tile" below the actual tile.
    std::uint8_t road_sprite = 0;
    // 8-bit bitmask storing flags for this tile.
    // See Map/Constants/TileFlag.h for the details for each flag.
    TileFlags flags {};
  };
}
