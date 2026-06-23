#pragma once

#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/CreatureType.h>
#include <h3mtxt/Map/Utils/TypedQuantity.h>

#include <array>
#include <cstdint>

namespace h3m
{
  // Represents an army - 7 stacks of creatures (some of which can be empty).
  //
  // The Map Editor only allows values from [1; 9999] for quantities in creature stacks
  // (or 0 for empty slots), but any signed 16-bit integer can be used here.
  // The behavior for nonpositive numbers depends on the context.
  //
  // All slots are empty in a default-constructed Army.
  struct Army
  {
    using CreatureStack = TypedQuantity<CreatureType, std::int16_t>;

    // The number of slots.
    static constexpr std::size_t kNumSlots = 7;

    // Represents an empty slot.
    static constexpr CreatureStack kEmptySlot{
      .type = CreatureType::None,
      .quantity = 0
    };

    // Equality comparison.
    constexpr bool operator==(const Army&) const noexcept = default;

    // Creature stack for each slot.
    std::array<CreatureStack, kNumSlots> slots = []() consteval
      {
        std::array<CreatureStack, kNumSlots> result {};
        result.fill(kEmptySlot);
        return result;
      }();
  };
}
