#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/HeroSettings.h>

#include <catch2/catch_test_macros.hpp>

#include <iterator>
#include <sstream>
#include <string>
#include <string_view>

namespace h3m
{
  namespace
  {
    // Encodes h3m::HeroSettings via H3MWriter.
    // \param hero_settings - input HeroSettings.
    // \return std::string storing the encoded data.
    std::string encodeHeroSettings(const HeroSettings& hero_settings)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(hero_settings);
      return std::move(stream).str();
    }

    // Decodes h3m::HeroSettings via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::HeroSettings decoded from @encoded_data.
    HeroSettings decodeHeroSettings(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readHeroSettings();
    }
  }

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
      static constexpr char kBinaryDataCStr[] = "\x00\x00\x00\x00\xff\x00\x00";
      // std::string_view into kBinaryDataCStr.
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(encodeHeroSettings(kHeroSettings) == kBinaryData);
      REQUIRE(decodeHeroSettings(kBinaryData) == kHeroSettings);
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
      static constexpr char kBinaryDataCStr[] =
        "\x01"
          "\x10\x27\x00\x00"
        "\x00\x00\x00\xff\x00\x00";
      // std::string_view into kBinaryDataCStr.
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(encodeHeroSettings(kHeroSettings) == kBinaryData);
      REQUIRE(decodeHeroSettings(kBinaryData) == kHeroSettings);
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
      static constexpr char kBinaryDataCStr[] =
        "\x00"
        "\x01"
          "\x02\x00\x00\x00" "\x02\x03" "\x07\x02"
        "\x00\x00\xff\x00\x00";
      // std::string_view into kBinaryDataCStr.
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(encodeHeroSettings(kHeroSettings) == kBinaryData);
      REQUIRE(decodeHeroSettings(kBinaryData) == kHeroSettings);
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
      static constexpr char kBinaryDataCStr[] =
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
        "\x00\xff\x00\x00";
      // std::string_view into kBinaryDataCStr.
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(encodeHeroSettings(kHeroSettings) == kBinaryData);
      REQUIRE(decodeHeroSettings(kBinaryData) == kHeroSettings);
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
      static constexpr char kBinaryDataCStr[] =
        "\x00\x00\x00"
        "\x01"
          "\x23\x00\x00\x00" "Born on a Monday,\nBuried on Sunday."
        "\xff\x00\x00";
      // std::string_view into kBinaryDataCStr.
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(encodeHeroSettings(kHeroSettings) == kBinaryData);
      REQUIRE(decodeHeroSettings(kBinaryData) == kHeroSettings);
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
      static constexpr char kBinaryDataCStr[] = "\x00\x00\x00\x00\x00\x00\x00";
      // std::string_view into kBinaryDataCStr.
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(encodeHeroSettings(kHeroSettings) == kBinaryData);
      REQUIRE(decodeHeroSettings(kBinaryData) == kHeroSettings);
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
      static constexpr char kBinaryDataCStr[] =
        "\x00\x00\x00\x00\xff"
        "\x01"
          "\x00\x02\x00\x04\x00\x00\x00\x00\x00"
        "\x00";
      // std::string_view into kBinaryDataCStr.
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(encodeHeroSettings(kHeroSettings) == kBinaryData);
      REQUIRE(decodeHeroSettings(kBinaryData) == kHeroSettings);
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
        .primary_skills = PrimarySkills{
          .attack = 1,
          .defense = 2,
          .spell_power = 3,
          .knowledge = 4
        }
      };
      // The binary representation of kHeroSettings.
      static constexpr char kBinaryDataCStr[] =
        "\x00\x00\x00\x00\xff\x00"
        "\x01"
          "\x01\x02\x03\x04";
      // std::string_view into kBinaryDataCStr.
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(encodeHeroSettings(kHeroSettings) == kBinaryData);
      REQUIRE(decodeHeroSettings(kBinaryData) == kHeroSettings);
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
        .primary_skills = PrimarySkills{
          .attack = 1,
          .defense = 2,
          .spell_power = 3,
          .knowledge = 4
        }
      };
      // The binary representation of kHeroSettings.
      static constexpr char kBinaryDataCStr[] =
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
          "\x01\x02\x03\x04";
      // std::string_view into kBinaryDataCStr.
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };
      REQUIRE(encodeHeroSettings(kHeroSettings) == kBinaryData);
      REQUIRE(decodeHeroSettings(kBinaryData) == kHeroSettings);
    }
  }
}
