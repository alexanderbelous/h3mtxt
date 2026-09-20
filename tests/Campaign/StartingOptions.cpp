#include "TestUtils_H3C.h"

#include <h3mtxt/Campaign/StartingOptions.h>
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
  TEST_CASE("H3M.StartingOptionsDetails.None", "[H3C]")
  {
    // StartingOptionsDetails used in this test.
    static constexpr StartingOptionsDetails<StartingOptionsType::None> kStartingOptionsDetails{};
    // The binary representation of kStartingOptionsDetails.
    static constexpr std::string_view kBinaryData;

    REQUIRE(asByteVector(encodeViaH3CWriter(kStartingOptionsDetails)) == asByteVector(kBinaryData));
    REQUIRE(H3CReaderAdapter(kBinaryData).readStartingOptionsDetails<StartingOptionsType::None>() ==
            kStartingOptionsDetails);
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
              .quantity = 1
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
    static constexpr std::string_view kBinaryData =
      "\x03"
      "\x02"
      "\x01" "\x55\x00" "\x53\x00" "\x01\x00"
      "\x04" "\x55\x00" "\x17"
      ""sv;

    REQUIRE(asByteVector(encodeViaH3CWriter(kStartingOptionsDetails)) == asByteVector(kBinaryData));
    REQUIRE(H3CReaderAdapter(kBinaryData).readStartingOptionsDetails<StartingOptionsType::StartingBonus>() ==
            kStartingOptionsDetails);
    REQUIRE(encodeAndDecodeJson(kStartingOptionsDetails) == kStartingOptionsDetails);
  }

  TEST_CASE("H3M.StartingOptionsDetails.HeroCrossover", "[H3C]")
  {
    // StartingOptionsDetails used in this test.
    const StartingOptionsDetails<StartingOptionsType::HeroCrossover> kStartingOptionsDetails{
      .options = {
        HeroCrossoverOption{
          .player = PlayerColor::Green,
          .source_scenario = 1
        },
        HeroCrossoverOption{
          .player = PlayerColor::Teal,
          .source_scenario = 1
        }
      }
    };

    // The binary representation of kStartingOptionsDetails.
    static constexpr std::string_view kBinaryData =
      "\x02"
      "\x03" "\x01"
      "\x06" "\x01"
      ""sv;

    REQUIRE(asByteVector(encodeViaH3CWriter(kStartingOptionsDetails)) == asByteVector(kBinaryData));
    REQUIRE(H3CReaderAdapter(kBinaryData).readStartingOptionsDetails<StartingOptionsType::HeroCrossover>() ==
            kStartingOptionsDetails);
    REQUIRE(encodeAndDecodeJson(kStartingOptionsDetails) == kStartingOptionsDetails);
  }

  TEST_CASE("H3M.StartingOptionsDetails.StartingHero", "[H3C]")
  {
    // StartingOptionsDetails used in this test.
    const StartingOptionsDetails<StartingOptionsType::StartingHero> kStartingOptionsDetails{
      .options = {
        StartingHeroOption{
          .player = PlayerColor::Red,
          .type = static_cast<std::uint16_t>(HeroType::SirMullich)
        },
        StartingHeroOption{
          .player = PlayerColor::Blue,
          .type = static_cast<std::uint16_t>(HeroType::Mephala)
        },
        StartingHeroOption{
          .player = PlayerColor::Tan,
          .type = static_cast<std::uint16_t>(HeroType::Gunnar)
        }
      }
    };

    // The binary representation of kStartingOptionsDetails.
    static constexpr std::string_view kBinaryData =
      "\x03"
      "\x00" "\x90\x00"
      "\x01" "\x10\x00"
      "\x02" "\x55\x00"
      ""sv;

    REQUIRE(asByteVector(encodeViaH3CWriter(kStartingOptionsDetails)) == asByteVector(kBinaryData));
    REQUIRE(H3CReaderAdapter(kBinaryData).readStartingOptionsDetails<StartingOptionsType::StartingHero>() ==
            kStartingOptionsDetails);
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
                .quantity = 1
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
    static constexpr std::string_view kBinaryData =
      "\x01"
      "\x03"
      "\x02"
      "\x01" "\x55\x00" "\x53\x00" "\x01\x00"
      "\x04" "\x55\x00" "\x17"
      ""sv;

    REQUIRE(kStartingOptions.type() == StartingOptionsType::StartingBonus);
    REQUIRE(asByteVector(encodeViaH3CWriter(kStartingOptions)) == asByteVector(kBinaryData));
    REQUIRE(H3CReaderAdapter(kBinaryData).readStartingOptions() == kStartingOptions);
    REQUIRE(encodeAndDecodeJson(kStartingOptions) == kStartingOptions);
  }
}
