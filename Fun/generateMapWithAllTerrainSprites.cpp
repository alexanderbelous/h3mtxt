#include <h3mtxt/Fun/generateMapWithAllTerrainSprites.h>

#include <h3mtxt/Fun/generatePlayerSpecs.h>
#include <h3mtxt/Fun/HeroesAvailability.h>
#include <h3mtxt/Fun/Util.h>

namespace h3m
{
  Map generateMapWithAllTerrainSprites()
  {
    constexpr std::uint32_t kMapSize = 108;
    constexpr std::uint8_t kNumTerrainTypes = 10;

    Map map {
      .format = MapFormat::ShadowOfDeath,
      .basic_info {
        .is_playable = false,
        .map_size = kMapSize,
        .has_two_levels = false,
        .name = "All terrain sprites",
        .description = "This map is a cheatsheet for viewing terrain sprites in H3M.\n"
                       "Each tile (X, Y) has the terrain type X and the terrain sprite Y.\n"
                       "If X is not a valid terrain type or Y is not a valid sprite for X, "
                       "the tile has a campfire object on that tile.",
        .difficulty = MapDifficulty::Easy,
        .max_hero_level = 0
      },
      .players {
        kAbsentPlayerSpecs,
        kAbsentPlayerSpecs,
        kAbsentPlayerSpecs,
        kAbsentPlayerSpecs,
        kAbsentPlayerSpecs,
        kAbsentPlayerSpecs,
        kAbsentPlayerSpecs,
        kAbsentPlayerSpecs
      },
      .additional_info {
        // Enable all heroes.
        .heroes_availability = kAllHeroesAvailability,
      },
      .tiles = std::vector<Tile>(kMapSize * kMapSize, Tile{
        .terrain_type = TerrainType::Rock,
        .terrain_sprite = 0
      }),
    };
    for (std::uint8_t terrain_type_idx = 0; terrain_type_idx < kNumTerrainTypes; ++terrain_type_idx)
    {
      const TerrainType terrain_type = static_cast<TerrainType>(terrain_type_idx);
      const std::uint8_t num_sprites = countSprites(terrain_type);
      for (std::uint8_t sprite = 0; sprite < num_sprites; ++sprite)
      {
        if (Tile* tile = safeGetTile(map, sprite, terrain_type_idx))
        {
          tile->terrain_type = terrain_type;
          tile->terrain_sprite = sprite;
        }
      }
    }
    map.objects_templates.push_back(ObjectTemplate{
      .def = "adcfra.def",
      .object_class = ObjectClass::CAMPFIRE,
      .object_subclass = 0,
      .object_group = ObjectGroup::Treasure,
      });
    for (std::uint32_t y = 0; y < map.basic_info.map_size; ++y)
    {
      const std::uint8_t num_sprites =
        (y >= kNumTerrainTypes) ? 0 : countSprites(static_cast<TerrainType>(y));
      for (std::uint32_t x = num_sprites; x < map.basic_info.map_size; ++x)
      {
        map.objects_details.push_back(ObjectDetails{
          .x = static_cast<std::uint8_t>(x),
          .y = static_cast<std::uint8_t>(y),
          .z = 0,
          .kind = 0
          });
      }
    }
    return map;
  }
}
