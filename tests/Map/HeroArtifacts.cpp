#include "TestUtils_H3M.h"

#include <h3mtxt/Map/HeroArtifacts.h>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3MWriter;
using ::Testing_NS::H3MReaderAdapter;

namespace h3m
{
  TEST_CASE("H3M.HeroArtifacts", "[H3M]")
  {
    SECTION("Empty backpack")
    {
      const HeroArtifacts kHeroArtifacts{
        .equipped = []() consteval {
          EnumIndexedArray<ArtifactSlot, ArtifactType, kNumArtifactSlots> artifacts =
            HeroArtifacts::kNoEquippedArtifacts;
          artifacts[ArtifactSlot::Feet] = ArtifactType::BootsOfSpeed;
          artifacts[ArtifactSlot::LeftRing] = ArtifactType::EquestriansGloves;
          artifacts[ArtifactSlot::Shoulders] = ArtifactType::AngelWings;
          artifacts[ArtifactSlot::Spellbook] = ArtifactType::Spellbook;
          return artifacts;
        }()
      };
      // The binary representation of kHeroArtifacts.
      static constexpr std::string_view kBinaryData =
        "\xff\xff"    // Head
        "\x48\x00"    // Shoulders
        "\xff\xff"    // Neck
        "\xff\xff"    // RightHand
        "\xff\xff"    // LeftHand
        "\xff\xff"    // Torso
        "\xff\xff"    // RightRing
        "\x46\x00"    // LeftRing
        "\x62\x00"    // Feet
        "\xff\xff"    // Misc1
        "\xff\xff"    // Misc2
        "\xff\xff"    // Misc3
        "\xff\xff"    // Misc4
        "\xff\xff"    // WarMachine1
        "\xff\xff"    // WarMachine2
        "\xff\xff"    // WarMachine3
        "\xff\xff"    // WarMachine4
        "\x00\x00"    // Spellbook
        "\xff\xff"    // Misc5
        "\x00\x00"sv; // backpack

      REQUIRE(asByteVector(encodeViaH3MWriter(kHeroArtifacts)) == asByteVector(kBinaryData));
      REQUIRE(H3MReaderAdapter(kBinaryData).readHeroArtifacts() == kHeroArtifacts);
      REQUIRE(encodeAndDecodeJson(kHeroArtifacts) == kHeroArtifacts);
    }
    SECTION("Non-empty backpack")
    {
      const HeroArtifacts kHeroArtifacts{
        .equipped = []() consteval {
          auto artifacts = HeroArtifacts::kNoEquippedArtifacts;
          artifacts[ArtifactSlot::Feet] = ArtifactType::BootsOfSpeed;
          artifacts[ArtifactSlot::LeftRing] = ArtifactType::EquestriansGloves;
          artifacts[ArtifactSlot::Shoulders] = ArtifactType::AngelWings;
          artifacts[ArtifactSlot::Spellbook] = ArtifactType::Spellbook;
          return artifacts;
        }(),
        .backpack = {ArtifactType::AdmiralsHat, ArtifactType::ArmorOfTheDamned}
      };
      // The binary representation of kHeroArtifacts.
      static constexpr std::string_view kBinaryData =
        "\xff\xff"                          // Head
        "\x48\x00"                          // Shoulders
        "\xff\xff"                          // Neck
        "\xff\xff"                          // RightHand
        "\xff\xff"                          // LeftHand
        "\xff\xff"                          // Torso
        "\xff\xff"                          // RightRing
        "\x46\x00"                          // LeftRing
        "\x62\x00"                          // Feet
        "\xff\xff"                          // Misc1
        "\xff\xff"                          // Misc2
        "\xff\xff"                          // Misc3
        "\xff\xff"                          // Misc4
        "\xff\xff"                          // WarMachine1
        "\xff\xff"                          // WarMachine2
        "\xff\xff"                          // WarMachine3
        "\xff\xff"                          // WarMachine4
        "\x00\x00"                          // Spellbook
        "\xff\xff"                          // Misc5
        "\x02\x00" "\x88\x00" "\x84\x00"sv; // backpack

      REQUIRE(asByteVector(encodeViaH3MWriter(kHeroArtifacts)) == asByteVector(kBinaryData));
      REQUIRE(H3MReaderAdapter(kBinaryData).readHeroArtifacts() == kHeroArtifacts);
      REQUIRE(encodeAndDecodeJson(kHeroArtifacts) == kHeroArtifacts);
    }
  }
}
