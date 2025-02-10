#pragma once

#include <h3mtxt/Map/Constants/CreatureType.h>

#include <cstdint>

namespace h3m
{
  // Represents a stack of creatures.
  //
  // This appears in multiple places in .h3m, e.g., in a hero's army, a garrison,
  // a quest, etc.
  //
  // The default-constructed CreatureStack represents an empty stack.
  struct CreatureStack
  {
    // 0xFFFF means "no creature".
    CreatureType type {0xFFFF};
    std::uint16_t count{};
  };
}
