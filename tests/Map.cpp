#include "Utils.h"

#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/Map.h>

#include <catch2/catch_test_macros.hpp>

#include <iterator>
#include <sstream>
#include <string>
#include <string_view>

using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;

namespace h3m
{
  namespace
  {
    // Encodes h3m::Map via H3MWriter.
    // \param map - input Map.
    // \return std::string storing the encoded data.
    std::string encodeMap(const Map& map)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(map);
      return std::move(stream).str();
    }

    // Decodes h3m::Map via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::Map decoded from @encoded_data.
    Map decodeMap(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readMap();
    }
  }

  // FYI: Apart from serialization, this test indirectly checks some default initializers.
  // For example, MapAdditionalInfo::victory_condition is expected to be VictoryConditionType::Normal by default.
  TEST_CASE("H3M.Map", "[H3M]")
  {
    // A simple 2x2 map with 2 heroes: Orrin (Red) and Edric (Blue).
    // This map is even playable!
    const Map kMap{
      .format = MapFormat::ShadowOfDeath,
      .basic_info = {
        .is_playable = 1,
        .map_size = 2,
        .has_two_levels = 0,
        .name = "Test map",
        .description = "Orrin vs Edric",
        .difficulty = MapDifficulty::Normal,
      },
      .players = {
        // Red
        PlayerSpecs{
          .can_be_human = 1,
          .can_be_computer = 1,
          .behavior = PlayerBehavior::Random,
          .has_customized_alignments = 1,
          .allowed_alignments = []() consteval {
            TownsBitmask bitmask;
            bitmask.set(TownType::Castle, true);
            return bitmask;
          }(),
          .allow_random_alignment = 0,
          .has_random_heroes = 0,
          .starting_hero {
            .type = HeroType::Orrin,
            .portrait = HeroPortrait::Orrin
          },
          .heroes = {
            PlayerSpecs::HeroInfo{ .type = HeroType::Orrin },
          }
        },
        // Blue
        PlayerSpecs{
          .can_be_human = 0,
          .can_be_computer = 1,
          .behavior = PlayerBehavior::Warrior,
          .has_customized_alignments = 1,
          .allowed_alignments = []() consteval {
            TownsBitmask bitmask;
            bitmask.set(TownType::Castle, true);
            return bitmask;
          }(),
          .allow_random_alignment = 0,
          .has_random_heroes = 0,
          .starting_hero {
            .type = HeroType::Edric,
            .portrait = HeroPortrait::Edric
          },
          .heroes = {
            PlayerSpecs::HeroInfo{ .type = HeroType::Edric },
          }
        },
        PlayerSpecs{}, // Tan (missing)
        PlayerSpecs{}, // Green (missing)
        PlayerSpecs{}, // Orange (missing)
        PlayerSpecs{}, // Purple (missing)
        PlayerSpecs{}, // Teal (missing)
        PlayerSpecs{}  // Pink (missing)
      },
      .tiles = {
        // (0, 0)
        Tile{
          .terrain_type = TerrainType::Dirt,
          .terrain_sprite = 21,
        },
        // (1, 0)
        Tile{
          .terrain_type = TerrainType::Dirt,
          .terrain_sprite = 22,
        },
        // (0, 1)
        Tile{
          .terrain_type = TerrainType::Dirt,
          .terrain_sprite = 23,
        },
        // (1, 1)
        Tile{
          .terrain_type = TerrainType::Dirt,
          .terrain_sprite = 24,
        }
      },
      // The Map Editor always uses RANDOM_MONSTER and PASSABLE_HOLE as the
      // 0th and the 1st template, so let's do the same.
      .objects_templates = {
        // objects_templates[0]
        ObjectTemplate{
          .def = "AVWmrnd0.def",
          .passability = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F},
          .actionability = {0, 0, 0, 0, 0, 0x80},
          .allowed_landscapes = {255, 0},
          .landscape_group = {1, 0},
          .object_class = ObjectClass::RANDOM_MONSTER,
          .object_subclass = 0,
          .object_group = ObjectGroup::Monster,
          .is_ground = 0,
        },
        // objects_templates[1]
        ObjectTemplate{
          .def = "AVLholg0.def",
          .passability = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
          .actionability = {0, 0, 0, 0, 0, 0},
          .allowed_landscapes {4, 0},
          .landscape_group {4, 0},
          .object_class = ObjectClass::PASSABLE_HOLE,
          .object_subclass = 0,
          .object_group = ObjectGroup::Terrain,
          .is_ground = 1,
        },
        // objects_templates[2]
        ObjectTemplate{
          .def = "ah00_e.def",
          .passability = {255, 255, 255, 255, 255, 191},
          .actionability = {0, 0, 0, 0, 0, 64},
          .allowed_landscapes = {255, 0},
          .landscape_group = {255, 0},
          .object_class = h3m::ObjectClass::HERO,
          .object_subclass = 0,
          .object_group = h3m::ObjectGroup::Hero,
          .is_ground = 0
        }
      },
      .objects = {
        Object{
          .coordinates = {.x = 1, .y = 0, .z = 0},
          .template_idx = 2,
          .properties = ObjectProperties<ObjectPropertiesType::HERO>{
            .absod_id = 1062840167,
            .owner = PlayerColor::Red,
            .type = HeroType::Orrin,
          }
        },
        Object{
          .coordinates = {.x = 2, .y = 0, .z = 0},
          .template_idx = 2,
          .properties = ObjectProperties<ObjectPropertiesType::HERO>{
            .absod_id = 1062840168,
            .owner = PlayerColor::Blue,
            .type = HeroType::Edric,
          }
        }
      },
      .global_events = {
        TimedEvent{
          .name = "Good luck",
          .message = "Good luck!",
          .resources = {-30, -30, -30, -30, -30, -30, -50000}, // Wood, Mercury, Ore, Sulfur, Crystal, Gems, Gold
          .affected_players { 0xFF }, // Affects all players
          .applies_to_human = 1,
          .applies_to_computer = 1,
          .day_of_first_occurence = 0, // Month: 1; Week: 1; Day: 1
          .repeat_after_days = 0, // Does not repeat
        }
      }
    };
    // The binary representation of kMap.
    static constexpr char kBinaryDataCStr[] =
      // format
      "\x1c\x00\x00\x00"
      // basic_info
      "\x01"                              // is_playable
      "\x02\x00\x00\x00"                  // map_size
      "\x00"                              // has_two_levels
      "\x08\x00\x00\x00" "Test map"       // name
      "\x0e\x00\x00\x00" "Orrin vs Edric" // description
      "\x01"                              // difficulty
      "\x00"                              // max_hero_level
      // players
      //   Red
      "\x01"                                           // can_be_human
      "\x01"                                           // can_be_computer
      "\x00"                                           // behavior
      "\x01"                                           // has_customized_alignments
      "\x01\x00"                                       // allowed_alignments
      "\x00"                                           // allow_random_alignment
      "\x00"                                           // ?main_town
      "\x00"                                           // has_random_heroes
      "\x00" "\x00" "\x00\x00\x00\x00" ""              // starting_hero
      "\x00"                                           // num_nonspecific_placeholder_heroes
      "\x01\x00\x00\x00" "\x00" "\x00\x00\x00\x00" ""  // heroes
      //   Blue
      "\x00"                                           // can_be_human
      "\x01"                                           // can_be_computer
      "\x01"                                           // behavior
      "\x01"                                           // has_customized_alignments
      "\x01\x00"                                       // allowed_alignments
      "\x00"                                           // allow_random_alignment
      "\x00"                                           // ?main_town
      "\x00"                                           // has_random_heroes
      "\x02" "\x02" "\x00\x00\x00\x00" ""              // starting_hero
      "\x00"                                           // num_nonspecific_placeholder_heroes
      "\x01\x00\x00\x00" "\x02" "\x00\x00\x00\x00" ""  // heroes
      //   Tan (missing)
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\x00\x00\x00\x00\x00"
      //   Green (missing)
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\x00\x00\x00\x00\x00"
      //   Orange (missing)
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\x00\x00\x00\x00\x00"
      //   Purple (missing)
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\x00\x00\x00\x00\x00"
      //   Teal (missing)
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\x00\x00\x00\x00\x00"
      //   Pink (missing)
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\x00\x00\x00\x00\x00"
      // additional_info
      "\xff"                                             // victory_condition
      "\xff"                                             // loss_condition
      "\x00"                                             // teams
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"         // heroes_availability
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00"                                 // placeholder_heroes
      "\x00"                                             // custom_heroes
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"         // reserved
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00"             // disabled_artifacts
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00"             // disabled_spells
      "\x00\x00\x00\x00"                                 // disabled_skills
      "\x00\x00\x00\x00"                                 // rumors
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" // heroes_settings
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      // tiles
      "\x00\x15\x00\x00\x00\x00\x00" // (0, 0)
      "\x00\x16\x00\x00\x00\x00\x00" // (1, 0)
      "\x00\x17\x00\x00\x00\x00\x00" // (0, 1)
      "\x00\x18\x00\x00\x00\x00\x00" // (1, 1)
      // objects_templates
      "\x03\x00\x00\x00"
      //   objects_templates[0]
      "\x0c\x00\x00\x00" "AVWmrnd0.def"                                   // def
      "\xff\xff\xff\xff\xff\x7f"                                          // passability
      "\x00\x00\x00\x00\x00\x80"                                          // actionability
      "\xff\x00"                                                          // allowed_landscapes
      "\x01\x00"                                                          // landscape_group
      "\x47\x00\x00\x00"                                                  // object_class
      "\x00\x00\x00\x00"                                                  // object_subclass
      "\x02"                                                              // object_group
      "\x00"                                                              // is_ground
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"  // unknown
      //   objects_templates[1]
      "\x0c\x00\x00\x00" "AVLholg0.def"                                   // def
      "\xff\xff\xff\xff\xff\xff"                                          // passability
      "\x00\x00\x00\x00\x00\x00"                                          // actionability
      "\x04\x00"                                                          // allowed_landscapes
      "\x04\x00"                                                          // landscape_group
      "\x7c\x00\x00\x00"                                                  // object_class
      "\x00\x00\x00\x00"                                                  // object_subclass
      "\x00"                                                              // object_group
      "\x01"                                                              // is_ground
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"  // unknown
      //   objects_templates[2]
      "\x0a\x00\x00\x00" "ah00_e.def"                                     // def
      "\xff\xff\xff\xff\xff\xbf"                                          // passability
      "\x00\x00\x00\x00\x00\x40"                                          // actionability
      "\xff\x00"                                                          // allowed_landscapes
      "\xff\x00"                                                          // landscape_group
      "\x22\x00\x00\x00"                                                  // object_class
      "\x00\x00\x00\x00"                                                  // object_subclass
      "\x03"                                                              // object_group
      "\x00"                                                              // is_ground
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"  // unknown
      // objects
      "\x02\x00\x00\x00"
      //   objects[0]
      "\x01\x00\x00"                     // coordinates
      "\x02\x00\x00\x00"                 // template_idx
      "\x00\x00\x00\x00\x00"             // unknown
                                         // properties
      "\x67\xa7\x59\x3f"                 //   absod_id
      "\x00"                             //   owner
      "\x00"                             //   type
      "\x00"                             //   ?name
      "\x00"                             //   ?experience
      "\x00"                             //   ?portrait
      "\x00"                             //   ?secondary_skills
      "\x00"                             //   ?creatures
      "\x00"                             //   formation
      "\x00"                             //   ?artifacts
      "\xff"                             //   patrol_radius
      "\x00"                             //   ?biography
      "\xff"                             //   gender
      "\x00"                             //   ?spells
      "\x00"                             //   ?primary_skills
      "\x00\x00\x00\x00\x00\x00\x00\x00" //   unknown
      "\x00\x00\x00\x00\x00\x00\x00\x00"
      //   objects[1]
      "\x02\x00\x00"                     // coordinates
      "\x02\x00\x00\x00"                 // template_idx
      "\x00\x00\x00\x00\x00"             // unknown
                                         // properties
      "\x68\xa7\x59\x3f"                 //   absod_id
      "\x01"                             //   owner
      "\x02"                             //   type
      "\x00"                             //   ?name
      "\x00"                             //   ?experience
      "\x00"                             //   ?portrait
      "\x00"                             //   ?secondary_skills
      "\x00"                             //   ?creatures
      "\x00"                             //   formation
      "\x00"                             //   ?artifacts
      "\xff"                             //   patrol_radius
      "\x00"                             //   ?biography
      "\xff"                             //   gender
      "\x00"                             //   ?spells
      "\x00"                             //   ?primary_skills
      "\x00\x00\x00\x00\x00\x00\x00\x00" //   unknown
      "\x00\x00\x00\x00\x00\x00\x00\x00"
      // global_events
      "\x01\x00\x00\x00"
      //   global_events[0]
      "\x09\x00\x00\x00" "Good luck"                                     // name
      "\x0a\x00\x00\x00" "Good luck!"                                    // message
      "\xe2\xff\xff\xff" "\xe2\xff\xff\xff" "\xe2\xff\xff\xff"           // resources
      "\xe2\xff\xff\xff" "\xe2\xff\xff\xff" "\xe2\xff\xff\xff"
      "\xb0\x3c\xff\xff"
      "\xff"                                                             // affected_players
      "\x01"                                                             // applies_to_human
      "\x01"                                                             // applies_to_computer
      "\x00\x00"                                                         // day_of_first_occurence
      "\x00\x00"                                                         // repeat_after_days
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" // unknown
      // padding
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
    // std::string_view into kBinaryDataCStr.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
    REQUIRE(asByteVector(encodeMap(kMap)) == asByteVector(kBinaryData));
    REQUIRE(decodeMap(kBinaryData) == kMap);
    REQUIRE(encodeAndDecodeJson(kMap) == kMap);
  }
}
