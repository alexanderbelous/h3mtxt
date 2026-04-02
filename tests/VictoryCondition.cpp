#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/VictoryCondition.h>

#include <catch2/catch_test_macros.hpp>

#include <iterator>
#include <sstream>
#include <string>
#include <string_view>

namespace h3m
{
  TEST_CASE("H3M.VictoryCondition", "[H3M]")
  {
    SECTION("AcquireArtifact")
    {
      constexpr VictoryCondition kVictoryCondition = {
        VictoryConditionDetails<VictoryConditionType::AcquireArtifact>{
          SpecialVictoryConditionBase{.allow_normal_win = 1, .applies_to_computer = 1},
          ArtifactType::ArmageddonsBlade
        }
      };
      static constexpr char kBinaryDataCStr[] = "\x00\x01\x01\x80\x00";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

      SECTION("Encode")
      {
        std::ostringstream stream;
        H3MWriter{ stream }.writeData(kVictoryCondition);
        REQUIRE(stream.view() == kBinaryData);
      }
      SECTION("Decode")
      {
        std::istringstream stream{ std::string{kBinaryData} };
        REQUIRE(H3MReader{ stream }.readVictoryCondition() == kVictoryCondition);
      }
    }

    SECTION("AccumulateCreatures")
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

      SECTION("Encode")
      {
        std::ostringstream stream;
        H3MWriter{ stream }.writeData(kVictoryCondition);
        REQUIRE(stream.view() == kBinaryData);
      }
      SECTION("Decode")
      {
        std::istringstream stream{ std::string{kBinaryData} };
        REQUIRE(H3MReader{ stream }.readVictoryCondition() == kVictoryCondition);
      }
    }

    SECTION("AccumulateResources")
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

      SECTION("Encode")
      {
        std::ostringstream stream;
        H3MWriter{ stream }.writeData(kVictoryCondition);
        REQUIRE(stream.view() == kBinaryData);
      }
      SECTION("Decode")
      {
        std::istringstream stream{ std::string{kBinaryData} };
        REQUIRE(H3MReader{ stream }.readVictoryCondition() == kVictoryCondition);
      }
    }

    SECTION("UpgradeTown")
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

      SECTION("Encode")
      {
        std::ostringstream stream;
        H3MWriter{ stream }.writeData(kVictoryCondition);
        REQUIRE(stream.view() == kBinaryData);
      }
      SECTION("Decode")
      {
        std::istringstream stream{ std::string{kBinaryData} };
        REQUIRE(H3MReader{ stream }.readVictoryCondition() == kVictoryCondition);
      }
    }

    SECTION("BuildGrail")
    {
      constexpr VictoryCondition kVictoryCondition = {
        VictoryConditionDetails<VictoryConditionType::BuildGrail>{
          SpecialVictoryConditionBase{.allow_normal_win = 0, .applies_to_computer = 0},
          Coordinates{.x = 10, .y = 20, .z = 1}
        }
      };
      static constexpr char kBinaryDataCStr[] = "\x04\x00\x00\x0a\x14\x01";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

      SECTION("Encode")
      {
        std::ostringstream stream;
        H3MWriter{ stream }.writeData(kVictoryCondition);
        REQUIRE(stream.view() == kBinaryData);
      }
      SECTION("Decode")
      {
        std::istringstream stream{ std::string{kBinaryData} };
        REQUIRE(H3MReader{ stream }.readVictoryCondition() == kVictoryCondition);
      }
    }

    SECTION("DefeatHero")
    {
      constexpr VictoryCondition kVictoryCondition = {
        VictoryConditionDetails<VictoryConditionType::DefeatHero>{
          SpecialVictoryConditionBase{.allow_normal_win = 0, .applies_to_computer = 0},
          Coordinates{.x = 10, .y = 20, .z = 1}
        }
      };
      static constexpr char kBinaryDataCStr[] = "\x05\x00\x00\x0a\x14\x01";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

      SECTION("Encode")
      {
        std::ostringstream stream;
        H3MWriter{ stream }.writeData(kVictoryCondition);
        REQUIRE(stream.view() == kBinaryData);
      }
      SECTION("Decode")
      {
        std::istringstream stream{ std::string{kBinaryData} };
        REQUIRE(H3MReader{ stream }.readVictoryCondition() == kVictoryCondition);
      }
    }

    SECTION("CaptureTown")
    {
      constexpr VictoryCondition kVictoryCondition = {
        VictoryConditionDetails<VictoryConditionType::CaptureTown>{
          SpecialVictoryConditionBase{.allow_normal_win = 0, .applies_to_computer = 0},
          Coordinates{.x = 10, .y = 20, .z = 1}
        }
      };
      static constexpr char kBinaryDataCStr[] = "\x06\x00\x00\x0a\x14\x01";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

      SECTION("Encode")
      {
        std::ostringstream stream;
        H3MWriter{ stream }.writeData(kVictoryCondition);
        REQUIRE(stream.view() == kBinaryData);
      }
      SECTION("Decode")
      {
        std::istringstream stream{ std::string{kBinaryData} };
        REQUIRE(H3MReader{ stream }.readVictoryCondition() == kVictoryCondition);
      }
    }

    SECTION("DefeatMonster")
    {
      constexpr VictoryCondition kVictoryCondition = {
        VictoryConditionDetails<VictoryConditionType::DefeatMonster>{
          SpecialVictoryConditionBase{.allow_normal_win = 0, .applies_to_computer = 0},
          Coordinates{.x = 10, .y = 20, .z = 1}
        }
      };
      static constexpr char kBinaryDataCStr[] = "\x07\x00\x00\x0a\x14\x01";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

      SECTION("Encode")
      {
        std::ostringstream stream;
        H3MWriter{ stream }.writeData(kVictoryCondition);
        REQUIRE(stream.view() == kBinaryData);
      }
      SECTION("Decode")
      {
        std::istringstream stream{ std::string{kBinaryData} };
        REQUIRE(H3MReader{ stream }.readVictoryCondition() == kVictoryCondition);
      }
    }

    SECTION("FlagDwellings")
    {
      constexpr VictoryCondition kVictoryCondition = {
        VictoryConditionDetails<VictoryConditionType::FlagDwellings>{
          SpecialVictoryConditionBase{.allow_normal_win = 1, .applies_to_computer = 0}
        }
      };
      static constexpr char kBinaryDataCStr[] = "\x08\x01\x00";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

      SECTION("Encode")
      {
        std::ostringstream stream;
        H3MWriter{ stream }.writeData(kVictoryCondition);
        REQUIRE(stream.view() == kBinaryData);
      }
      SECTION("Decode")
      {
        std::istringstream stream{ std::string{kBinaryData} };
        REQUIRE(H3MReader{ stream }.readVictoryCondition() == kVictoryCondition);
      }
    }

    SECTION("FlagMines")
    {
      constexpr VictoryCondition kVictoryCondition = {
        VictoryConditionDetails<VictoryConditionType::FlagMines>{
          SpecialVictoryConditionBase{.allow_normal_win = 1, .applies_to_computer = 0}
        }
      };
      static constexpr char kBinaryDataCStr[] = "\x09\x01\x00";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

      SECTION("Encode")
      {
        std::ostringstream stream;
        H3MWriter{ stream }.writeData(kVictoryCondition);
        REQUIRE(stream.view() == kBinaryData);
      }
      SECTION("Decode")
      {
        std::istringstream stream{ std::string{kBinaryData} };
        REQUIRE(H3MReader{ stream }.readVictoryCondition() == kVictoryCondition);
      }
    }

    SECTION("TransportArtifact")
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

      SECTION("Encode")
      {
        std::ostringstream stream;
        H3MWriter{ stream }.writeData(kVictoryCondition);
        REQUIRE(stream.view() == kBinaryData);
      }
      SECTION("Decode")
      {
        std::istringstream stream{ std::string{kBinaryData} };
        REQUIRE(H3MReader{ stream }.readVictoryCondition() == kVictoryCondition);
      }
    }

    SECTION("DefeatAllMonsters")
    {
      constexpr VictoryCondition kVictoryCondition = {
        VictoryConditionDetails<VictoryConditionType::DefeatAllMonsters>{
          SpecialVictoryConditionBase{.allow_normal_win = 1, .applies_to_computer = 0}
        }
      };
      static constexpr char kBinaryDataCStr[] = "\x0b\x01\x00";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

      SECTION("Encode")
      {
        std::ostringstream stream;
        H3MWriter{ stream }.writeData(kVictoryCondition);
        REQUIRE(stream.view() == kBinaryData);
      }
      SECTION("Decode")
      {
        std::istringstream stream{ std::string{kBinaryData} };
        REQUIRE(H3MReader{ stream }.readVictoryCondition() == kVictoryCondition);
      }
    }

    SECTION("SurviveBeyondATimeLimit")
    {
      constexpr VictoryCondition kVictoryCondition = {
        VictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit>{
          SpecialVictoryConditionBase{.allow_normal_win = 1, .applies_to_computer = 0},
          99
        }
      };
      static constexpr char kBinaryDataCStr[] = "\x0c\x01\x00\x63\x00\x00\x00";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

      SECTION("Encode")
      {
        std::ostringstream stream;
        H3MWriter{ stream }.writeData(kVictoryCondition);
        REQUIRE(stream.view() == kBinaryData);
      }
      SECTION("Decode")
      {
        std::istringstream stream{ std::string{kBinaryData} };
        REQUIRE(H3MReader{ stream }.readVictoryCondition() == kVictoryCondition);
      }
    }

    SECTION("Normal")
    {
      constexpr VictoryCondition kVictoryCondition = {
        VictoryConditionDetails<VictoryConditionType::Normal>{}
      };
      static constexpr char kBinaryDataCStr[] = "\xff";
      static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

      SECTION("Encode")
      {
        std::ostringstream stream;
        H3MWriter{ stream }.writeData(kVictoryCondition);
        REQUIRE(stream.view() == kBinaryData);
      }
      SECTION("Decode")
      {
        std::istringstream stream{ std::string{kBinaryData} };
        REQUIRE(H3MReader{ stream }.readVictoryCondition() == kVictoryCondition);
      }
    }
  }
}
