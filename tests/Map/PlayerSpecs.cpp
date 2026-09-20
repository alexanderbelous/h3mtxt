#include "TestUtils_H3M.h"

#include <h3mtxt/Map/PlayerSpecs.h>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3MWriter;
using ::Testing_NS::H3MReaderAdapter;

namespace h3m
{
  TEST_CASE("H3M.MainTown", "[H3M]")
  {
    constexpr MainTown kMainTown = {
      .generate_hero = 1,
      .town_type = TownType::Dungeon,
      .coordinates{.x = 70, .y = 24, .z = 1}
    };
    static constexpr std::string_view kBinaryData = "\x01\x05\x46\x18\x01"sv;

    REQUIRE(asByteVector(encodeViaH3MWriter(kMainTown)) == asByteVector(kBinaryData));
    REQUIRE(H3MReaderAdapter(kBinaryData).readMainTown() == kMainTown);
    REQUIRE(encodeAndDecodeJson(kMainTown) == kMainTown);
  }

  TEST_CASE("H3M.StartingHero", "[H3M]")
  {
    SECTION("None")
    {
      const StartingHero kStartingHero = { .type = static_cast<HeroType>(-1) };
      constexpr std::string_view kBinaryData = "\xff"sv;
      REQUIRE(asByteVector(encodeViaH3MWriter(kStartingHero)) == asByteVector(kBinaryData));
      REQUIRE(H3MReaderAdapter(kBinaryData).readStartingHero() == kStartingHero);
      REQUIRE(encodeAndDecodeJson(kStartingHero) == kStartingHero);
    }
    SECTION("Not None")
    {
      const StartingHero kStartingHero = {
        .type = HeroType::Mutare,
        .portrait = HeroPortrait::Mephala,
        .name = "Jessica"
      };
      static constexpr std::string_view kBinaryData = "\x97\x10\x07\x00\x00\x00Jessica"sv;
      REQUIRE(asByteVector(encodeViaH3MWriter(kStartingHero)) == asByteVector(kBinaryData));
      REQUIRE(H3MReaderAdapter(kBinaryData).readStartingHero() == kStartingHero);
      REQUIRE(encodeAndDecodeJson(kStartingHero) == kStartingHero);
    }
  }

  TEST_CASE("H3M.PlayerSpecs", "[H3M]")
  {
    const PlayerSpecs kPlayerSpecs = {
      .can_be_human = 1,
      .can_be_computer = 1,
      .behavior = PlayerBehavior::Random,
      .has_customized_alignments = 1,
      .allowed_alignments = []() consteval {
        TownsBitmask bitmask;
        bitmask.set(TownType::Rampart, true);
        bitmask.set(TownType::Dungeon, true);
        return bitmask;
      }(),
      .allow_random_alignment = 0,
      .main_town = MainTown{
        .generate_hero = 1,
        .town_type = TownType::Random,
        .coordinates {.x = 44, .y = 12, .z = 1}
      },
      .has_random_heroes = 0,
      .starting_hero {
        .type = HeroType::Mutare,
        .portrait = HeroPortrait::Mephala,
        .name = "Jessica"
      },
      .num_nonspecific_placeholder_heroes = 0,
      .heroes = {
        PlayerSpecs::HeroInfo{.type = HeroType::Mutare, .name = "Jessica"},
        PlayerSpecs::HeroInfo{.type = HeroType::Orrin, .name = ""},
      }
    };
    static constexpr std::string_view kBinaryData =
      "\x01"                                                                   // can_be_human
      "\x01"                                                                   // can_be_computer
      "\x00"                                                                   // behavior
      "\x01"                                                                   // has_customized_alignments
      "\x22\x00"                                                               // allowed_alignments
      "\x00"                                                                   // allow_random_alignment
      "\x01"                                                                   // has_main_town
      "\x01" "\xff" "\x2c\x0c\x01"                                             // ?main_town
      "\x00"                                                                   // has_random_heroes
      "\x97\x10\x07\x00\x00\x00Jessica"                                        // starting_hero
      "\x00"                                                                   // num_nonspecific_placeholder_heroes
      "\x02\x00\x00\x00" "\x97\x07\x00\x00\x00Jessica" "\x00\x00\x00\x00\x00"  // heroes
      ""sv;

    REQUIRE(asByteVector(encodeViaH3MWriter(kPlayerSpecs)) == asByteVector(kBinaryData));
    REQUIRE(H3MReaderAdapter(kBinaryData).readPlayerSpecs() == kPlayerSpecs);
    REQUIRE(encodeAndDecodeJson(kPlayerSpecs) == kPlayerSpecs);
  }
}
