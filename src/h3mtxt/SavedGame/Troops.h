#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/CreatureType.h>
#include <h3mtxt/Map/Utils/makeArrayOfDuplicates.h>

#include <array>
#include <cstdint>

namespace h3svg
{
  // TODO: consider reworking this class so that the creatures are stored similar to
  // std::array<CreatureStack, 7>.
  struct Troops
  {
    // Each element is CreatureType or 0xFFFFFFFF if the stack is empty.
    std::array<CreatureType32, kNumArmySlots> creature_types =
      h3m::Detail_NS::makeArrayOfDuplicates<kNumArmySlots>(static_cast<CreatureType32>(CreatureType::None));
    // The number of creatures in each slot.
    std::array<std::int32_t, kNumArmySlots> creature_counts {};
  };
}
