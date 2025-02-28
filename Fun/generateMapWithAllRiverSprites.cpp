#include <h3mtxt/Fun/generateMapWithAllRiverSprites.h>

#include <h3mtxt/Fun/generatePlayerSpecs.h>
#include <h3mtxt/Fun/HeroesAvailability.h>
#include <h3mtxt/Fun/Util.h>

namespace h3m
{
  Map generateMapWithAllRiverSprites()
  {
    constexpr std::uint32_t kMapSize = 36;
    constexpr std::uint8_t kNumRiverTypes = 5;

    Map map {
      .format = MapFormat::ShadowOfDeath,
      .basic_info {
        .is_playable = false,
        .map_size = kMapSize,
        .has_two_levels = false,
        .name = "All river sprites",
        .description = "This map is a cheatsheet for viewing river sprites in H3M.\n"
                       "Each tile (X, Y) has the river type X and the river sprite Y.\n"
                       "If X is not a valid river type or Y is not a valid sprite for X, "
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
    for (std::uint8_t river_type_idx = 0; river_type_idx < kNumRiverTypes; ++river_type_idx)
    {
      const RiverType river_type = static_cast<RiverType>(river_type_idx);
      const std::uint8_t num_sprites = countSprites(river_type);
      for (std::uint8_t sprite = 0; sprite < num_sprites; ++sprite)
      {
        if (Tile* tile = safeGetTile(map, sprite, river_type_idx))
        {
          tile->river_type = river_type;
          tile->river_sprite = sprite;
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
        (y >= kNumRiverTypes) ? 0 : countSprites(static_cast<RiverType>(y));
      for (std::uint32_t x = num_sprites; x < map.basic_info.map_size; ++x)
      {
        map.objects.push_back(Object{
          .x = static_cast<std::uint8_t>(x),
          .y = static_cast<std::uint8_t>(y),
          .z = 0,
          .template_idx = 0
          });
      }
    }
    return map;
  }
}
