#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3svg
{
  enum class CartographerType : std::uint8_t
  {
    Water        = 0,
    Land         = 1,
    Subterranean = 2
  };

  inline constexpr std::uint8_t kNumCartographerTypes = 3;
}
