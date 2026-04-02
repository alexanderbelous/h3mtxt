#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/VictoryCondition.h>

#include <catch2/catch_test_macros.hpp>

#include <iterator>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

namespace h3m
{
  namespace
  {
    // Encodes h3m::VictoryCondition via H3MWriter.
    // \param victory_condition - input VictoryCondition.
    // \return std::string storing the encoded data.
    std::string encodeVictoryCondition(const VictoryCondition& victory_condition)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(victory_condition);
      return std::move(stream).str();
    }

    // Decodes h3m::VictoryCondition via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::VictoryCondition decoded from @encoded_data.
    VictoryCondition decodeVictoryCondition(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readVictoryCondition();
    }
  }

  TEST_CASE("H3M.VictoryCondition.AcquireArtifact", "[H3M]")
  {
    constexpr VictoryCondition kVictoryCondition = {
      VictoryConditionDetails<VictoryConditionType::AcquireArtifact>{
        SpecialVictoryConditionBase{.allow_normal_win = 1, .applies_to_computer = 1},
        ArtifactType::ArmageddonsBlade
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x00\x01\x01\x80\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kVictoryCondition.type() == VictoryConditionType::AcquireArtifact);
    REQUIRE(encodeVictoryCondition(kVictoryCondition) == kBinaryData);
    REQUIRE(decodeVictoryCondition(kBinaryData) == kVictoryCondition);
  }

  TEST_CASE("H3M.VictoryCondition.AccumulateCreatures", "[H3M]")
  {
    constexpr VictoryCondition kVictoryCondition = {
      VictoryConditionDetails<VictoryConditionType::AccumulateCreatures>{
        SpecialVictoryConditionBase{.allow_normal_win = 0, .applies_to_computer = 0},
        CreatureType::AzureDragon,
        99
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x01\x00\x00\x84\x00\x63\x00\x00\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kVictoryCondition.type() == VictoryConditionType::AccumulateCreatures);
    REQUIRE(encodeVictoryCondition(kVictoryCondition) == kBinaryData);
    REQUIRE(decodeVictoryCondition(kBinaryData) == kVictoryCondition);
  }

  TEST_CASE("H3M.VictoryCondition.AccumulateResources", "[H3M]")
  {
    constexpr VictoryCondition kVictoryCondition = {
      VictoryConditionDetails<VictoryConditionType::AccumulateResources>{
        SpecialVictoryConditionBase{.allow_normal_win = 0, .applies_to_computer = 0},
        ResourceType::Gems,
        100
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x02\x00\x00\x05\x64\x00\x00\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kVictoryCondition.type() == VictoryConditionType::AccumulateResources);
    REQUIRE(encodeVictoryCondition(kVictoryCondition) == kBinaryData);
    REQUIRE(decodeVictoryCondition(kBinaryData) == kVictoryCondition);
  }

  TEST_CASE("H3M.VictoryCondition.UpgradeTown", "[H3M]")
  {
    constexpr VictoryCondition kVictoryCondition = {
      VictoryConditionDetails<VictoryConditionType::UpgradeTown>{
        SpecialVictoryConditionBase{.allow_normal_win = 0, .applies_to_computer = 0},
        Coordinates{.x = 10, .y = 20, .z = 1},
        2, // Capitol
        0  // Fort
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x03\x00\x00\x0a\x14\x01\x02\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kVictoryCondition.type() == VictoryConditionType::UpgradeTown);
    REQUIRE(encodeVictoryCondition(kVictoryCondition) == kBinaryData);
    REQUIRE(decodeVictoryCondition(kBinaryData) == kVictoryCondition);
  }

  TEST_CASE("H3M.VictoryCondition.BuildGrail", "[H3M]")
  {
    constexpr VictoryCondition kVictoryCondition = {
      VictoryConditionDetails<VictoryConditionType::BuildGrail>{
        SpecialVictoryConditionBase{.allow_normal_win = 0, .applies_to_computer = 0},
        Coordinates{.x = 10, .y = 20, .z = 1}
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x04\x00\x00\x0a\x14\x01";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kVictoryCondition.type() == VictoryConditionType::BuildGrail);
    REQUIRE(encodeVictoryCondition(kVictoryCondition) == kBinaryData);
    REQUIRE(decodeVictoryCondition(kBinaryData) == kVictoryCondition);
  }

  TEST_CASE("H3M.VictoryCondition.DefeatHero", "[H3M]")
  {
    constexpr VictoryCondition kVictoryCondition = {
      VictoryConditionDetails<VictoryConditionType::DefeatHero>{
        SpecialVictoryConditionBase{.allow_normal_win = 0, .applies_to_computer = 0},
        Coordinates{.x = 10, .y = 20, .z = 1}
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x05\x00\x00\x0a\x14\x01";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kVictoryCondition.type() == VictoryConditionType::DefeatHero);
    REQUIRE(encodeVictoryCondition(kVictoryCondition) == kBinaryData);
    REQUIRE(decodeVictoryCondition(kBinaryData) == kVictoryCondition);
  }

  TEST_CASE("H3M.VictoryCondition.CaptureTown", "[H3M]")
  {
    constexpr VictoryCondition kVictoryCondition = {
      VictoryConditionDetails<VictoryConditionType::CaptureTown>{
        SpecialVictoryConditionBase{.allow_normal_win = 0, .applies_to_computer = 0},
        Coordinates{.x = 10, .y = 20, .z = 1}
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x06\x00\x00\x0a\x14\x01";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kVictoryCondition.type() == VictoryConditionType::CaptureTown);
    REQUIRE(encodeVictoryCondition(kVictoryCondition) == kBinaryData);
    REQUIRE(decodeVictoryCondition(kBinaryData) == kVictoryCondition);
  }

  TEST_CASE("H3M.VictoryCondition.DefeatMonster", "[H3M]")
  {
    constexpr VictoryCondition kVictoryCondition = {
      VictoryConditionDetails<VictoryConditionType::DefeatMonster>{
        SpecialVictoryConditionBase{.allow_normal_win = 0, .applies_to_computer = 0},
        Coordinates{.x = 10, .y = 20, .z = 1}
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x07\x00\x00\x0a\x14\x01";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kVictoryCondition.type() == VictoryConditionType::DefeatMonster);
    REQUIRE(encodeVictoryCondition(kVictoryCondition) == kBinaryData);
    REQUIRE(decodeVictoryCondition(kBinaryData) == kVictoryCondition);
  }

  TEST_CASE("H3M.VictoryCondition.FlagDwellings", "[H3M]")
  {
    constexpr VictoryCondition kVictoryCondition = {
      VictoryConditionDetails<VictoryConditionType::FlagDwellings>{
        SpecialVictoryConditionBase{.allow_normal_win = 1, .applies_to_computer = 0}
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x08\x01\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kVictoryCondition.type() == VictoryConditionType::FlagDwellings);
    REQUIRE(encodeVictoryCondition(kVictoryCondition) == kBinaryData);
    REQUIRE(decodeVictoryCondition(kBinaryData) == kVictoryCondition);
  }

  TEST_CASE("H3M.VictoryCondition.FlagMines", "[H3M]")
  {
    constexpr VictoryCondition kVictoryCondition = {
      VictoryConditionDetails<VictoryConditionType::FlagMines>{
        SpecialVictoryConditionBase{.allow_normal_win = 1, .applies_to_computer = 0}
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x09\x01\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kVictoryCondition.type() == VictoryConditionType::FlagMines);
    REQUIRE(encodeVictoryCondition(kVictoryCondition) == kBinaryData);
    REQUIRE(decodeVictoryCondition(kBinaryData) == kVictoryCondition);
  }

  TEST_CASE("H3M.VictoryCondition.TransportArtifact", "[H3M]")
  {
    constexpr VictoryCondition kVictoryCondition = {
      VictoryConditionDetails<VictoryConditionType::TransportArtifact>{
        SpecialVictoryConditionBase{.allow_normal_win = 1, .applies_to_computer = 0},
        static_cast<std::uint8_t>(ArtifactType::ArmageddonsBlade),
        Coordinates{.x = 10, .y = 20, .z = 1}
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x0a\x01\x00\x80\x0a\x14\x01";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kVictoryCondition.type() == VictoryConditionType::TransportArtifact);
    REQUIRE(encodeVictoryCondition(kVictoryCondition) == kBinaryData);
    REQUIRE(decodeVictoryCondition(kBinaryData) == kVictoryCondition);
  }

  TEST_CASE("H3M.VictoryCondition.DefeatAllMonsters", "[H3M]")
  {
    constexpr VictoryCondition kVictoryCondition = {
      VictoryConditionDetails<VictoryConditionType::DefeatAllMonsters>{
        SpecialVictoryConditionBase{.allow_normal_win = 1, .applies_to_computer = 0}
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x0b\x01\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kVictoryCondition.type() == VictoryConditionType::DefeatAllMonsters);
    REQUIRE(encodeVictoryCondition(kVictoryCondition) == kBinaryData);
    REQUIRE(decodeVictoryCondition(kBinaryData) == kVictoryCondition);
  }

  TEST_CASE("H3M.VictoryCondition.SurviveBeyondATimeLimit", "[H3M]")
  {
    constexpr VictoryCondition kVictoryCondition = {
      VictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit>{
        SpecialVictoryConditionBase{.allow_normal_win = 1, .applies_to_computer = 0},
        99
      }
    };
    static constexpr char kBinaryDataCStr[] = "\x0c\x01\x00\x63\x00\x00\x00";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kVictoryCondition.type() == VictoryConditionType::SurviveBeyondATimeLimit);
    REQUIRE(encodeVictoryCondition(kVictoryCondition) == kBinaryData);
    REQUIRE(decodeVictoryCondition(kBinaryData) == kVictoryCondition);
  }

  TEST_CASE("H3M.VictoryCondition.Normal", "[H3M]")
  {
    constexpr VictoryCondition kVictoryCondition = {
      VictoryConditionDetails<VictoryConditionType::Normal>{}
    };
    static constexpr char kBinaryDataCStr[] = "\xff";
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    static_assert(kVictoryCondition.type() == VictoryConditionType::Normal);
    REQUIRE(encodeVictoryCondition(kVictoryCondition) == kBinaryData);
    REQUIRE(decodeVictoryCondition(kBinaryData) == kVictoryCondition);
  }
}
