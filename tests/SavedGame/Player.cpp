#include "TestingUtils_H3SVG.h"

#include <h3mtxt/SavedGame/Player.h>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

using namespace std::string_view_literals;
using ::Testing_NS::asByteVector;
using ::Testing_NS::encodeAndDecodeJson;
using ::Testing_NS::encodeViaH3SVGWriter;
using ::Testing_NS::H3SVGReaderAdapter;

namespace h3svg
{
  // Test encoding/decoding Player for H3SVG.
  TEST_CASE("H3SVG.Player", "[H3SVG]")
  {
    static constexpr Player kPlayer = {
      .player_color = PlayerColor::Green,
      .num_heroes = 5,
      .active_hero = HeroType::Mephala,
      .heroes = {
        HeroType::Mephala,
        HeroType::Elleshar,
        HeroType::Gelu,
        HeroType::Kyrre,
        HeroType::Alamar,
        HeroType{0xFF},
        HeroType{0xFF},
        HeroType{0xFF}
      },
      .heroes_in_tavern = {
        HeroType::Malcom,
        HeroType::Geon
      },
      .unknown1 = 0,
      .personality = PlayerPersonality::Human,
      .unknown2 = 0,
      .grail_guess = { .x = -1, .y = -1, .z = -1 },
      .days_left = -1,
      .num_towns = 2,
      .current_town = -1,
      .towns = []() consteval {
        std::array<std::int8_t, 72> result {};
        result.fill(-1);
        result[0] = 3;
        result[1] = 5;
        return result;
      }(),
      .resources = { 15, 10, 15, 9, 8, 7, 4000 },
      .mystical_gardens = { 0xFF, 0x03, 0x00, 0x01 },
      .magic_springs = { 0x00, 0x80, 0x00, 0x33 },
      .corpses = { 0x70, 0x00, 0x00, 0x10 },
      .lean_tos = { 0x00, 0x00, 0x00, 0x00 },
      .show_tactics_message = false,
      .unknown3 = { 0, 0 }
    };
    // Binary representation of kPlayer.
    static constexpr std::string_view kBinaryData =
      "\x03" // player_color
      "\x05" // num_heroes
      "\x10" // active_hero
      "\x10" "\x1a" "\x94" "\x17" "\x58" "\xff" "\xff" "\xff" // heroes
      "\x1c" "\x5c" // heroes_in_tavern
      "\x00" // unknown1
      "\x03\x00\x00\x00" // personality
      "\x00" // unknown2
      "\xff\x03\xff\x3f" // grail_guess
      "\xff" // days_left
      "\x02" // num_towns
      "\xff" // current_town
      "\x03\x05\xff\xff" "\xff\xff\xff\xff" "\xff\xff\xff\xff" "\xff\xff\xff\xff" // towns
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff" "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\xff\xff\xff\xff" "\xff\xff\xff\xff"
      "\x0f\x00\x00\x00" "\x0a\x00\x00\x00" "\x0f\x00\x00\x00" "\x09\x00\x00\x00" // resources
      "\x08\x00\x00\x00" "\x07\x00\x00\x00" "\xa0\x0f\x00\x00"
      "\xff\x03\x00\x01" // mystical_gardens
      "\x00\x80\x00\x33" // magic_springs
      "\x70\x00\x00\x10" // corpses
      "\x00\x00\x00\x00" // lean_tos
      "\x00" // show_tactics_message
      "\x00\x00" // unknown3
      ""sv;

    REQUIRE(asByteVector(encodeViaH3SVGWriter(kPlayer)) == asByteVector(kBinaryData));
    REQUIRE(H3SVGReaderAdapter(kBinaryData).readPlayer() == kPlayer);
    REQUIRE(encodeAndDecodeJson(kPlayer) == kPlayer);
  }
}
