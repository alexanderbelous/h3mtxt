#include <h3mtxt/Fun/fillWithTerrain.h>
#include <h3mtxt/Map/Map.h>

#include <random>

namespace h3m
{
  namespace
  {
    struct SpritesRange
    {
      std::uint8_t first {};
      std::uint8_t last {};
    };

    // Returns the range of non-decorative "pure" sprites for the specified TerrainType.
    // TODO: the Editor probably has a different definition of "decorative" sprites at
    // least for some terrain types.
    constexpr SpritesRange getPureTerrainSpritesRange(TerrainType terrain_type)
    {
      switch (terrain_type)
      {
      case TerrainType::Dirt:
        return SpritesRange{ .first = 21, .last = 28 };
      case TerrainType::Sand:
        return SpritesRange{ .first = 0, .last = 9 };
      case TerrainType::Grass:
        return SpritesRange{ .first = 49, .last = 63 };
      case TerrainType::Snow:
        return SpritesRange{ .first = 49, .last = 56 };
      case TerrainType::Swamp:
        return SpritesRange{ .first = 49, .last = 63 };
      case TerrainType::Rough:
        return SpritesRange{ .first = 49, .last = 60 };
      case TerrainType::Subterranean:
        return SpritesRange{ .first = 49, .last = 63 };
      case TerrainType::Lava:
        return SpritesRange{ .first = 49, .last = 62 };
      case TerrainType::Water:
        return SpritesRange{ .first = 20, .last = 32 };
      case TerrainType::Rock:
        // Technically it's [0; 7], but they all look the same.
        return SpritesRange{ .first = 0, .last = 0 };
      default:
        throw std::runtime_error("getPureTerrainSpritesRange(): invalid terrain_type.");
      }
    }

    // Checks if mirroring is OK to apply for tiles of the specified TerrainType.
    // The Editor doesn't apply mirroring for "pure" tiles, i.e. tiles that aren't neighbors
    // with tiles of different TerrainType(s). However, it's perfectly safe to do so, and
    // it can be aesthetically pleasant since it increases the set of visually different
    // sprites.
    // \param terrain_type - type of the terrain.
    // \return true if mirroring is OK to apply for @terrain_type, false otherwise.
    constexpr bool shouldApplyMirroring(TerrainType terrain_type)
    {
      switch (terrain_type)
      {
      // Don't apply mirroring for Water tiles - it will make water flow north for vertically
      // mirrored tiles, which is a bit weird.
      case TerrainType::Water:
      // Don't apply mirroring for Rock tiles - they are just black squares.
      case TerrainType::Rock:
        return false;
      default:
        return true;
      }
    }
  }

  void fillWithTerrain(Map& map, TerrainType terrain_type)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    const SpritesRange sprites_range = getPureTerrainSpritesRange(terrain_type);
    const bool should_apply_mirroring = shouldApplyMirroring(terrain_type);
    std::uniform_int_distribution<> distrib(sprites_range.first, sprites_range.last);
    std::uniform_int_distribution<> distrib_mirroring(0, 3);
    for (Tile& tile : map.tiles)
    {
      tile.terrain_type = terrain_type;
      tile.terrain_sprite = static_cast<std::uint8_t>(distrib(gen));
      tile.mirroring &= (~0b11);
      if (should_apply_mirroring)
      {
        tile.mirroring |= static_cast<std::uint8_t>(distrib_mirroring(gen));
      }
    }
  }
}
