#include <h3mtxt/Map/Map.h>
#include <h3mtxt/H3Writer/H3MWriter/writeh3m.h>

#include <fstream>
#include <iostream>
#include <filesystem>

namespace
{
  h3m::Map makeTerrainSpritesCheatsheet()
  {
    // The smallest standard map size large enough to represent all sprites for any TerrainType on a single row.
    // The maximum number of sprites for a TerrainType is 73.
    constexpr std::uint8_t kMapSize = 108;

    h3m::Map map = {
      .basic_info {
        // This map is not playable, because there are no players on it.
        // It is meant to be viewed in the Map Editor.
        .is_playable = 0,
        .map_size = kMapSize,
        .has_two_levels = 0,
        .name = "Terrain sprites cheatsheet",
        .description = "This map is a cheatsheet for viewing terrain sprites in H3M.\n"
                       "\n"
                       "Each tile (X, Y) has the terrain type Y and the terrain sprite X.\n"
                       "\n"
                       "If Y is not a valid terrain type or X is not a valid sprite "
                       "for this terrain type, the tile has a Campfire sprite on that tile."
      },
      .tiles = std::vector<h3m::Tile>{
        static_cast<std::size_t>(kMapSize) * kMapSize,
        h3m::Tile{
          .terrain_type = h3m::TerrainType::Rock,
          .terrain_sprite = 0
        }
      },
      .objects_templates = {
        h3m::ObjectTemplate{
          .def = "adcfra.def",
          .passability = {255, 255, 255, 255, 255, 127},
          .actionability = {0, 0, 0, 0, 0, 0},
          .object_class = h3m::ObjectClass::NONE,
          .object_subclass = 0,
          .object_group = h3m::ObjectGroup::Terrain,
        }
      }
    };
    // Process each tile.
    for (std::uint8_t y = 0; y < kMapSize; ++y)
    {
      // The number of sprites for TerrainType{y}, or 0 if TerrainType{y} is not a valid TerrainType.
      const std::uint8_t num_sprites = h3m::countSprites(static_cast<h3m::TerrainType>(y));

      for (std::uint8_t x = 0; x < kMapSize; ++x)
      {
        if (x < num_sprites)
        {
          // Set terrain_type and terrain_sprite for tiles whose coordinates (x, y) represent valid
          // (terrain_sprite, terrain_type) combinations.
          const std::size_t tile_idx = static_cast<std::size_t>(y) * kMapSize + x;
          h3m::Tile& tile = map.tiles.at(tile_idx);
          tile.terrain_type = static_cast<h3m::TerrainType>(y);
          tile.terrain_sprite = x;
        }
        else
        {
          // Put Campfire sprites on tiles whose coordinates (x, y) don't represent valid
          // (terrain_sprite, terrain_type) combinations.
          map.objects.push_back(h3m::Object{
            .coordinates = {.x = x, .y = y, .z = 0},
            .template_idx = 0
          });
        }
      }
    }
    return map;
  }
}

int main()
{
  const std::filesystem::path output_path = "terrain_sprites_cheatsheet.h3m";
  const h3m::Map map = makeTerrainSpritesCheatsheet();
  std::ofstream output_stream{ output_path, std::ios_base::out | std::ios_base::binary };
  if (!output_stream)
  {
    std::cerr << "Failed to open " << output_path << std::endl;
    return -1;
  }
  h3m::writeh3m(output_stream, map);
  return 0;
}
