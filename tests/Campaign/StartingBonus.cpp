#include "TestUtils_H3C.h"

#include <h3mtxt/Campaign/StartingBonus.h>
#include <h3mtxt/Map/Constants/HeroType.h>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3CWriter;
using ::Testing_NS::H3CReaderAdapter;

namespace h3m
{
  TEST_CASE("H3M.StartingBonusDetails.Spell", "[H3C]")
  {
    // StartingBonusDetails used in this test.
    static constexpr StartingBonusDetails<StartingBonusType::Spell> kStartingBonusDetails{
      .hero = static_cast<std::uint16_t>(HeroType::Gunnar),
      .spell = SpellType::TownPortal
    };

    // The binary representation of kStartingBonusDetails.
    static constexpr std::string_view kBinaryData = "\x55\x00" "\x09" ""sv;

    REQUIRE(asByteVector(encodeViaH3CWriter(kStartingBonusDetails)) == asByteVector(kBinaryData));
    REQUIRE(H3CReaderAdapter(kBinaryData).readStartingBonusDetails<StartingBonusType::Spell>() ==
            kStartingBonusDetails);
    REQUIRE(encodeAndDecodeJson(kStartingBonusDetails) == kStartingBonusDetails);
  }

  TEST_CASE("H3M.StartingBonusDetails.Creature", "[H3C]")
  {
    // StartingBonusDetails used in this test.
    static constexpr StartingBonusDetails<StartingBonusType::Creature> kStartingBonusDetails{
      .hero = static_cast<std::uint16_t>(HeroType::Gunnar),
      .creature_stack = {
        .type = CreatureType::MinotaurKing,
        .quantity = 12
      }
    };

    // The binary representation of kStartingBonusDetails.
    static constexpr std::string_view kBinaryData = "\x55\x00" "\x4f\x00" "\x0c\x00" ""sv;

    REQUIRE(asByteVector(encodeViaH3CWriter(kStartingBonusDetails)) == asByteVector(kBinaryData));
    REQUIRE(H3CReaderAdapter(kBinaryData).readStartingBonusDetails<StartingBonusType::Creature>() ==
            kStartingBonusDetails);
    REQUIRE(encodeAndDecodeJson(kStartingBonusDetails) == kStartingBonusDetails);
  }

  TEST_CASE("H3M.StartingBonusDetails.Building", "[H3C]")
  {
    // StartingBonusDetails used in this test.
    static constexpr StartingBonusDetails<StartingBonusType::Building> kStartingBonusDetails{
      .building = TownBuildingType::Dwelling5
    };

    // The binary representation of kStartingBonusDetails.
    static constexpr std::string_view kBinaryData = "\x22" ""sv;

    REQUIRE(asByteVector(encodeViaH3CWriter(kStartingBonusDetails)) == asByteVector(kBinaryData));
    REQUIRE(H3CReaderAdapter(kBinaryData).readStartingBonusDetails<StartingBonusType::Building>() ==
            kStartingBonusDetails);
    REQUIRE(encodeAndDecodeJson(kStartingBonusDetails) == kStartingBonusDetails);
  }

  TEST_CASE("H3M.StartingBonusDetails.Artifact", "[H3C]")
  {
    // StartingBonusDetails used in this test.
    static constexpr StartingBonusDetails<StartingBonusType::Artifact> kStartingBonusDetails{
      .hero = static_cast<std::uint16_t>(HeroType::Gunnar),
      .artifact = ArtifactType::EquestriansGloves
    };

    // The binary representation of kStartingBonusDetails.
    static constexpr std::string_view kBinaryData = "\x55\x00" "\x46\x00" ""sv;

    REQUIRE(asByteVector(encodeViaH3CWriter(kStartingBonusDetails)) == asByteVector(kBinaryData));
    REQUIRE(H3CReaderAdapter(kBinaryData).readStartingBonusDetails<StartingBonusType::Artifact>() ==
            kStartingBonusDetails);
    REQUIRE(encodeAndDecodeJson(kStartingBonusDetails) == kStartingBonusDetails);
  }

  TEST_CASE("H3M.StartingBonusDetails.SpellScroll", "[H3C]")
  {
    // StartingBonusDetails used in this test.
    static constexpr StartingBonusDetails<StartingBonusType::SpellScroll> kStartingBonusDetails{
      .hero = static_cast<std::uint16_t>(HeroType::Gunnar),
      .spell = SpellType::TownPortal
    };

    // The binary representation of kStartingBonusDetails.
    static constexpr std::string_view kBinaryData = "\x55\x00" "\x09" ""sv;

    REQUIRE(asByteVector(encodeViaH3CWriter(kStartingBonusDetails)) == asByteVector(kBinaryData));
    REQUIRE(H3CReaderAdapter(kBinaryData).readStartingBonusDetails<StartingBonusType::SpellScroll>() ==
            kStartingBonusDetails);
    REQUIRE(encodeAndDecodeJson(kStartingBonusDetails) == kStartingBonusDetails);
  }

  TEST_CASE("H3M.StartingBonusDetails.PrimarySkills", "[H3C]")
  {
    // StartingBonusDetails used in this test.
    static constexpr StartingBonusDetails<StartingBonusType::PrimarySkills> kStartingBonusDetails{
      .hero = static_cast<std::uint16_t>(HeroType::Gunnar),
      .skills = []() consteval {
        PrimarySkills skills;
        skills[PrimarySkillType::Attack] = 4;
        skills[PrimarySkillType::Defense] = 3;
        return skills;
      }()
    };

    // The binary representation of kStartingBonusDetails.
    static constexpr std::string_view kBinaryData = "\x55\x00" "\x04\x03\x00\x00" ""sv;

    REQUIRE(asByteVector(encodeViaH3CWriter(kStartingBonusDetails)) == asByteVector(kBinaryData));
    REQUIRE(H3CReaderAdapter(kBinaryData).readStartingBonusDetails<StartingBonusType::PrimarySkills>() ==
            kStartingBonusDetails);
    REQUIRE(encodeAndDecodeJson(kStartingBonusDetails) == kStartingBonusDetails);
  }

  TEST_CASE("H3M.StartingBonusDetails.SecondarySkill", "[H3C]")
  {
    // StartingBonusDetails used in this test.
    static constexpr StartingBonusDetails<StartingBonusType::SecondarySkill> kStartingBonusDetails{
      .hero = static_cast<std::uint16_t>(HeroType::Gunnar),
      .skill = {
        .type = SecondarySkillType::EarthMagic,
        .level = 3
      }
    };

    // The binary representation of kStartingBonusDetails.
    static constexpr std::string_view kBinaryData = "\x55\x00" "\x11" "\x03" ""sv;

    REQUIRE(asByteVector(encodeViaH3CWriter(kStartingBonusDetails)) == asByteVector(kBinaryData));
    REQUIRE(H3CReaderAdapter(kBinaryData).readStartingBonusDetails<StartingBonusType::SecondarySkill>() ==
            kStartingBonusDetails);
    REQUIRE(encodeAndDecodeJson(kStartingBonusDetails) == kStartingBonusDetails);
  }

  TEST_CASE("H3M.StartingBonusDetails.Resource", "[H3C]")
  {
    // StartingBonusDetails used in this test.
    static constexpr StartingBonusDetails<StartingBonusType::Resource> kStartingBonusDetails{
      .resource = {
        .type = ResourceType::MercurySulfurCrystalGems,
        .quantity = 5
      }
    };

    // The binary representation of kStartingBonusDetails.
    static constexpr std::string_view kBinaryData = "\xfe" "\x05\x00\x00\x00" ""sv;

    REQUIRE(asByteVector(encodeViaH3CWriter(kStartingBonusDetails)) == asByteVector(kBinaryData));
    REQUIRE(H3CReaderAdapter(kBinaryData).readStartingBonusDetails<StartingBonusType::Resource>() ==
            kStartingBonusDetails);
    REQUIRE(encodeAndDecodeJson(kStartingBonusDetails) == kStartingBonusDetails);
  }

  TEST_CASE("H3M.StartingBonus", "[H3C]")
  {
    // StartingBonus used in this test.
    static constexpr StartingBonus kStartingBonus = {
      .details = StartingBonusDetails<StartingBonusType::Resource>{
        TypedQuantity<ResourceType, std::int32_t>{
          .type = ResourceType::WoodOre,
          .quantity = 10
        }
      }
    };

    // The binary representation of kStartingBonus.
    static constexpr std::string_view kBinaryData = "\x07" "\xfd" "\x0a\x00\x00\x00" ""sv;

    static_assert(kStartingBonus.type() == StartingBonusType::Resource);
    REQUIRE(asByteVector(encodeViaH3CWriter(kStartingBonus)) == asByteVector(kBinaryData));
    REQUIRE(H3CReaderAdapter(kBinaryData).readStartingBonus() == kStartingBonus);
    REQUIRE(encodeAndDecodeJson(kStartingBonus) == kStartingBonus);
  }
}
