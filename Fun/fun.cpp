#include <h3mtxt/Fun/drawCarpet.h>
#include <h3mtxt/Fun/fakeIslands.h>
#include <h3mtxt/Fun/fillWithTerrain.h>
#include <h3mtxt/Fun/generateMapWithAllRiverSprites.h>
#include <h3mtxt/Fun/generatePlayerSpecs.h>
#include <h3mtxt/Fun/HeroesAvailability.h>
#include <h3mtxt/Fun/makeDefaultObjectAttributes.h>
#include <h3mtxt/Fun/Util.h>
#include <h3mtxt/H3Writer/writeh3m.h>
#include <h3mtxt/Map/Map.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>

namespace fs = std::filesystem;

using h3m::drawFakeDiagonalLandStripSE;
using h3m::drawFakeIsland;
using h3m::drawFakeMiniIsland;
using h3m::drawFakeVerticalLandStrip;
using h3m::kAbsentPlayerSpecs;
using h3m::safeGetTile;

namespace
{
  h3m::Map generateTestMap(std::uint32_t map_size = 36)
  {
    h3m::Map map {
      .format = h3m::MapFormat::ShadowOfDeath,
      .basic_info {
        .is_playable = false,
        .map_size = map_size,
        .has_two_levels = false,
        .name = "Test map",
        .description = "Test map generated by h3mtxt.",
        .difficulty = h3m::MapDifficulty::Easy,
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
        // Normal victory condition.
        .victory_condition {},
        // Normal loss condition.
        .loss_condition {},
        // No teams.
        .teams {},
        // Enable all heroes.
        .heroes_availability = h3m::kAllHeroesAvailability,
        // No placeholder heroes.
        .placeholder_heroes {},
        // No custom heroes.
        .custom_heroes {},
        .reserved {},
        .disabled_artifacts {},
        .disabled_spells {},
        .disabled_skills {},
        .rumors {
          h3m::Rumor {
            .name = "Rumor",
            .description = "This is the only rumor."
          }
        },
        // No heroes with customized settings.
        .heroes_settings {}
      },
      .tiles = std::vector<h3m::Tile>(map_size * map_size, h3m::Tile{
        .terrain_type = h3m::TerrainType::Rock,
        .terrain_sprite = 0
      }),
      .global_events {
        h3m::GlobalEvent {
          h3m::TimedEventBase {
            .name = "Global event",
            .message = "Enjoy some resources.",
            .resources {
              .data {10, 5, 10, 5, 5, 5, 10000}
             },
            .affected_players {std::array<std::uint8_t, 1>{ 0xFF }},
            .applies_to_human = true,
            .applies_to_computer = true,
            .day_of_first_occurence = 0,
            .repeat_after_days = 0
          }
        }
      }
    };
    return map;
  }

  void drawFakeIslands(h3m::Map& map)
  {
    drawFakeIsland(map, 5, 5);
    drawFakeIsland(map, 5, 9);
    drawFakeIsland(map, 9, 5);
    drawFakeIsland(map, 9, 9);
    drawFakeMiniIsland(map, 20, 8);
    drawFakeMiniIsland(map, 20, 10);
    drawFakeMiniIsland(map, 22, 9);
    drawFakeMiniIsland(map, 24, 11);
    drawFakeMiniIsland(map, 22, 12);
    drawFakeMiniIsland(map, 25, 9);
    drawFakeMiniIsland(map, 26, 13);
    drawFakeVerticalLandStrip(map, 10, 15, 10);
    drawFakeVerticalLandStrip(map, 12, 15, 10);
    drawFakeVerticalLandStrip(map, 14, 15, 10);
    drawFakeDiagonalLandStripSE(map, 20, 20, 10);
    drawFakeDiagonalLandStripSE(map, 24, 20, 10);
  }

  h3m::Map generateMapWithHeroes()
  {
    constexpr h3m::PlayerColor player1 = h3m::PlayerColor::Red;
    constexpr h3m::PlayerColor player2 = h3m::PlayerColor::Blue;
    constexpr h3m::HeroType hero1 = h3m::HeroType::ORRIN;
    constexpr h3m::HeroType hero2 = h3m::HeroType::XERON;

    h3m::Map map = generateTestMap(36);
    map.basic_info.is_playable = true;
    map.basic_info.name = "Test spell scroll";
    map.basic_info.description = "Testing if a spell scroll can be added as an artifact.";
    map.players[static_cast<std::size_t>(player1)] = h3m::generatePlayerSpecsNoTown(true, hero1);
    map.players[static_cast<std::size_t>(player2)] = h3m::generatePlayerSpecsNoTown(false, hero2);

    h3m::drawCarpet(map, h3m::TerrainType::Lava, 30, 1);

    constexpr std::uint32_t kHeroKind = 0;
    constexpr std::uint32_t kSpellScrollKind = 1;
    constexpr std::uint32_t kPandorasBoxKind = 2;
    // Add heroes.
    map.objects_attributes.push_back(h3m::ObjectAttributes{
      .def = "ah00_e.def",
      .passability {255, 255, 255, 255, 255, 191},
      .actionability {0, 0, 0, 0, 0, 64},
      .object_class = h3m::ObjectClass::HERO,
      .object_subclass = 0,
      .object_group = h3m::ObjectGroup::Hero,
      .is_ground = 0
      });
    map.objects_details.push_back(h3m::ObjectDetails{
      .x = 1,
      .y = 0,
      .z = 0,
      .kind = kHeroKind,
      .details = h3m::ObjectDetailsData<h3m::MetaObjectType::HERO> {
        .absod_id = 69,
        .owner = 0,
        .type = hero1,
        .secondary_skills = std::vector<h3m::SecondarySkill> {
          h3m::SecondarySkill {.type = h3m::SecondarySkillType::Mysticism, .level = 3},
          h3m::SecondarySkill {.type = h3m::SecondarySkillType::Artillery, .level = 3},
          h3m::SecondarySkill {.type = h3m::SecondarySkillType::Archery, .level = 3},
          h3m::SecondarySkill {.type = h3m::SecondarySkillType::Logistics, .level = 3},
        },
        .creatures = std::array<h3m::CreatureStack, 7> {
          h3m::CreatureStack {.type = h3m::CreatureType::Archangel, .count = 10},
          h3m::CreatureStack {.type = h3m::CreatureType::Ballista, .count = 20},
          h3m::CreatureStack {.type = h3m::CreatureType::Titan, .count = 10},
          h3m::CreatureStack{},
          h3m::CreatureStack{},
          h3m::CreatureStack{},
          h3m::CreatureStack{}
        },
        .patrol_radius = 255,
        .primary_skills = h3m::PrimarySkills {
          .attack = 0,
          .defense = 0,
          .spell_power = 10,
          .knowledge = 10
        }
      }
    });
    map.objects_details.push_back(h3m::ObjectDetails{
      .x = 10,
      .y = 10,
      .z = 0,
      .kind = kHeroKind,
      .details = h3m::ObjectDetailsData<h3m::MetaObjectType::HERO> {
        .absod_id = 666,
        .owner = 1,
        .type = hero2,
        .secondary_skills = std::vector<h3m::SecondarySkill>{
          h3m::SecondarySkill {.type = h3m::SecondarySkillType::Artillery, .level = 3}
        },
        .creatures = std::array<h3m::CreatureStack, 7> {
          h3m::CreatureStack {.type = h3m::CreatureType::Imp, .count = 50},
          h3m::CreatureStack {.type = h3m::CreatureType::Ballista, .count = 20},
          h3m::CreatureStack{},
          h3m::CreatureStack{},
          h3m::CreatureStack{},
          h3m::CreatureStack{},
          h3m::CreatureStack{}
        },
        .patrol_radius = 255
      }
    });
    // Add a spell scroll.
    map.objects_attributes.push_back(h3m::makeDefaultObjectAttributes(h3m::ObjectClass::SPELL_SCROLL));
    map.objects_details.push_back(h3m::ObjectDetails{
      .x = 2,
      .y = 2,
      .z = 0,
      .kind = kSpellScrollKind,
      .details = h3m::ObjectDetailsData<h3m::MetaObjectType::SPELL_SCROLL> {
        .spell = h3m::SpellType::SLOW
      }
    });
    // Add a Pandora's Box.
    map.objects_attributes.push_back(h3m::makeDefaultObjectAttributes(h3m::ObjectClass::PANDORAS_BOX));
    map.objects_details.push_back(h3m::ObjectDetails{
      .x = 2,
      .y = 3,
      .z = 0,
      .kind = kPandorasBoxKind,
      .details = h3m::ObjectDetailsData<h3m::MetaObjectType::PANDORAS_BOX> {
        h3m::EventBase {
          .secondary_skills {
            h3m::SecondarySkill {.type = h3m::SecondarySkillType::Mysticism, .level = 3 }
          }
        }
      }
    });
    // Add a Scholar.
    map.objects_attributes.push_back(h3m::makeDefaultObjectAttributes(h3m::ObjectClass::SCHOLAR));
    map.objects_details.push_back(h3m::ObjectDetails{
      .x = 2,
      .y = 4,
      .z = 0,
      .kind = static_cast<std::uint32_t>(map.objects_attributes.size() - 1),
      .details = h3m::ObjectDetailsData<h3m::MetaObjectType::SCHOLAR> {
        .reward_type = h3m::ScholarRewardType::SecondarySkill,
        .reward_value = static_cast<std::uint8_t>(h3m::SecondarySkillType::Mysticism)
      }
    });
    // Add an Event.
    map.objects_attributes.push_back(h3m::makeDefaultObjectAttributes(h3m::ObjectClass::EVENT));
    {
      h3m::ObjectDetailsData<h3m::MetaObjectType::EVENT> event_details{
        h3m::EventBase{
          .spell_points = -999
        },
      };
      event_details.affected_players.bitset.data = std::array<std::uint8_t, 1>{0xFF};
      event_details.remove_after_first_visit = true;
      map.objects_details.push_back(h3m::ObjectDetails{
        .x = 0,
        .y = 1,
        .z = 0,
        .kind = static_cast<std::uint32_t>(map.objects_attributes.size() - 1),
        .details = std::move(event_details)
      });
    }
    map.objects_attributes.push_back(h3m::makeDefaultObjectAttributes(h3m::ObjectClass::EVENT));
    {
      h3m::ObjectDetailsData<h3m::MetaObjectType::EVENT> event_details{
        h3m::EventBase{
          .secondary_skills {
            h3m::SecondarySkill {.type = h3m::SecondarySkillType::FirstAid, .level = 3}
          }
        },
      };
      event_details.affected_players.bitset.data = std::array<std::uint8_t, 1>{0xFF};
      event_details.remove_after_first_visit = true;
      map.objects_details.push_back(h3m::ObjectDetails{
        .x = 0,
        .y = 2,
        .z = 0,
        .kind = static_cast<std::uint32_t>(map.objects_attributes.size() - 1),
        .details = std::move(event_details)
        });
    }
    // Add a Seer's Hut.
    map.objects_attributes.push_back(h3m::makeDefaultObjectAttributes(h3m::ObjectClass::SEER_HUT));
    map.objects_details.push_back(h3m::ObjectDetails{
      .x = 4,
      .y = 5,
      .z = 0,
      .kind = static_cast<std::uint32_t>(map.objects_attributes.size() - 1),
      .details = h3m::ObjectDetailsData<h3m::MetaObjectType::SEERS_HUT> {
        .quest {
          .details = h3m::QuestDetails<h3m::QuestType::BeHero> {
            .hero = hero1
          }
        },
        .reward {
          .details = h3m::RewardDetails<h3m::RewardType::SecondarySkill> {
            .skill {
              .type = h3m::SecondarySkillType::Mysticism,
              .level = 3
            }
          }
        }
      }
    });
    return map;
  }
}

int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cout << "Usage: Fun map-path" << std::endl;
    return -1;
  }

  try
  {
    const fs::path path_map(argv[1]);

    const h3m::Map map = generateMapWithHeroes();
    //h3m::Map map = generateTestMap();
    //fillWithTerrain(map, h3m::TerrainType::Water);
    //drawFakeIslands(map);

    std::ofstream out_stream(path_map, std::ios_base::out | std::ios_base::binary);
    h3m::H3Writer_NS::writeh3m(out_stream, map);
  }
  catch (const std::exception& error)
  {
    std::cerr << error.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "Unknown error." << std::endl;
  }

  return 0;
}
