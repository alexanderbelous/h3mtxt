#pragma once

#include <h3mtxt/Map/Constants/SecondarySkillType.h>

#include <cstdint>

namespace h3m
{
  struct SecondarySkill
  {
    SecondarySkillType type {};
    // Normally, the level should be within [1; 3] (basic, advanced, expert).
    // However, the game has well-defined behavior for some values outside of this range
    // for some skills - see SecondarySkillLevel.h.
    std::uint8_t level {};
  };
}
