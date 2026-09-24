#include "TestingUtils_H3SVG.h"

#include <h3mtxt/SavedGame/SavedGame.h>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3SVGWriter;
using ::Testing_NS::H3SVGReaderAdapter;

namespace h3svg
{
  TEST_CASE("H3SVG.ArtifactMerchants", "[H3SVG]")
  {
    static constexpr ArtifactMerchants kArtifactMerchants{
      .artifacts = {
        static_cast<ArtifactType32>(ArtifactType::BadgeOfCourage),
        static_cast<ArtifactType32>(ArtifactType::CentaurAxe),
        static_cast<ArtifactType32>(ArtifactType::CloverOfFortune),
        static_cast<ArtifactType32>(ArtifactType::EndlessBagOfGold),
        static_cast<ArtifactType32>(ArtifactType::BowOfElvenCherrywood),
        static_cast<ArtifactType32>(ArtifactType::None),
        static_cast<ArtifactType32>(ArtifactType::None)
      }
    };
    static constexpr std::string_view kBinaryData =
      "\x31\x00\x00\x00" "\x07\x00\x00\x00" "\x2e\x00\x00\x00" "\x74\x00\x00\x00"
      "\x3c\x00\x00\x00" "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kArtifactMerchants)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readArtifactMerchants() == kArtifactMerchants);
    REQUIRE(encodeAndDecodeJson(kArtifactMerchants) == kArtifactMerchants);
  }

  TEST_CASE("H3SVG.CreatureBank", "[H3SVG]")
  {
    const CreatureBank kCreatureBank = {
      .guards = {
        .creature_types = {
          static_cast<CreatureType32>(CreatureType::BlackDragon),
          static_cast<CreatureType32>(CreatureType::GreenDragon),
          static_cast<CreatureType32>(CreatureType::GoldDragon),
          static_cast<CreatureType32>(CreatureType::RedDragon),
          static_cast<CreatureType32>(CreatureType::None),
          static_cast<CreatureType32>(CreatureType::None),
          static_cast<CreatureType32>(CreatureType::None)
        },
        .creature_counts = {2, 7, 3, 6}
      },
      .resources = {0, 0, 0, 0, 0, 15, 30000}, // Wood, Mercury, Ore, Sulfur, Crystal, Gems, Gold
      .creatures = {.type = static_cast<CreatureType32>(CreatureType::AzureDragon), .quantity = 1},
      .artifacts = {
        static_cast<ArtifactType32>(ArtifactType::PowerOfTheDragonFather),
        static_cast<ArtifactType32>(ArtifactType::OrbOfVulnerability),
        static_cast<ArtifactType32>(ArtifactType::Cornucopia),
        static_cast<ArtifactType32>(ArtifactType::BirdOfPerception),
      }
    };
    static constexpr std::string_view kBinaryData =
      // guards
      //   creature_types
      "\x53\x00\x00\x00" "\x1a\x00\x00\x00" "\x1b\x00\x00\x00" "\x52\x00\x00\x00"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      //   creature_counts
      "\x02\x00\x00\x00" "\x07\x00\x00\x00" "\x03\x00\x00\x00" "\x06\x00\x00\x00"
      "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00"
      // resources
      "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00" "\x00\x00\x00\x00"
      "\x00\x00\x00\x00" "\x0f\x00\x00\x00" "\x30\x75\x00\x00"
      // creatures
      //   type
      "\x84\x00\x00\x00"
      //   quantity
      "\x01"
      // artifacts
      //   size
      "\x04\x00"
      //   elements
      "\x86\x00\x00\x00" "\x5d\x00\x00\x00" "\x8c\x00\x00\x00" "\x3f\x00\x00\x00"
      ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kCreatureBank)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readCreatureBank() == kCreatureBank);
    REQUIRE(encodeAndDecodeJson(kCreatureBank) == kCreatureBank);
  }

  TEST_CASE("H3SVG.Date", "[H3SVG]")
  {
    static constexpr Date kDate = {
      .day = 7,
      .week = 2,
      .month = 1
    };
    static constexpr std::string_view kBinaryData = "\x07\x00" "\x02\x00" "\x01\x00" ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kDate)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readDate() == kDate);
    REQUIRE(encodeAndDecodeJson(kDate) == kDate);
  }

  TEST_CASE("H3SVG.Object", "[H3SVG]")
  {
    static constexpr Object kObject = {
      .coordinates = {.x = 12, .y = 49, .z = 1},
      .template_idx = 77
    };
    static constexpr std::string_view kBinaryData = "\x0c\x31\x01" "\x4d\x00" ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kObject)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readObject() == kObject);
    REQUIRE(encodeAndDecodeJson(kObject) == kObject);
  }

  TEST_CASE("H3SVG.ObjectExits", "[H3SVG]")
  {
    const ObjectExits kObjectExits = {
      .exits = {
        CoordinatesPacked{.x = 1, .y = 39, .z = 0},
        CoordinatesPacked{.x = 7, .y = 59, .z = 0},
        CoordinatesPacked{.x = 22, .y = 61, .z = 0},
        CoordinatesPacked{.x = 112, .y = 8, .z = 1}
      }
    };
    static constexpr std::string_view kBinaryData =
      "\x04\x00"
      "\x01\x00\x27\x00"
      "\x07\x00\x3b\x00"
      "\x16\x00\x3d\x00"
      "\x70\x00\x08\x04"
      ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kObjectExits)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readObjectExits() == kObjectExits);
    REQUIRE(encodeAndDecodeJson(kObjectExits) == kObjectExits);
  }

  TEST_CASE("H3SVG.University", "[H3SVG]")
  {
    static constexpr University kUniversity = {
      .skills = {
        static_cast<SecondarySkillType32>(SecondarySkillType::Armorer),
        static_cast<SecondarySkillType32>(SecondarySkillType::EarthMagic),
        static_cast<SecondarySkillType32>(SecondarySkillType::Tactics),
        static_cast<SecondarySkillType32>(SecondarySkillType::Intelligence)
      }
    };
    static constexpr std::string_view kBinaryData =
      "\x17\x00\x00\x00"
      "\x11\x00\x00\x00"
      "\x13\x00\x00\x00"
      "\x18\x00\x00\x00"
      ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kUniversity)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readUniversity() == kUniversity);
    REQUIRE(encodeAndDecodeJson(kUniversity) == kUniversity);
  }
}
