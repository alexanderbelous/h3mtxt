#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3svg
{
  enum class KeymastersTentType : std::uint8_t
  {
    LightBlue = 0,
    Green = 1,
    Red = 2,
    DarkBlue = 3,
    Brown = 4,
    Purple = 5,
    White = 6,
    Black = 7
  };

  inline constexpr std::uint8_t kNumKeymastersTentTypes = 8;
}