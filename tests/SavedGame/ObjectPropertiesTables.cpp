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
}
