#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3svg
{
  enum class FloatsamContentType : std::uint32_t
  {
    None = 0,
    Wood5 = 1,
    Wood5Gold200 = 2,
    Wood10Gold500 = 3
  };
}
