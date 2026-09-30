#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

namespace h3svg
{
  enum class PlayerType : std::int8_t
  {
    Human = 0,
    Computer = 10,
    None = -1
  };
}
