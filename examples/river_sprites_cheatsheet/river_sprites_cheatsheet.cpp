#include <h3mtxt/Map/Map.h>
#include <h3mtxt/H3Writer/H3MWriter/writeh3m.h>

#include <fstream>
#include <iostream>
#include <filesystem>

namespace
{
  h3m::Map makeRiverSpritesCheatsheet()
  {
    // The smallest standard map size large enough to represent all sprites for any RiverType on a single row.
    // The maximum number of sprites for a RiverType is 13.
    constexpr std::uint8_t kMapSize = 36;

    h3m::Map map = {
      .basic_info {
        // This map is not playable, because there are no players on it.
        // It is meant to be viewed in the Map Editor.
        .is_playable = 0,
        .map_size = kMapSize,
        .has_two_levels = 0,
        .name = "River sprites cheatsheet",
        .description = "This map is a cheatsheet for viewing river sprites in H3M.\n"
                       "\n"
                       "Each tile (X, Y) has the river type Y and the river sprite X.\n"
                       "\n"
                       "If Y is not a valid river type or X is not a valid sprite "
                       "for this river type, the tile has a Campfire sprite on that tile."
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
      // The number of sprites for RiverType{y}, or 0 if RiverType{y} is not a valid RiverType.
      const std::uint8_t num_sprites = h3m::countSprites(static_cast<h3m::RiverType>(y));

      for (std::uint8_t x = 0; x < kMapSize; ++x)
      {
        if (x < num_sprites)
        {
          // Set river_type and river_sprite for tiles whose coordinates (x, y) represent valid
          // (river_sprite, river_type) combinations.
          const std::size_t tile_idx = static_cast<std::size_t>(y) * kMapSize + x;
          h3m::Tile& tile = map.tiles.at(tile_idx);
          tile.river_type = static_cast<h3m::RiverType>(y);
          tile.river_sprite = x;
        }
        else
        {
          // Put Campfire sprites on tiles whose coordinates (x, y) don't represent valid
          // (river_sprite, river_type) combinations.
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
  const std::filesystem::path output_path = "river_sprites_cheatsheet.h3m";
  const h3m::Map map = makeRiverSpritesCheatsheet();
  std::ofstream output_stream{ output_path, std::ios_base::out | std::ios_base::binary };
  if (!output_stream)
  {
    std::cerr << "Failed to open " << output_path << std::endl;
    return -1;
  }
  h3m::writeh3m(output_stream, map);
  return 0;
}
