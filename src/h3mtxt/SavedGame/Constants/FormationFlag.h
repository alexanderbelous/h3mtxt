#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3svg
{
  // Formation flags for heroes on the Adventure Map.
  //
  // Used to index the bits in EnumBitmask<FormationFlag, 1> in h3svg::Hero.
  enum class FormationFlag : std::uint8_t
  {
    Tight   = 0,  // Controls the army combat formation
    Tactics = 1   // Controls Tactics formation
  };
}
