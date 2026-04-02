#pragma once

#include <h3mtxt/Map/MapFwd.h>

#include <compare>
#include <cstdint>

namespace h3m
{
  struct Coordinates
  {
    constexpr std::strong_ordering operator<=>(const Coordinates& other) const noexcept = default;

    std::uint8_t x {};
    std::uint8_t y {};
    std::uint8_t z {};
  };
}
