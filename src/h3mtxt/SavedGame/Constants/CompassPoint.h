#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3svg
{
  // Orientation/direction on the Adventure Map.
  //
  //          North
  //      +-----------+
  //      | 7 | 0 | 1 |
  //      +---+---+---+
  // West | 6 | * | 2 | East
  //      +---+---+---+
  //      | 5 | 4 | 3 |
  //      +---+---+---+
  //          South
  enum class CompassPoint : std::uint8_t
  {
    North     = 0,
    NorthEast = 1,
    East      = 2,
    SouthEast = 3,
    South     = 4,
    SouthWest = 5,
    West      = 6,
    NorthWest = 7
  };
}
