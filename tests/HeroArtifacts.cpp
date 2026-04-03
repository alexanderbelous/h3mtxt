#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/HeroArtifacts.h>

#include <catch2/catch_test_macros.hpp>

#include <iterator>
#include <sstream>
#include <string>
#include <string_view>

namespace h3m
{
  namespace
  {
    // Encodes h3m::HeroArtifacts via H3MWriter.
    // \param hero_artifacts - input HeroArtifacts.
    // \return std::string storing the encoded data.
    std::string encodeHeroArtifacts(const HeroArtifacts& hero_artifacts)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(hero_artifacts);
      return std::move(stream).str();
    }

    // Decodes h3m::HeroArtifacts via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::HeroArtifacts decoded from @encoded_data.
    HeroArtifacts decodeHeroArtifacts(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readHeroArtifacts();
    }
  }

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
      static constexpr char kBinaryDataCStr[] =
        "\xff\xff"  // Head
        "\x48\x00"  // Shoulders
        "\xff\xff"  // Neck
        "\xff\xff"  // RightHand
        "\xff\xff"  // LeftHand
        "\xff\xff"  // Torso
        "\xff\xff"  // RightRing
        "\x46\x00"  // LeftRing
        "\x62\x00"  // Feet
        "\xff\xff"  // Misc1
        "\xff\xff"  // Misc2
        "\xff\xff"  // Misc3
        "\xff\xff"  // Misc4
        "\xff\xff"  // WarMachine1
        "\xff\xff"  // WarMachine2
        "\xff\xff"  // WarMachine3
        "\xff\xff"  // WarMachine4
        "\x00\x00"  // Spellbook
        "\xff\xff"  // Misc5
        "\x00\x00"; // backpack
      // std::string_view into kBinaryDataCStr.
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(encodeHeroArtifacts(kHeroArtifacts) == kBinaryData);
      REQUIRE(decodeHeroArtifacts(kBinaryData) == kHeroArtifacts);
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
      static constexpr char kBinaryDataCStr[] =
        "\xff\xff"                        // Head
        "\x48\x00"                        // Shoulders
        "\xff\xff"                        // Neck
        "\xff\xff"                        // RightHand
        "\xff\xff"                        // LeftHand
        "\xff\xff"                        // Torso
        "\xff\xff"                        // RightRing
        "\x46\x00"                        // LeftRing
        "\x62\x00"                        // Feet
        "\xff\xff"                        // Misc1
        "\xff\xff"                        // Misc2
        "\xff\xff"                        // Misc3
        "\xff\xff"                        // Misc4
        "\xff\xff"                        // WarMachine1
        "\xff\xff"                        // WarMachine2
        "\xff\xff"                        // WarMachine3
        "\xff\xff"                        // WarMachine4
        "\x00\x00"                        // Spellbook
        "\xff\xff"                        // Misc5
        "\x02\x00" "\x88\x00" "\x84\x00"; // backpack
      // std::string_view into kBinaryDataCStr.
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(encodeHeroArtifacts(kHeroArtifacts) == kBinaryData);
      REQUIRE(decodeHeroArtifacts(kBinaryData) == kHeroArtifacts);
    }
  }
}
