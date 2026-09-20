#include "TestUtils_H3M.h"

#include <h3mtxt/Map/HeroSettings.h>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3MWriter;
using ::Testing_NS::H3MReaderAdapter;

namespace h3m
{
  TEST_CASE("H3M.HeroSettings", "[H3M]")
  {
    SECTION("None")
    {
      const HeroSettings kHeroSettings{
        .experience = std::nullopt,
        .secondary_skills = std::nullopt,
        .artifacts = std::nullopt,
        .biography = std::nullopt,
        .gender = Gender::Default,
        .spells = std::nullopt,
        .primary_skills = std::nullopt
      };
      // The binary representation of kHeroSettings.
      static constexpr std::string_view kBinaryData = "\x00\x00\x00\x00\xff\x00\x00"sv;
      REQUIRE(asByteVector(encodeViaH3MWriter(kHeroSettings)) == asByteVector(kBinaryData));
      REQUIRE(H3MReaderAdapter(kBinaryData).readHeroSettings() == kHeroSettings);
      REQUIRE(encodeAndDecodeJson(kHeroSettings) == kHeroSettings);
    }
    SECTION("Experience")
    {
      const HeroSettings kHeroSettings{
        .experience = 10000,
        .secondary_skills = std::nullopt,
        .artifacts = std::nullopt,
        .biography = std::nullopt,
        .gender = Gender::Default,
        .spells = std::nullopt,
        .primary_skills = std::nullopt
      };
      // The binary representation of kHeroSettings.
      static constexpr std::string_view kBinaryData =
        "\x01"
          "\x10\x27\x00\x00"
        "\x00\x00\x00\xff\x00\x00"sv;
      REQUIRE(asByteVector(encodeViaH3MWriter(kHeroSettings)) == asByteVector(kBinaryData));
      REQUIRE(H3MReaderAdapter(kBinaryData).readHeroSettings() == kHeroSettings);
      REQUIRE(encodeAndDecodeJson(kHeroSettings) == kHeroSettings);
    }
    SECTION("SecondarySkills")
    {
      const HeroSettings kHeroSettings{
        .experience = std::nullopt,
        .secondary_skills = std::vector<SecondarySkill>{
          SecondarySkill{.type = SecondarySkillType::Logistics, .level = 3},
          SecondarySkill{.type = SecondarySkillType::Wisdom, .level = 2}
        },
        .artifacts = std::nullopt,
        .biography = std::nullopt,
        .gender = Gender::Default,
        .spells = std::nullopt,
        .primary_skills = std::nullopt
      };
      // The binary representation of kHeroSettings.
      static constexpr std::string_view kBinaryData =
        "\x00"
        "\x01"
          "\x02\x00\x00\x00" "\x02\x03" "\x07\x02"
        "\x00\x00\xff\x00\x00"sv;
      REQUIRE(asByteVector(encodeViaH3MWriter(kHeroSettings)) == asByteVector(kBinaryData));
      REQUIRE(H3MReaderAdapter(kBinaryData).readHeroSettings() == kHeroSettings);
      REQUIRE(encodeAndDecodeJson(kHeroSettings) == kHeroSettings);
    }
    SECTION("Artifacts")
    {
      const HeroSettings kHeroSettings{
        .experience = std::nullopt,
        .secondary_skills = std::nullopt,
        .artifacts = HeroArtifacts{
          .equipped = []() consteval {
            auto artifacts = HeroArtifacts::kNoEquippedArtifacts;
            artifacts[ArtifactSlot::Feet] = ArtifactType::BootsOfSpeed;
            artifacts[ArtifactSlot::LeftRing] = ArtifactType::EquestriansGloves;
            return artifacts;
          }(),
          .backpack = {ArtifactType::TomeOfEarthMagic}
        },
        .biography = std::nullopt,
        .gender = Gender::Default,
        .spells = std::nullopt,
        .primary_skills = std::nullopt
      };
      // The binary representation of kHeroSettings.
      static constexpr std::string_view kBinaryData =
        "\x00\x00"
        "\x01"
          "\xff\xff"  // Head
          "\xff\xff"  // Shoulders
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
          "\xff\xff"  // Spellbook
          "\xff\xff"  // Misc5
          "\x01\x00"  // backpack
            "\x59\x00"
        "\x00\xff\x00\x00"sv;
      REQUIRE(asByteVector(encodeViaH3MWriter(kHeroSettings)) == asByteVector(kBinaryData));
      REQUIRE(H3MReaderAdapter(kBinaryData).readHeroSettings() == kHeroSettings);
      REQUIRE(encodeAndDecodeJson(kHeroSettings) == kHeroSettings);
    }
    SECTION("Biography")
    {
      const HeroSettings kHeroSettings{
        .experience = std::nullopt,
        .secondary_skills = std::nullopt,
        .artifacts = std::nullopt,
        .biography = "Born on a Monday,\nBuried on Sunday.",
        .gender = Gender::Default,
        .spells = std::nullopt,
        .primary_skills = std::nullopt
      };
      // The binary representation of kHeroSettings.
      static constexpr std::string_view kBinaryData =
        "\x00\x00\x00"
        "\x01"
          "\x23\x00\x00\x00" "Born on a Monday,\nBuried on Sunday."
        "\xff\x00\x00"sv;
      REQUIRE(asByteVector(encodeViaH3MWriter(kHeroSettings)) == asByteVector(kBinaryData));
      REQUIRE(H3MReaderAdapter(kBinaryData).readHeroSettings() == kHeroSettings);
      REQUIRE(encodeAndDecodeJson(kHeroSettings) == kHeroSettings);
    }
    SECTION("Gender")
    {
      const HeroSettings kHeroSettings{
        .experience = std::nullopt,
        .secondary_skills = std::nullopt,
        .artifacts = std::nullopt,
        .biography = std::nullopt,
        .gender = Gender::Male,
        .spells = std::nullopt,
        .primary_skills = std::nullopt
      };
      // The binary representation of kHeroSettings.
      static constexpr std::string_view kBinaryData = "\x00\x00\x00\x00\x00\x00\x00"sv;
      REQUIRE(asByteVector(encodeViaH3MWriter(kHeroSettings)) == asByteVector(kBinaryData));
      REQUIRE(H3MReaderAdapter(kBinaryData).readHeroSettings() == kHeroSettings);
      REQUIRE(encodeAndDecodeJson(kHeroSettings) == kHeroSettings);
    }
    SECTION("Spells")
    {
      const HeroSettings kHeroSettings{
        .experience = std::nullopt,
        .secondary_skills = std::nullopt,
        .artifacts = std::nullopt,
        .biography = std::nullopt,
        .gender = Gender::Default,
        .spells = []() consteval {
          SpellsBitmask bitmask;
          bitmask.set(SpellType::TownPortal, true);
          bitmask.set(SpellType::Armageddon, true);
          return bitmask;
         }(),
        .primary_skills = std::nullopt
      };
      // The binary representation of kHeroSettings.
      static constexpr std::string_view kBinaryData =
        "\x00\x00\x00\x00\xff"
        "\x01"
          "\x00\x02\x00\x04\x00\x00\x00\x00\x00"
        "\x00"sv;
      REQUIRE(asByteVector(encodeViaH3MWriter(kHeroSettings)) == asByteVector(kBinaryData));
      REQUIRE(H3MReaderAdapter(kBinaryData).readHeroSettings() == kHeroSettings);
      REQUIRE(encodeAndDecodeJson(kHeroSettings) == kHeroSettings);
    }
    SECTION("PrimarySkills")
    {
      const HeroSettings kHeroSettings{
        .experience = std::nullopt,
        .secondary_skills = std::nullopt,
        .artifacts = std::nullopt,
        .biography = std::nullopt,
        .gender = Gender::Default,
        .spells = std::nullopt,
        .primary_skills = []() consteval {
          PrimarySkills primary_skills;
          primary_skills[PrimarySkillType::Attack] = 1;
          primary_skills[PrimarySkillType::Defense] = 2;
          primary_skills[PrimarySkillType::SpellPower] = 3;
          primary_skills[PrimarySkillType::Knowledge] = 4;
          return primary_skills;
        }()
      };
      // The binary representation of kHeroSettings.
      static constexpr std::string_view kBinaryData =
        "\x00\x00\x00\x00\xff\x00"
        "\x01"
          "\x01\x02\x03\x04"sv;
      REQUIRE(asByteVector(encodeViaH3MWriter(kHeroSettings)) == asByteVector(kBinaryData));
      REQUIRE(H3MReaderAdapter(kBinaryData).readHeroSettings() == kHeroSettings);
      REQUIRE(encodeAndDecodeJson(kHeroSettings) == kHeroSettings);
    }
    SECTION("ALL")
    {
      const HeroSettings kHeroSettings{
        .experience = 10000,
        .secondary_skills = std::vector<SecondarySkill>{
          SecondarySkill{.type = SecondarySkillType::Logistics, .level = 3},
          SecondarySkill{.type = SecondarySkillType::Wisdom, .level = 2}
        },
        .artifacts = HeroArtifacts{
          .equipped = []() consteval {
            auto artifacts = HeroArtifacts::kNoEquippedArtifacts;
            artifacts[ArtifactSlot::Feet] = ArtifactType::BootsOfSpeed;
            artifacts[ArtifactSlot::LeftRing] = ArtifactType::EquestriansGloves;
            return artifacts;
          }(),
          .backpack = {ArtifactType::TomeOfEarthMagic}
        },
        .biography = "Born on a Monday,\nBuried on Sunday.",
        .gender = Gender::Male,
        .spells = []() consteval {
          SpellsBitmask bitmask;
          bitmask.set(SpellType::TownPortal, true);
          bitmask.set(SpellType::Armageddon, true);
          return bitmask;
         }(),
        .primary_skills = []() consteval {
          PrimarySkills primary_skills;
          primary_skills[PrimarySkillType::Attack] = 1;
          primary_skills[PrimarySkillType::Defense] = 2;
          primary_skills[PrimarySkillType::SpellPower] = 3;
          primary_skills[PrimarySkillType::Knowledge] = 4;
          return primary_skills;
        }()
      };
      // The binary representation of kHeroSettings.
      static constexpr std::string_view kBinaryData =
        "\x01"                                     // Experience
          "\x10\x27\x00\x00"
        "\x01"                                     // Secondary skills
          "\x02\x00\x00\x00" "\x02\x03" "\x07\x02"
        "\x01"                                     // Artifacts
          "\xff\xff"  // Head
          "\xff\xff"  // Shoulders
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
          "\xff\xff"  // Spellbook
          "\xff\xff"  // Misc5
          "\x01\x00"  // backpack
            "\x59\x00"
        "\x01"                                     // Biography
          "\x23\x00\x00\x00" "Born on a Monday,\nBuried on Sunday."
        "\x00"                                     // Gender
        "\x01"                                     // Spells
          "\x00\x02\x00\x04\x00\x00\x00\x00\x00"
        "\x01"                                     // Primary skills
          "\x01\x02\x03\x04"sv;
      REQUIRE(asByteVector(encodeViaH3MWriter(kHeroSettings)) == asByteVector(kBinaryData));
      REQUIRE(H3MReaderAdapter(kBinaryData).readHeroSettings() == kHeroSettings);
      REQUIRE(encodeAndDecodeJson(kHeroSettings) == kHeroSettings);
    }
  }
}
