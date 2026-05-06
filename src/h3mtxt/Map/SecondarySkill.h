#pragma once

#include <h3mtxt/Map/Constants/SecondarySkillType.h>

#include <cstdint>

namespace h3m
{
  // Represents a secondary skill at a specific level.
  struct SecondarySkill
  {
    constexpr bool operator==(const SecondarySkill&) const noexcept = default;

    SecondarySkillType type {};
    // Normally, the level should be within [1; 3] (Basic, Advanced, Expert).
    // However, the game accidentally has stable behavior for some values outside of this range
    // for some skills - see SecondarySkillLevel.h.
    std::uint8_t level = 1;
  };
}
