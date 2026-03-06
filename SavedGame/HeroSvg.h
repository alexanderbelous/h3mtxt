#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/MapFwd.h>

#include <array>
#include <cstdint>
#include <string>

namespace h3m
{
  struct HeroSvg
  {
    std::int16_t x {};
    std::int16_t y {};
    std::int16_t z {};
    Bool is_visible {};
    std::uint32_t coordinates_packed {};
    std::array<std::uint8_t, 11> unknown1 {};
    // Size is 32-bit.
    std::string biography;
    std::array<std::uint8_t, 169> unknown2 {};
    // Fixed-size; only the characters before the first null terminator are significant.
    std::array<char, 13> name {};
    std::array<std::uint8_t, 886> unknown3 {};
  };
}