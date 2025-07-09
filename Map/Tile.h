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
    TerrainType terrain_type {};
    std::uint8_t terrain_sprite {};
    RiverType river_type {};
    // For normal RiverTypes: (0-3 corners, 4 + , 5 6 T, 7 8 |-, 9 10 | , 11 12--)
    std::uint8_t river_sprite {};
    RoadType road_type {};
    // For normal RoadTypes: (0-5 corners, 6 7 |-, 8 9 T, 10 11 | , 12 13 --, 14 ', 15 -, 16 +)
    // TODO: Undocumented stuff: Similar to rivers, but note that roads are rendered "half-tile" below the actual tile.
    std::uint8_t road_sprite {};
    // 8-bit bitmask storing flags for this tile.
    // See Map/Constants/TileFlag.h for the details for each flag.
    TileFlags flags {};
  };

  // Undocumented stuff:
  // Normally, RiverType should be within [0; 4], but the game has well-defined behavior for some other values as well.
  // Most importantly:
  // * values 15 and 17 allow drawing sprites of uncharted territory instead of river sprites.
  // * values [246; 255] allow drawing terrain sprites instead of river sprites. For example, you can have a Snow tile
  //   that looks like Grass.
  // See the switch statement below for the full list.
  //
  // Note that the Map Editor does not support RiverTypes outside of [0; 4] (it will report "Invalid or corrupt map file").
  //
  // Returns the number of "usable" sprites for the specified RiverType.
  // This is an extended version of countSprites().
  //
  // \param river_type - (possibly extended) type of the river.
  // \return the number N of usable sprites for @river_type..
  //         The values [0; N) are safe to use in Tile::river_sprite for @river_type.
  constexpr std::uint8_t countHexedSprites(RiverType river_type) noexcept
  {
    const std::uint8_t river_type_idx = static_cast<std::uint8_t>(river_type);
    switch (river_type_idx)
    {
    // [0; 4] are normal river sprites (0 is "no river").
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
      return countSprites(river_type);
    // [6; 8] are road sprites
    case 6:
    case 7:
    case 8:
      return countSprites(static_cast<RoadType>(river_type_idx - 5));
    // 9 is the "black marble" around the map when playing the game.
    case 9:
      return 36;
    // 10 is the hero's path (green/red arrows and the cross) on the Adventure Map.
    case 10:
      return 50;
    // 11, 12 and 14 are the gem in the corners of the window around the Adventure Map.
    case 11:
    case 12:
    case 14:
      return 8;
    // 15 and 17 are uncharted territory.
    case 15:
      return 4;
    case 17:
      return 34;
    // 22 is creatures (partial sprite)
    case 22:
      return 128;
    // [246; 255] are terrain sprites.
    case 246:
    case 247:
    case 248:
    case 249:
    case 250:
    case 251:
    case 252:
    case 253:
    case 254:
    case 255:
      return countSprites(static_cast<TerrainType>(river_type_idx - 246));
    // No sprites for other values of RiverType.
    default:
      return 0;
    // TODO: 56 or 57 to 64 are flags; 65-72 as well. probably up to 88
    }
  }
}
