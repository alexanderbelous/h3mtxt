#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3m
{
  struct Coordinates
  {
    std::uint8_t x {};
    std::uint8_t y {};
    std::uint8_t z {};
  };
}
