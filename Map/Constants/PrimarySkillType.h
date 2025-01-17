#pragma once

#include <cstdint>

namespace h3m
{
  enum class PrimarySkillType : std::uint8_t
  {
    Attack = 0,
    Defense = 1,
    SpellPower = 2,
    Knowledge = 3,
  };
}
