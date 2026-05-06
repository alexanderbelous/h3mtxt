#pragma once

#include <h3mtxt/Map/MapFwd.h>

#include <cstdint>

namespace h3m
{
  // Coordinates on the Adventure Map.
  struct Coordinates
  {
    constexpr bool operator==(const Coordinates&) const noexcept = default;

    std::uint8_t x {};
    std::uint8_t y {};
    std::uint8_t z {};
  };
}
