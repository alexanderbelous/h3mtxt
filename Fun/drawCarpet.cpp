#include <h3mtxt/Fun/drawCarpet.h>

#include <h3mtxt/Fun/Util.h>
#include <h3mtxt/Map/Map.h>

#include <stdexcept>

namespace h3m
{
  void drawCarpet(Map& map, TerrainType terrain_type, std::uint8_t terrain_sprite, std::uint8_t initial_mirroring)
  {
    if (map.tiles.size() != countTiles(map.basic_info))
    {
      throw std::runtime_error("drawCarpet(): wrong number of elements in map.tiles.");
    }
    // Clear all bits in @initial_mirroring except the 2 least significant ones.
    initial_mirroring &= 0b11;
    const std::uint32_t map_size = map.basic_info.map_size;
    for (std::uint32_t y = 0; y < map_size; ++y)
    {
      for (std::uint32_t x = 0; x < map_size; ++x)
      {
        Tile& tile = map.tiles[static_cast<std::size_t>(y) * map_size + x];
        tile.terrain_type = terrain_type;
        tile.terrain_sprite = terrain_sprite;

        const std::uint8_t mirror_x = (x % 2 == 0) ? 0 : 1;
        const std::uint8_t mirror_y = ((x / 2) % 2 != (y % 2)) ? 1 : 0;
        const std::uint8_t mirroring = mirror_x | (mirror_y << 1);
        //const std::uint8_t mirror_y = (y % 2 == 0) ? 0 : 1;
        //const std::uint8_t mirror_x = ((y / 2) % 2 != (x % 2)) ? 0 : 1;

        tile.mirroring &= (~0b11);
        tile.mirroring |= (mirroring ^ initial_mirroring);
      }
    }
  }

  void drawCarpetBlock(Map& map, TerrainType terrain_type, std::uint8_t terrain_sprite,
                       std::uint32_t x, std::uint32_t y, std::uint32_t z,
                       std::uint8_t initial_mirroring)
  {
    struct TileData
    {
      std::uint8_t x {};
      std::uint8_t y {};
      std::uint8_t mirroring {};
    };
    constexpr TileData kTilesToDraw[] = {
      {.x = 0, .y = 0, .mirroring = 0},
      {.x = 1, .y = 0, .mirroring = 1},
      {.x = 0, .y = 1, .mirroring = 2},
      {.x = 1, .y = 1, .mirroring = 3},
    };
    // Clear all bits in @initial_mirroring except the 2 least significant ones.
    initial_mirroring &= 0b11;
    for (const TileData& tile_data : kTilesToDraw)
    {
      if (Tile* tile = safeGetTile(map, x + tile_data.x, y + tile_data.y, z))
      {
        tile->terrain_type = terrain_type;
        tile->terrain_sprite = terrain_sprite;
        // Clear the 2 least significant bits.
        tile->mirroring &= (~0b11);
        // Set the 2 least significant bits.
        tile->mirroring |= (tile_data.mirroring ^ initial_mirroring);
      }
    }
  }
}
