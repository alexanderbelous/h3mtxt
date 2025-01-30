#pragma once

#include <h3mtxt/Map/Map.h>

namespace h3m
{
  // Access the specified tile.
  // \param map - input map.
  // \param x - X coordinate of the tile.
  // \param y - Y coordinate of the tile.
  // \param z - Z coordinate of the tile.
  // \return the tile (x, y, z) or nullptr if (x, y, z) doesn't refer to an existing tile.
  inline Tile* safeGetTile(Map& map, std::uint32_t x, std::uint32_t y, std::uint32_t z = 0)
  {
    const std::uint32_t map_size = map.basic_info.map_size;
    if (x >= map_size || y >= map_size || ((z == 1) && !map.basic_info.has_two_levels))
    {
      return nullptr;
    }
    const std::size_t tile_idx = (static_cast<std::size_t>(z) * map_size + y) * map_size + x;
    return &map.tiles[tile_idx];
  }
}
