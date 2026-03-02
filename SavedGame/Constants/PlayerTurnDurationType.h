#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3m
{
  // Enum type used in H3SVG to specify player turn duration.
  enum class PlayerTurnDurationType : std::uint8_t
  {
    OneMinute = 0,
    TwoMinutes = 1,
    FourMinutes = 2,
    SixMinutes = 3,
    EightMinutes = 4,
    TenMinutes = 5,
    FifteenMinutes = 6,
    TwentyMinutes = 7,
    TwentyFiveMinutes = 8,
    ThirtyMinutes = 9,
    Unlimited = 10
  };
}
