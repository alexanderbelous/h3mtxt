#include "../Utils.h"

#include <h3mtxt/H3JsonReader/H3CJsonReader/H3CJsonReader.h>
#include <h3mtxt/H3JsonWriter/H3CJsonWriter/H3CJsonWriter.h>
#include <h3mtxt/H3Reader/H3CReader/H3CReader.h>
#include <h3mtxt/H3Writer/H3CWriter/H3CWriter.h>
#include <h3mtxt/Campaign/StartingBonus.h>
#include <h3mtxt/Map/Constants/HeroType.h>

#include <catch2/catch_test_macros.hpp>

#include <iterator>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;

namespace h3m
{
  namespace
  {
    // Encodes h3m::StartingBonusDetails via H3CWriter.
    // \param starting_bonus_details - input StartingBonusDetails.
    // \return std::string storing the encoded data.
    template<StartingBonusType T>
    std::string encodeStartingBonusDetails(const StartingBonusDetails<T>& starting_bonus_details)
    {
      std::ostringstream stream;
      H3CWriter{ stream }.writeData(starting_bonus_details);
      return std::move(stream).str();
    }

    // Decodes h3m::StartingBonusDetails via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::StartingBonusDetails decoded from @encoded_data.
    template<StartingBonusType T>
    StartingBonusDetails<T> decodeStartingBonusDetails(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3CReader{ stream }.readStartingBonusDetails<T>();
    }

    // Encodes h3m::StartingBonus via H3CWriter.
    // \param starting_bonus - input StartingBonus.
    // \return std::string storing the encoded data.
    std::string encodeStartingBonus(const StartingBonus& starting_bonus)
    {
      std::ostringstream stream;
      H3CWriter{ stream }.writeData(starting_bonus);
      return std::move(stream).str();
    }

    // Decodes h3m::StartingBonus via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::StartingBonus decoded from @encoded_data.
    StartingBonus decodeStartingBonus(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3CReader{ stream }.readStartingBonus();
    }
  }

  TEST_CASE("H3M.StartingBonusDetails.Spell", "[H3C]")
  {
    // StartingBonusDetails used in this test.
    static constexpr StartingBonusDetails<StartingBonusType::Spell> kStartingBonusDetails{
      .hero = static_cast<std::uint16_t>(HeroType::Gunnar),
      .spell = SpellType::TownPortal
    };

    // The binary representation of kStartingBonusDetails.
    static constexpr char kBinaryDataCStr[] = "\x55\x00" "\x09";

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeStartingBonusDetails(kStartingBonusDetails)) == asByteVector(kBinaryData));
    REQUIRE(decodeStartingBonusDetails<StartingBonusType::Spell>(kBinaryData) == kStartingBonusDetails);
    REQUIRE(encodeAndDecodeJson(kStartingBonusDetails) == kStartingBonusDetails);
  }

  TEST_CASE("H3M.StartingBonusDetails.Creature", "[H3C]")
  {
    // StartingBonusDetails used in this test.
    static constexpr StartingBonusDetails<StartingBonusType::Creature> kStartingBonusDetails{
      .hero = static_cast<std::uint16_t>(HeroType::Gunnar),
      .creature_stack = {
        .type = CreatureType::MinotaurKing,
        .count = 12
      }
    };

    // The binary representation of kStartingBonusDetails.
    static constexpr char kBinaryDataCStr[] = "\x55\x00" "\x4f\x00" "\x0c\x00";

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeStartingBonusDetails(kStartingBonusDetails)) == asByteVector(kBinaryData));
    REQUIRE(decodeStartingBonusDetails<StartingBonusType::Creature>(kBinaryData) == kStartingBonusDetails);
    REQUIRE(encodeAndDecodeJson(kStartingBonusDetails) == kStartingBonusDetails);
  }

  TEST_CASE("H3M.StartingBonusDetails.Building", "[H3C]")
  {
    // StartingBonusDetails used in this test.
    static constexpr StartingBonusDetails<StartingBonusType::Building> kStartingBonusDetails{
      .building = TownBuildingType::Dwelling5
    };

    // The binary representation of kStartingBonusDetails.
    static constexpr char kBinaryDataCStr[] = "\x22";

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeStartingBonusDetails(kStartingBonusDetails)) == asByteVector(kBinaryData));
    REQUIRE(decodeStartingBonusDetails<StartingBonusType::Building>(kBinaryData) == kStartingBonusDetails);
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
    static constexpr char kBinaryDataCStr[] = "\x55\x00" "\x46\x00";

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeStartingBonusDetails(kStartingBonusDetails)) == asByteVector(kBinaryData));
    REQUIRE(decodeStartingBonusDetails<StartingBonusType::Artifact>(kBinaryData) == kStartingBonusDetails);
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
    static constexpr char kBinaryDataCStr[] = "\x55\x00" "\x09";

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeStartingBonusDetails(kStartingBonusDetails)) == asByteVector(kBinaryData));
    REQUIRE(decodeStartingBonusDetails<StartingBonusType::SpellScroll>(kBinaryData) == kStartingBonusDetails);
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
    static constexpr char kBinaryDataCStr[] = "\x55\x00" "\x04\x03\x00\x00";

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeStartingBonusDetails(kStartingBonusDetails)) == asByteVector(kBinaryData));
    REQUIRE(decodeStartingBonusDetails<StartingBonusType::PrimarySkills>(kBinaryData) == kStartingBonusDetails);
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
    static constexpr char kBinaryDataCStr[] = "\x55\x00" "\x11" "\x03";

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeStartingBonusDetails(kStartingBonusDetails)) == asByteVector(kBinaryData));
    REQUIRE(decodeStartingBonusDetails<StartingBonusType::SecondarySkill>(kBinaryData) == kStartingBonusDetails);
    REQUIRE(encodeAndDecodeJson(kStartingBonusDetails) == kStartingBonusDetails);
  }

  TEST_CASE("H3M.StartingBonusDetails.Resource", "[H3C]")
  {
    // StartingBonusDetails used in this test.
    static constexpr StartingBonusDetails<StartingBonusType::Resource> kStartingBonusDetails{
      .type = StartingBonusResourceType::MercurySulfurCrystalGems,
      .amount = 5
    };

    // The binary representation of kStartingBonusDetails.
    static constexpr char kBinaryDataCStr[] = "\xfe" "\x05\x00\x00\x00";

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeStartingBonusDetails(kStartingBonusDetails)) == asByteVector(kBinaryData));
    REQUIRE(decodeStartingBonusDetails<StartingBonusType::Resource>(kBinaryData) == kStartingBonusDetails);
    REQUIRE(encodeAndDecodeJson(kStartingBonusDetails) == kStartingBonusDetails);
  }

  TEST_CASE("H3M.StartingBonus", "[H3C]")
  {
    // StartingBonus used in this test.
    static constexpr StartingBonus kStartingBonus = {
      .details = StartingBonusDetails<StartingBonusType::Resource>{
        .type = StartingBonusResourceType::WoodOre,
        .amount = 10
      }
    };

    // The binary representation of kStartingBonus.
    static constexpr char kBinaryDataCStr[] = "\x07" "\xfd" "\x0a\x00\x00\x00";

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kStartingBonus.type() == StartingBonusType::Resource);
    REQUIRE(asByteVector(encodeStartingBonus(kStartingBonus)) == asByteVector(kBinaryData));
    REQUIRE(decodeStartingBonus(kBinaryData) == kStartingBonus);
    REQUIRE(encodeAndDecodeJson(kStartingBonus) == kStartingBonus);
  }
}
