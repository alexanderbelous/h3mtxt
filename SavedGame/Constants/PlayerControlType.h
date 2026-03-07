#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

namespace h3svg
{
  enum class PlayerControlType : std::int8_t
  {
    Cpu = 0,        // Only the computer can control this color.
    HumanOrCpu = 1, // This color can be played by the human or the computer.
    None = -1       // No one can control this color (because it's missing from the map).
  };
}
