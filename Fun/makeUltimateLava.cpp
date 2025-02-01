#include <h3mtxt/Fun/makeUltimateLava.h>

#include <h3mtxt/Map/Map.h>

#include <random>

namespace h3m
{
  namespace {
    constexpr bool isEligibleLavaTile(const h3m::Tile& tile) noexcept
    {
      // Lava sprites [49; 72] are "pure", i.e. they don't border other terrain types.
      return tile.terrain_type == h3m::TerrainType::Lava &&
             tile.terrain_sprite >= 49 &&
             tile.terrain_sprite <= 72;
    }
  }

  // Replaces the sprites of "pure" Lava tiles with random animated Lava sprites.
  void makeUltimateLava(h3m::Map& map)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    // Sprites [65; 70] look like animated Lava tiles.
    std::uniform_int_distribution<> distrib_sprite(65, 70);
    std::uniform_int_distribution<> distrib_mirror(0, 3);
    for (h3m::Tile& tile : map.tiles)
    {
      if (isEligibleLavaTile(tile))
      {
        tile.terrain_sprite = distrib_sprite(gen);
        // Only overwrite the 2 bits for terrain mirroring, don't modify anything else
        // (e.g., roads, rivers).
        tile.mirroring &= (~std::uint8_t{ 0x03 });
        tile.mirroring |= distrib_mirror(gen);
      }
    }
  }
}