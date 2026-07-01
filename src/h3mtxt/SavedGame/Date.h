#pragma once

#include <cstdint>

namespace h3svg
{
  // Structured representation of a date as stored in H3SVG.
  struct Date
  {
    constexpr bool operator==(const Date&) const noexcept = default;

    // Day of the month (normally within [1; 7]).
    std::uint16_t day = 1;
    // Week of the month (normally within [1; 4]).
    std::uint16_t week = 1;
    // The current month (initialized with 1 at the start of the game; resets to 0 after Month 65535).
    std::uint16_t month = 1;
  };
}
