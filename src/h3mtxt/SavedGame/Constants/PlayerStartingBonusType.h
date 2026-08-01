#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3svg
{
  // Enum type used in H3SVG to specify the type of the starting bonus for players.
  //
  // !!! Not to be confused be h3m::StartingBonusType, which specifies the !!!
  // !!! type of the starting bonus in campaign scenarios!                 !!!
  enum class PlayerStartingBonusType : std::uint8_t
  {
    Artifact = 0,
    Gold = 1,
    Resource = 2
  };
}
