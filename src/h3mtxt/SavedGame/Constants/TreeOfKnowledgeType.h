#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3svg
{
  enum class TreeOfKnowledgeType : std::uint8_t
  {
    Free = 0, // Free
    Gold = 1, // 2000 Gold
    Gems = 2  // 10 Gems
  };
}
