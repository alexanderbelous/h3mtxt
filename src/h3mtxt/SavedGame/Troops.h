#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/CreatureType.h>

#include <array>
#include <cstdint>

namespace h3svg
{
  // TODO: consider reworking this class so that the creatures are stored similar to
  // std::array<CreatureStack, 7>.
  struct Troops
  {
    // Each element is CreatureType or 0xFFFFFFFF if the stack is empty.
    std::array<CreatureType32, 7> creature_types =
      []() consteval
      {
        std::array<CreatureType32, 7> result{};
        result.fill(static_cast<CreatureType32>(CreatureType::None));
        return result;
      }();
    // The number of creatures in each slot.
    std::array<std::int32_t, 7> creature_counts {};
  };
}
