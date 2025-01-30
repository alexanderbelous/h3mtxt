#include <h3mtxt/Fun/fakeIslands.h>
#include <h3mtxt/Fun/Util.h>
#include <h3mtxt/Map/Map.h>

#include <iterator>
#include <random>
#include <stdexcept>

namespace h3m
{
  namespace
  {
    enum class WaterSpriteGroup : std::uint8_t
    {
      CoastWN,          // Coast to the West and to the North of the tile.
      CoastW,           // Coast to the West of the tile.
      CoastN,           // Coast to the North of the tile.
      CoastCornerSE,    // Coast in the SouthEastern corner of the tile.
      CoastDiagonalNW,  // Diagonal coast NorthWest of the tile.
      NoCoast           // No coast.
    };

    class WaterSpriteDistribution
    {
      static constexpr std::uint8_t kCornerCoastSprites[] = { 12, 13, 14, 15, 18, 19 };

    public:
      WaterSpriteDistribution():
        distrib_coast_corner_se_(0, std::size(kCornerCoastSprites) - 1)
      {}

      // Generates a random Water sprite from the specified group.
      template<class Generator>
      std::uint8_t operator()(WaterSpriteGroup sprite_group, Generator& g)
      {
        switch (sprite_group)
        {
        case WaterSpriteGroup::CoastWN:
          return static_cast<std::uint8_t>(distrib_coast_wn_(g));
        case WaterSpriteGroup::CoastW:
          return static_cast<std::uint8_t>(distrib_coast_w_(g));
        case WaterSpriteGroup::CoastN:
          return static_cast<std::uint8_t>(distrib_coast_n_(g));
        case WaterSpriteGroup::CoastCornerSE:
          return kCornerCoastSprites[distrib_coast_corner_se_(g)];
        case WaterSpriteGroup::CoastDiagonalNW:
          return static_cast<std::uint8_t>(distrib_coast_diagonal_nw_(g));
        case WaterSpriteGroup::NoCoast:
          return static_cast<std::uint8_t>(distrib_no_coast_(g));
        default:
          throw std::runtime_error("WaterTileGenerator: invalid sprite_group.");
        }
      }

    private:
      std::uniform_int_distribution<unsigned short> distrib_coast_wn_ { 0, 3 };
      std::uniform_int_distribution<unsigned short> distrib_coast_w_ { 4, 7 };
      std::uniform_int_distribution<unsigned short> distrib_coast_n_ { 8, 11 };
      std::uniform_int_distribution<unsigned short> distrib_coast_corner_se_;
      std::uniform_int_distribution<unsigned short> distrib_coast_diagonal_nw_ { 16, 17 };
      std::uniform_int_distribution<unsigned short> distrib_no_coast_ { 20, 32 };
      
    };

    struct TileData
    {
      std::uint8_t x {};
      std::uint8_t y {};
      WaterSpriteGroup sprite {};
      std::uint8_t mirroring {};
    };
  }

  void drawFakeIsland(Map& map, std::uint32_t x, std::uint32_t y)
  {
    constexpr TileData kTilesToDraw[] = {
      {.x = 0, .y = 1, .sprite = WaterSpriteGroup::CoastCornerSE, .mirroring = 0},
      {.x = 0, .y = 2, .sprite = WaterSpriteGroup::CoastCornerSE, .mirroring = 2},

      {.x = 1, .y = 0, .sprite = WaterSpriteGroup::CoastCornerSE, .mirroring = 0},
      {.x = 1, .y = 1, .sprite = WaterSpriteGroup::CoastDiagonalNW, .mirroring = 3},
      {.x = 1, .y = 2, .sprite = WaterSpriteGroup::CoastDiagonalNW, .mirroring = 1},
      {.x = 1, .y = 3, .sprite = WaterSpriteGroup::CoastCornerSE, .mirroring = 2},

      {.x = 2, .y = 0, .sprite = WaterSpriteGroup::CoastCornerSE, .mirroring = 1},
      {.x = 2, .y = 1, .sprite = WaterSpriteGroup::CoastDiagonalNW, .mirroring = 2},
      {.x = 2, .y = 2, .sprite = WaterSpriteGroup::CoastDiagonalNW, .mirroring = 0},
      {.x = 2, .y = 3, .sprite = WaterSpriteGroup::CoastCornerSE, .mirroring = 3},

      {.x = 3, .y = 1, .sprite = WaterSpriteGroup::CoastCornerSE, .mirroring = 1},
      {.x = 3, .y = 2, .sprite = WaterSpriteGroup::CoastCornerSE, .mirroring = 3},
    };
    std::random_device rd;
    std::mt19937 gen(rd());
    WaterSpriteDistribution distrib;

    for (const TileData& tile_data : kTilesToDraw)
    {
      if (Tile* tile = safeGetTile(map, x + tile_data.x, y + tile_data.y))
      {
        tile->terrain_type = TerrainType::Water;
        tile->terrain_sprite = distrib(tile_data.sprite, gen);
        tile->mirroring = tile_data.mirroring;
      }
    }
  }

  void drawFakeMiniIsland(Map& map, std::uint32_t x, std::uint32_t y)
  {
    constexpr TileData kTilesToDraw[] = {
      {.x = 0, .y = 0, .sprite = WaterSpriteGroup::CoastCornerSE, .mirroring = 0},
      {.x = 1, .y = 0, .sprite = WaterSpriteGroup::CoastCornerSE, .mirroring = 1},
      {.x = 0, .y = 1, .sprite = WaterSpriteGroup::CoastCornerSE, .mirroring = 2},
      {.x = 1, .y = 1, .sprite = WaterSpriteGroup::CoastCornerSE, .mirroring = 3}
    };
    std::random_device rd;
    std::mt19937 gen(rd());
    WaterSpriteDistribution distrib;

    for (const TileData& tile_data : kTilesToDraw)
    {
      if (Tile* tile = safeGetTile(map, x + tile_data.x, y + tile_data.y))
      {
        tile->terrain_type = TerrainType::Water;
        tile->terrain_sprite = distrib(tile_data.sprite, gen);
        tile->mirroring = tile_data.mirroring;
      }
    }
  }

  void drawFakeVerticalLandStrip(h3m::Map& map, std::uint32_t x, std::uint32_t y, std::uint32_t length)
  {
    // 2x1 segment.
    constexpr TileData kTilesToDraw[] = {
      {.x = 0, .y = 0, .sprite = WaterSpriteGroup::CoastW, .mirroring = 1},
      {.x = 1, .y = 0, .sprite = WaterSpriteGroup::CoastW, .mirroring = 0},
    };
    std::random_device rd;
    std::mt19937 gen(rd());
    WaterSpriteDistribution distrib;

    for (std::uint32_t i = 0; i < length; ++i)
    {
      for (const TileData& tile_data : kTilesToDraw)
      {
        if (Tile* tile = safeGetTile(map, x + tile_data.x, y + i + tile_data.y))
        {
          tile->terrain_type = TerrainType::Water;
          tile->terrain_sprite = distrib(tile_data.sprite, gen);
          tile->mirroring = tile_data.mirroring;
        }
      }
    }
  }

  void drawFakeDiagonalLandStripSE(Map& map, std::uint32_t x, std::uint32_t y, std::uint32_t length)
  {
    // 4x1 segment.
    constexpr TileData kTilesToDraw[] = {
      {.x = 0, .y = 0, .sprite = WaterSpriteGroup::CoastCornerSE, .mirroring = 2},
      {.x = 1, .y = 0, .sprite = WaterSpriteGroup::CoastDiagonalNW, .mirroring = 1},
      {.x = 2, .y = 0, .sprite = WaterSpriteGroup::CoastDiagonalNW, .mirroring = 2},
      {.x = 3, .y = 0, .sprite = WaterSpriteGroup::CoastCornerSE, .mirroring = 1}
    };
    std::random_device rd;
    std::mt19937 gen(rd());
    WaterSpriteDistribution distrib;

    for (std::uint32_t i = 0; i < length; ++i)
    {
      for (const TileData& tile_data : kTilesToDraw)
      {
        if (Tile* tile = safeGetTile(map, x + i + tile_data.x, y + i + tile_data.y))
        {
          tile->terrain_type = TerrainType::Water;
          tile->terrain_sprite = distrib(tile_data.sprite, gen);
          tile->mirroring = tile_data.mirroring;
        }
      }
    }
  }
}
