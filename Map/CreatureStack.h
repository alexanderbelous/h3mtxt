#pragma once

#include <h3mtxt/Map/Constants/CreatureType.h>

#include <cstdint>

namespace h3m
{
  // Represents a stack of creatures.
  //
  // This appears in multiple places in .h3m, e.g., in a hero's army, a garrison, a reward in Seer's Hut, etc.
  //
  // The default-constructed CreatureStack represents an empty stack.
  struct CreatureStack
  {
    // 0xFFFF means "no creature".
    CreatureType type {0xFFFF};
    // The Map Editor only allows values from [1; 9999], but any signed 16-bit integer can be used here.
    // The behavior for nonpositive numbers depends on the context.
    std::int16_t count {};
  };
}
