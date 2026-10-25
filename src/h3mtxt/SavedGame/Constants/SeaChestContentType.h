#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3svg
{
  enum class SeaChestContentType : std::uint32_t
  {
    Empty = 0,
    Gold1500 = 1,
    Gold1000Artifact = 2
  };
}
