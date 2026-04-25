#include "../Utils.h"

#include <h3mtxt/H3JsonReader/H3CJsonReader/H3CJsonReader.h>
#include <h3mtxt/H3JsonWriter/H3CJsonWriter/H3CJsonWriter.h>
#include <h3mtxt/H3Reader/H3CReader/H3CReader.h>
#include <h3mtxt/H3Writer/H3CWriter/H3CWriter.h>
#include <h3mtxt/Campaign/StartingOptions.h>
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
    // Encodes h3m::StartingOptionsDetails via H3CWriter.
    // \param starting_options_details - input StartingOptionsDetails.
    // \return std::string storing the encoded data.
    template<StartingOptionsType T>
    std::string encodeStartingOptionsDetails(const StartingOptionsDetails<T>& starting_options_details)
    {
      std::ostringstream stream;
      H3CWriter{ stream }.writeData(starting_options_details);
      return std::move(stream).str();
    }

    // Decodes h3m::StartingOptionsDetails via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::StartingOptionsDetails decoded from @encoded_data.
    template<StartingOptionsType T>
    StartingOptionsDetails<T> decodeStartingOptionsDetails(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3CReader{ stream }.readStartingOptionsDetails<T>();
    }

    // Encodes h3m::StartingOptions via H3CWriter.
    // \param starting_options - input StartingOptions.
    // \return std::string storing the encoded data.
    std::string encodeStartingOptions(const StartingOptions& starting_options)
    {
      std::ostringstream stream;
      H3CWriter{ stream }.writeData(starting_options);
      return std::move(stream).str();
    }

    // Decodes h3m::StartingOptions via H3MReader.
    // \param encoded_data - input binary data.
    // \return h3m::StartingOptions decoded from @encoded_data.
    StartingOptions decodeStartingOptions(std::string_view encoded_data)
    {
      std::istringstream stream{ std::string{encoded_data} };
      return H3CReader{ stream }.readStartingOptions();
    }
  }

  TEST_CASE("H3M.StartingOptionsDetails.None", "[H3C]")
  {
    // StartingOptionsDetails used in this test.
    static constexpr StartingOptionsDetails<StartingOptionsType::None> kStartingOptionsDetails{};
    // The binary representation of kStartingOptionsDetails.
    static constexpr std::string_view kBinaryData;

    REQUIRE(asByteVector(encodeStartingOptionsDetails(kStartingOptionsDetails)) == asByteVector(kBinaryData));
    REQUIRE(decodeStartingOptionsDetails<StartingOptionsType::None>(kBinaryData) == kStartingOptionsDetails);
    REQUIRE(encodeAndDecodeJson(kStartingOptionsDetails) == kStartingOptionsDetails);
  }

  TEST_CASE("H3M.StartingOptionsDetails.StartingBonus", "[H3C]")
  {
    // StartingOptionsDetails used in this test.
    const StartingOptionsDetails<StartingOptionsType::StartingBonus> kStartingOptionsDetails{
      .player = PlayerColor::Green,
      .options = {
        StartingBonus{
          .details = StartingBonusDetails<StartingBonusType::Creature>{
            .hero = static_cast<std::uint16_t>(HeroType::Gunnar),
            .creature_stack = {
              .type = CreatureType::BlackDragon,
              .count = 1
            }
          }
        },
        StartingBonus{
          .details = StartingBonusDetails<StartingBonusType::SpellScroll>{
            .hero = static_cast<std::uint16_t>(HeroType::Gunnar),
            .spell = SpellType::MeteorShower
          }
        }
      }
    };

    // The binary representation of kStartingOptionsDetails.
    static constexpr char kBinaryDataCStr[] =
      "\x03"
      "\x02"
      "\x01" "\x55\x00" "\x53\x00" "\x01\x00"
      "\x04" "\x55\x00" "\x17";

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeStartingOptionsDetails(kStartingOptionsDetails)) == asByteVector(kBinaryData));
    REQUIRE(decodeStartingOptionsDetails<StartingOptionsType::StartingBonus>(kBinaryData) == kStartingOptionsDetails);
    REQUIRE(encodeAndDecodeJson(kStartingOptionsDetails) == kStartingOptionsDetails);
  }

  TEST_CASE("H3M.StartingOptionsDetails.HeroCrossover", "[H3C]")
  {
    using Hero = StartingOptionsDetails<StartingOptionsType::HeroCrossover>::Hero;

    // StartingOptionsDetails used in this test.
    const StartingOptionsDetails<StartingOptionsType::HeroCrossover> kStartingOptionsDetails{
      .options = {
        Hero{
          .player = PlayerColor::Green,
          .source_scenario = 1
        },
        Hero{
          .player = PlayerColor::Teal,
          .source_scenario = 1
        }
      }
    };

    // The binary representation of kStartingOptionsDetails.
    static constexpr char kBinaryDataCStr[] =
      "\x02"
      "\x03" "\x01"
      "\x06" "\x01";

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeStartingOptionsDetails(kStartingOptionsDetails)) == asByteVector(kBinaryData));
    REQUIRE(decodeStartingOptionsDetails<StartingOptionsType::HeroCrossover>(kBinaryData) == kStartingOptionsDetails);
    REQUIRE(encodeAndDecodeJson(kStartingOptionsDetails) == kStartingOptionsDetails);
  }

  TEST_CASE("H3M.StartingOptionsDetails.StartingHero", "[H3C]")
  {
    using Hero = StartingOptionsDetails<StartingOptionsType::StartingHero>::Hero;

    // StartingOptionsDetails used in this test.
    const StartingOptionsDetails<StartingOptionsType::StartingHero> kStartingOptionsDetails{
      .options = {
        Hero{
          .player = PlayerColor::Red,
          .type = static_cast<std::uint16_t>(HeroType::SirMullich)
        },
        Hero{
          .player = PlayerColor::Blue,
          .type = static_cast<std::uint16_t>(HeroType::Mephala)
        },
        Hero{
          .player = PlayerColor::Tan,
          .type = static_cast<std::uint16_t>(HeroType::Gunnar)
        }
      }
    };

    // The binary representation of kStartingOptionsDetails.
    static constexpr char kBinaryDataCStr[] =
      "\x03"
      "\x00" "\x90\x00"
      "\x01" "\x10\x00"
      "\x02" "\x55\x00";

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(asByteVector(encodeStartingOptionsDetails(kStartingOptionsDetails)) == asByteVector(kBinaryData));
    REQUIRE(decodeStartingOptionsDetails<StartingOptionsType::StartingHero>(kBinaryData) == kStartingOptionsDetails);
    REQUIRE(encodeAndDecodeJson(kStartingOptionsDetails) == kStartingOptionsDetails);
  }

  TEST_CASE("H3M.StartingOptions", "[H3C]")
  {
    // StartingOptions used in this test.
    const StartingOptions kStartingOptions{
      .details = StartingOptionsDetails<StartingOptionsType::StartingBonus>{
        .player = PlayerColor::Green,
        .options = {
          StartingBonus{
            .details = StartingBonusDetails<StartingBonusType::Creature>{
              .hero = static_cast<std::uint16_t>(HeroType::Gunnar),
              .creature_stack = {
                .type = CreatureType::BlackDragon,
                .count = 1
              }
            }
          },
          StartingBonus{
            .details = StartingBonusDetails<StartingBonusType::SpellScroll>{
              .hero = static_cast<std::uint16_t>(HeroType::Gunnar),
              .spell = SpellType::MeteorShower
            }
          }
        }
      }
    };

    // The binary representation of kStartingOptionsDetails.
    static constexpr char kBinaryDataCStr[] =
      "\x01"
      "\x03"
      "\x02"
      "\x01" "\x55\x00" "\x53\x00" "\x01\x00"
      "\x04" "\x55\x00" "\x17";

    // std::string_view into kBinaryData.
    static constexpr std::string_view kBinaryData{ kBinaryDataCStr, std::size(kBinaryDataCStr) - 1 };

    REQUIRE(kStartingOptions.type() == StartingOptionsType::StartingBonus);
    REQUIRE(asByteVector(encodeStartingOptions(kStartingOptions)) == asByteVector(kBinaryData));
    REQUIRE(decodeStartingOptions(kBinaryData) == kStartingOptions);
    REQUIRE(encodeAndDecodeJson(kStartingOptions) == kStartingOptions);
  }
}
