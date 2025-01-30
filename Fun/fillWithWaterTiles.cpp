#include <h3mtxt/Fun/fillWithWaterTiles.h>
#include <h3mtxt/Map/Map.h>

#include <random>

namespace h3m
{
  void fillWithWaterTiles(Map& map)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    // Sprites [20; 32] look like non-coastal Water tiles.
    std::uniform_int_distribution<> distrib(20, 32);

    // Set random water tiles.
    for (Tile& tile : map.tiles)
    {
      tile.terrain_type = TerrainType::Water;
      tile.terrain_sprite = distrib(gen);
      // Note: we can apply random mirroring as well. The official Map Editor doesn't
      // apply mirroring to non-coastal Water tiles (and switches it off if you modify a
      // water region with mirrored non-coastal tiles).
      tile.mirroring = 0;
    }
  }
}
