#pragma once

#include <cstdint>

namespace h3m
{
  enum class ScholarRewardType : std::uint8_t
  {
    PrimarySkill = 0,
    SecondarySkill = 1,
    Spell = 2,
    Random = 0xFF,
  };
}
