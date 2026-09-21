#include "TestingUtils_H3SVG.h"

#include <h3mtxt/SavedGame/ObjectPropertiesTables.h>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3SVGWriter;
using ::Testing_NS::H3SVGReaderAdapter;

namespace h3svg
{
  TEST_CASE("H3SVG.Artifact", "[H3SVG]")
  {
    const Artifact kArtifact = {
      .guardians = {
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

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kArtifact)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readArtifact() == kArtifact);
    REQUIRE(encodeAndDecodeJson(kArtifact) == kArtifact);
  }

  TEST_CASE("H3SVG.Garrison", "[H3SVG]")
  {
    const Garrison kGarrison = {
      .owner = PlayerColor::Purple,
      .creatures = {
        .creature_types = {
          static_cast<CreatureType32>(CreatureType::AzureDragon),
          static_cast<CreatureType32>(CreatureType::FaerieDragon),
          static_cast<CreatureType32>(CreatureType::GreenDragon),
          static_cast<CreatureType32>(CreatureType::None),
          static_cast<CreatureType32>(CreatureType::None),
          static_cast<CreatureType32>(CreatureType::None),
          static_cast<CreatureType32>(CreatureType::RustDragon)
        },
        .creature_counts = { 3, 7, 15, 0, 0, 0, 5 }
      },
      .coordinates = {.x = 12, .y = 44, .z = 1},
      .can_remove_units = false
    };
    static constexpr std::string_view kBinaryData =
      "\x05"                                                    // owner
      "\x84\x00\x00\x00" "\x86\x00\x00\x00" "\x1a\x00\x00\x00"  // creature_types
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\x87\x00\x00\x00"
      "\x03\x00\x00\x00" "\x07\x00\x00\x00" "\x0f\x00\x00\x00"  // creature_counts
      "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00"
      "\x05\x00\x00\x00"
      "\x0c\x2c\x01"                                            // coordinates
      "\x00"                                                    // can_remove_units
      ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kGarrison)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readGarrison() == kGarrison);
    REQUIRE(encodeAndDecodeJson(kGarrison) == kGarrison);
  }

  TEST_CASE("H3SVG.Monster", "[H3SVG]")
  {
    const Monster kMonster = {
      .message = "Looks like meat is back on the menu, boys!",
      .resources = {15, 5, 15, 5, 5, 5, 10000},
      .artifact = static_cast<ArtifactType8>(ArtifactType::OgresClubOfHavoc)
    };
    static constexpr std::string_view kBinaryData =
      "\x2a\x00" "Looks like meat is back on the menu, boys!"   // message
      "\x0f\x00\x00\x00" "\x05\x00\x00\x00" "\x0f\x00\x00\x00"  // resources
      "\x05\x00\x00\x00" "\x05\x00\x00\x00" "\x05\x00\x00\x00"
      "\x10\x27\x00\x00"
      "\x0a"                                                    // artifact
      ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kMonster)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readMonster() == kMonster);
    REQUIRE(encodeAndDecodeJson(kMonster) == kMonster);
  }

  TEST_CASE("H3SVG.Obelisk", "[H3SVG]")
  {
    constexpr Obelisk kObelisk = {
      .visited_by = []() consteval {
        PlayersBitmask bitmask;
        bitmask.set(PlayerColor::Green, true);
        bitmask.set(PlayerColor::Teal, true);
        return bitmask;
      }()
    };
    static constexpr std::string_view kBinaryData = "\x48"sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kObelisk)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readObelisk() == kObelisk);
    REQUIRE(encodeAndDecodeJson(kObelisk) == kObelisk);
  }

  TEST_CASE("H3SVG.Sign", "[H3SVG]")
  {
    const Sign kSign = {
      .message = "KEEP OFF THE GRASS",
      .is_custom = true
    };
    static constexpr std::string_view kBinaryData =
      "\x12\x00" "KEEP OFF THE GRASS"  // message
      "\x01"                           // is_custom
      ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kSign)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readSign() == kSign);
    REQUIRE(encodeAndDecodeJson(kSign) == kSign);
  }

  TEST_CASE("H3SVG.TimedEvent", "[H3SVG]")
  {
    const TimedEvent kEvent = {
      .message = "Good luck!",
      .resources = {-100, -50, -100, -50, -50, -50, -99999},
      .affected_players = {0xFF}, // applies to all players
      .applies_to_human = true,
      .applies_to_computer = false,
      .day_of_first_occurence = 6,
      .repeat_after_days = 7
    };
    static constexpr std::string_view kBinaryData =
      "\x0a\x00" "Good luck!"                                   // message
      "\x9c\xff\xff\xff" "\xce\xff\xff\xff" "\x9c\xff\xff\xff"  // resources
      "\xce\xff\xff\xff" "\xce\xff\xff\xff" "\xce\xff\xff\xff"
      "\x61\x79\xfe\xff"
      "\xff"                                                    // affected_players
      "\x01"                                                    // applies_to_human
      "\x00"                                                    // applies_to_computer
      "\x06\x00"                                                // day_of_first_occurence
      "\x07\x00"                                                // repeat_after_days
      ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kEvent)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readTimedEvent() == kEvent);
    REQUIRE(encodeAndDecodeJson(kEvent) == kEvent);
  }

  TEST_CASE("H3SVG.TownEvent", "[H3SVG]")
  {
    const TownEvent kEvent = {
      TimedEvent{
        .message = "Good luck!",
        .resources = {-100, -50, -100, -50, -50, -50, -99999},
        .affected_players = {0xFF}, // applies to all players
        .applies_to_human = true,
        .applies_to_computer = false,
        .day_of_first_occurence = 6,
        .repeat_after_days = 7
      },
      /* .town_id = */ 7,
      /* .buildings = */ []() consteval
      {
        TownBuildingsBitmask bitmask;
        bitmask.set(TownBuildingType::Fort, true);
        return bitmask;
      }(),
      /* .reserved = */ ReservedData<2>{},
      /* .creatures = */ { 30, 20, 15, 7, 4, 2, 1 }
    };
    static constexpr std::string_view kBinaryData =
      "\x0a\x00" "Good luck!"                                   // message
      "\x9c\xff\xff\xff" "\xce\xff\xff\xff" "\x9c\xff\xff\xff"  // resources
      "\xce\xff\xff\xff" "\xce\xff\xff\xff" "\xce\xff\xff\xff"
      "\x61\x79\xfe\xff"
      "\xff"                                                    // affected_players
      "\x01"                                                    // applies_to_human
      "\x00"                                                    // applies_to_computer
      "\x06\x00"                                                // day_of_first_occurence
      "\x07\x00"                                                // repeat_after_days
      "\x07"                                                    // town_id
      "\x08\x00\x00\x00\x00\x00"                                // buildings
      "\x00\x00"                                                // reserved
      "\x1e\x00" "\x14\x00" "\x0f\x00" "\x07\x00"               // creatures
      "\x04\x00" "\x02\x00" "\x01\x00"
      ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kEvent)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readTownEvent() == kEvent);
    REQUIRE(encodeAndDecodeJson(kEvent) == kEvent);
  }
}
