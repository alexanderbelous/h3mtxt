#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <array>
#include <cstdint>

namespace h3m
{
  // TODO: consider reworking this class so that the creatures are stored similar to
  // std::array<CreatureStack, 7>.
  struct TroopsSvg
  {
    // CreatureType or 0xFFFFFFFF if the stack is empty.
    std::array<CreatureType32, 7> creature_types{};
    std::array<std::int32_t, 7> creature_counts{};
  };
}
