#include "TestingUtils_H3SVG.h"

#include <h3mtxt/SavedGame/EventBase.h>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3SVGWriter;
using ::Testing_NS::H3SVGReaderAdapter;

namespace h3svg
{
  TEST_CASE("H3SVG.Guardians", "[H3SVG]")
  {
    const Guardians kGuardians = {
      .message = "Looks like meat is back on the menu, boys!",
      .creatures = Troops{
        .creature_types = {
          static_cast<CreatureType32>(CreatureType::Orc),
          static_cast<CreatureType32>(CreatureType::OrcChieftain),
          static_cast<CreatureType32>(CreatureType::Goblin),
          static_cast<CreatureType32>(CreatureType::Troll),
          static_cast<CreatureType32>(CreatureType::None),
          static_cast<CreatureType32>(CreatureType::None),
          static_cast<CreatureType32>(CreatureType::None)
        },
        .creature_counts = { 30, 20, 50, 10, 0, 0, 0 }
      }
    };
    static constexpr std::string_view kBinaryData =
      "\x2a\x00" "Looks like meat is back on the menu, boys!"   // message
      "\x01"                                                    // creatures
      "\x58\x00\x00\x00" "\x59\x00\x00\x00" "\x54\x00\x00\x00"  //   creature_types
      "\x90\x00\x00\x00" "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff"
      "\x1e\x00\x00\x00" "\x14\x00\x00\x00" "\x32\x00\x00\x00"  //   creature_counts
      "\x0a\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00"
      "\x00\x00\x00\x00"
      ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kGuardians)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readGuardians() == kGuardians);
    REQUIRE(encodeAndDecodeJson(kGuardians) == kGuardians);
  }

  TEST_CASE("H3SVG.EventBase", "[H3SVG]")
  {
    const EventBase kEvent = {
      .guardians = Guardians {
        .message = "Looks like meat is back on the menu, boys!",
        .creatures = Troops{
          .creature_types = {
            static_cast<CreatureType32>(CreatureType::Orc),
            static_cast<CreatureType32>(CreatureType::OrcChieftain),
            static_cast<CreatureType32>(CreatureType::Goblin),
            static_cast<CreatureType32>(CreatureType::Troll),
            static_cast<CreatureType32>(CreatureType::None),
            static_cast<CreatureType32>(CreatureType::None),
            static_cast<CreatureType32>(CreatureType::None)
          },
          .creature_counts = { 30, 20, 50, 10, 0, 0, 0 }
        }
      },
      .experience = 5000,
      .spell_points = 100,
      .morale = -3,
      .luck = 1,
      .resources = {15, 5, 15, 5, 5, 5, 10000},
      .primary_skills = {2, 2, 0, 1},
      .secondary_skills = {
        SecondarySkill{ .type = SecondarySkillType::Tactics, .level = 3 },
        SecondarySkill{ .type = SecondarySkillType::Offense, .level = 1 },
      },
      .artifacts = {
        static_cast<ArtifactType8>(ArtifactType::CentaurAxe),
        static_cast<ArtifactType8>(ArtifactType::RingOfTheWayfarer),
      },
      .spells = {
        SpellType::TownPortal,
        SpellType::ForceField
      },
      .creatures = {
        TypedQuantity<CreatureType, std::int16_t>{ .type = CreatureType::Sharpshooter, .quantity = 15 },
        TypedQuantity<CreatureType, std::int16_t>{ .type = CreatureType::Enchanter, .quantity = 4 }
      }
    };
    static constexpr std::string_view kBinaryData =
      "\x01"                                                    // guardians
      "\x2a\x00" "Looks like meat is back on the menu, boys!"   //   message
      "\x01"                                                    //   creatures
      "\x58\x00\x00\x00" "\x59\x00\x00\x00" "\x54\x00\x00\x00"  //     creature_types
      "\x90\x00\x00\x00" "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff"
      "\x1e\x00\x00\x00" "\x14\x00\x00\x00" "\x32\x00\x00\x00"  //     creature_counts
      "\x0a\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00"
      "\x00\x00\x00\x00"
      "\x88\x13\x00\x00"                                        // experience
      "\x64\x00\x00\x00"                                        // spell_points
      "\xfd"                                                    // morale
      "\x01"                                                    // luck
      "\x0f\x00\x00\x00" "\x05\x00\x00\x00" "\x0f\x00\x00\x00"  // resources
      "\x05\x00\x00\x00" "\x05\x00\x00\x00" "\x05\x00\x00\x00"
      "\x10\x27\x00\x00"
      "\x02\x02\x00\x01"                                        // primary_skills
      "\x02" "\x13\x03" "\x16\x01"                              // secondary_skills
      "\x02" "\x07" "\x45"                                      // artifacts
      "\x02" "\x09" "\x0c"                                      // spells
      "\x02" "\x89\x00" "\x0f\x00" "\x88\x00" "\x04\x00"        // creatures
      ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kEvent)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readEventBase() == kEvent);
    REQUIRE(encodeAndDecodeJson(kEvent) == kEvent);
  }
}
