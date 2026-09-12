#include "Utils.h"

#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/VictoryCondition.h>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <sstream>
#include <string>
#include <string_view>
#include <utility>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;

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

    // Encodes h3m::VictoryConditionDetails via H3MWriter.
    // \param details - input VictoryConditionDetails.
    // \return std::string storing the encoded data.
    template<VictoryConditionType T>
    std::string encodeVictoryConditionDetails(const VictoryConditionDetails<T>& details)
    {
      std::ostringstream stream;
      H3MWriter{ stream }.writeData(details);
      return std::move(stream).str();
    }

    // Decodes h3m::VictoryConditionDetails via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::VictoryConditionDetails decoded from @encoded_data.
    template<VictoryConditionType T>
    VictoryConditionDetails<T> decodeVictoryConditionDetails(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3MReader{ stream }.readVictoryConditionDetails<T>();
    }

    // Aggregates data for a test case for h3m::VictoryCondition.
    struct VictoryConditionTestCase
    {
      // Victory condition.
      VictoryCondition victory_condition;
      // Bytes representing @victory_condition in H3M.
      std::string_view binary_data;
    };

    // Variable template providing test data for each VictoryConditionType.
    template<VictoryConditionType T>
    constexpr VictoryConditionTestCase kVictoryConditionTestCase;

    template<>
    constexpr VictoryConditionTestCase kVictoryConditionTestCase<VictoryConditionType::AcquireArtifact> = {
      .victory_condition = {
        .details = VictoryConditionDetails<VictoryConditionType::AcquireArtifact>{
          SpecialVictoryConditionBase{ .allow_normal_win = 1, .applies_to_computer = 1 },
          ArtifactType::ArmageddonsBlade
        }
      },
      .binary_data = "\x00\x01\x01\x80\x00"sv
    };

    template<>
    constexpr VictoryConditionTestCase kVictoryConditionTestCase<VictoryConditionType::AccumulateCreatures> = {
      .victory_condition = {
        .details = VictoryConditionDetails<VictoryConditionType::AccumulateCreatures>{
          SpecialVictoryConditionBase{.allow_normal_win = 0, .applies_to_computer = 0},
          TypedQuantity<CreatureType, std::int32_t>{
            .type = CreatureType::AzureDragon,
            .quantity = 99
          }
        }
      },
      .binary_data = "\x01\x00\x00\x84\x00\x63\x00\x00\x00"sv
    };

    template<>
    constexpr VictoryConditionTestCase kVictoryConditionTestCase<VictoryConditionType::AccumulateResources> = {
      .victory_condition = {
        .details = VictoryConditionDetails<VictoryConditionType::AccumulateResources>{
          SpecialVictoryConditionBase{.allow_normal_win = 0, .applies_to_computer = 0},
          TypedQuantity<ResourceType, std::int32_t>{
            .type = ResourceType::Gems,
            .quantity = 100
          }
        }
      },
      .binary_data = "\x02\x00\x00\x05\x64\x00\x00\x00"sv
    };

    template<>
    constexpr VictoryConditionTestCase kVictoryConditionTestCase<VictoryConditionType::UpgradeTown> = {
      .victory_condition = {
        .details = VictoryConditionDetails<VictoryConditionType::UpgradeTown>{
          SpecialVictoryConditionBase{.allow_normal_win = 0, .applies_to_computer = 0},
          Coordinates{.x = 10, .y = 20, .z = 1},
          2, // Capitol
          0  // Fort
        }
      },
      .binary_data = "\x03\x00\x00\x0a\x14\x01\x02\x00"sv
    };

    template<>
    constexpr VictoryConditionTestCase kVictoryConditionTestCase<VictoryConditionType::BuildGrail> = {
      .victory_condition = {
        .details = VictoryConditionDetails<VictoryConditionType::BuildGrail>{
          SpecialVictoryConditionBase{.allow_normal_win = 0, .applies_to_computer = 0},
          Coordinates{.x = 10, .y = 20, .z = 1}
        }
      },
      .binary_data = "\x04\x00\x00\x0a\x14\x01"sv
    };

    template<>
    constexpr VictoryConditionTestCase kVictoryConditionTestCase<VictoryConditionType::DefeatHero> = {
      .victory_condition = {
        .details = VictoryConditionDetails<VictoryConditionType::DefeatHero>{
          SpecialVictoryConditionBase{.allow_normal_win = 0, .applies_to_computer = 0},
          Coordinates{.x = 10, .y = 20, .z = 1}
        }
      },
      .binary_data = "\x05\x00\x00\x0a\x14\x01"sv
    };

    template<>
    constexpr VictoryConditionTestCase kVictoryConditionTestCase<VictoryConditionType::CaptureTown> = {
      .victory_condition = {
        .details = VictoryConditionDetails<VictoryConditionType::CaptureTown>{
          SpecialVictoryConditionBase{.allow_normal_win = 0, .applies_to_computer = 0},
          Coordinates{.x = 10, .y = 20, .z = 1}
        }
      },
      .binary_data = "\x06\x00\x00\x0a\x14\x01"sv
    };

    template<>
    constexpr VictoryConditionTestCase kVictoryConditionTestCase<VictoryConditionType::DefeatMonster> = {
      .victory_condition = {
        .details = VictoryConditionDetails<VictoryConditionType::DefeatMonster>{
          SpecialVictoryConditionBase{.allow_normal_win = 0, .applies_to_computer = 0},
          Coordinates{.x = 10, .y = 20, .z = 1}
        }
      },
      .binary_data = "\x07\x00\x00\x0a\x14\x01"sv
    };

    template<>
    constexpr VictoryConditionTestCase kVictoryConditionTestCase<VictoryConditionType::FlagDwellings> = {
      .victory_condition = {
        .details = VictoryConditionDetails<VictoryConditionType::FlagDwellings>{
          SpecialVictoryConditionBase{.allow_normal_win = 1, .applies_to_computer = 0}
        }
      },
      .binary_data = "\x08\x01\x00"sv
    };

    template<>
    constexpr VictoryConditionTestCase kVictoryConditionTestCase<VictoryConditionType::FlagMines> = {
      .victory_condition = {
        .details = VictoryConditionDetails<VictoryConditionType::FlagMines>{
          SpecialVictoryConditionBase{.allow_normal_win = 1, .applies_to_computer = 0}
        }
      },
      .binary_data = "\x09\x01\x00"sv
    };

    template<>
    constexpr VictoryConditionTestCase kVictoryConditionTestCase<VictoryConditionType::TransportArtifact> = {
      .victory_condition = {
        .details = VictoryConditionDetails<VictoryConditionType::TransportArtifact>{
          SpecialVictoryConditionBase{.allow_normal_win = 1, .applies_to_computer = 0},
          static_cast<std::uint8_t>(ArtifactType::ArmageddonsBlade),
          Coordinates{.x = 10, .y = 20, .z = 1}
        }
      },
      .binary_data = "\x0a\x01\x00\x80\x0a\x14\x01"sv
    };

    template<>
    constexpr VictoryConditionTestCase kVictoryConditionTestCase<VictoryConditionType::DefeatAllMonsters> = {
      .victory_condition = {
        .details = VictoryConditionDetails<VictoryConditionType::DefeatAllMonsters>{
          SpecialVictoryConditionBase{.allow_normal_win = 1, .applies_to_computer = 0}
        }
      },
      .binary_data = "\x0b\x01\x00"sv
    };

    template<>
    constexpr VictoryConditionTestCase kVictoryConditionTestCase<VictoryConditionType::SurviveBeyondATimeLimit> = {
      .victory_condition = {
        .details = VictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit>{
          SpecialVictoryConditionBase{.allow_normal_win = 1, .applies_to_computer = 0},
          99
        }
      },
      .binary_data = "\x0c\x01\x00\x63\x00\x00\x00"sv
    };

    template<>
    constexpr VictoryConditionTestCase kVictoryConditionTestCase<VictoryConditionType::Normal> = {
      .victory_condition = {
        .details = VictoryConditionDetails<VictoryConditionType::Normal>{}
      },
      .binary_data = "\xff"sv
    };

    template<VictoryConditionType T>
    using StaticConstant = std::integral_constant<VictoryConditionType, T>;
  }

  TEMPLATE_TEST_CASE("H3M.VictoryCondition", "[H3M]",
                     StaticConstant<VictoryConditionType::AcquireArtifact>,
                     StaticConstant<VictoryConditionType::AccumulateCreatures>,
                     StaticConstant<VictoryConditionType::AccumulateResources>,
                     StaticConstant<VictoryConditionType::UpgradeTown>,
                     StaticConstant<VictoryConditionType::BuildGrail>,
                     StaticConstant<VictoryConditionType::DefeatHero>,
                     StaticConstant<VictoryConditionType::CaptureTown>,
                     StaticConstant<VictoryConditionType::DefeatMonster>,
                     StaticConstant<VictoryConditionType::FlagDwellings>,
                     StaticConstant<VictoryConditionType::FlagMines>,
                     StaticConstant<VictoryConditionType::TransportArtifact>,
                     StaticConstant<VictoryConditionType::DefeatAllMonsters>,
                     StaticConstant<VictoryConditionType::SurviveBeyondATimeLimit>,
                     StaticConstant<VictoryConditionType::Normal>)
  {
    static constexpr VictoryConditionType kVictoryConditionType = TestType::value;
    static constexpr const VictoryConditionTestCase& kTestData = kVictoryConditionTestCase<kVictoryConditionType>;
    static constexpr const VictoryCondition& kVictoryCondition = kTestData.victory_condition;
    static constexpr std::string_view kBinaryData = kTestData.binary_data;

    static_assert(kVictoryCondition.type() == kVictoryConditionType);

    // Test serialization of h3m::VictoryCondition.
    REQUIRE(asByteVector(encodeVictoryCondition(kVictoryCondition)) == asByteVector(kBinaryData));
    REQUIRE(decodeVictoryCondition(kBinaryData) == kVictoryCondition);
    REQUIRE(encodeAndDecodeJson(kVictoryCondition) == kVictoryCondition);

    // Test serialization of h3m::VictoryConditionDetails.
    static constexpr const auto& kVictoryConditionDetails =
      std::get<VictoryConditionDetails<kVictoryConditionType>>(kVictoryCondition.details);
    static constexpr std::string_view kBinaryDataDetails = kBinaryData.substr(1);
    REQUIRE(asByteVector(encodeVictoryConditionDetails(kVictoryConditionDetails)) == asByteVector(kBinaryDataDetails));
    REQUIRE(decodeVictoryConditionDetails<kVictoryConditionType>(kBinaryDataDetails) == kVictoryConditionDetails);
    REQUIRE(encodeAndDecodeJson(kVictoryConditionDetails) == kVictoryConditionDetails);
  }
}
