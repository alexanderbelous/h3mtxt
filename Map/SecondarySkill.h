#pragma once

#include <h3mtxt/Map/Constants/SecondarySkillType.h>

#include <cstdint>

namespace h3m
{
  struct SecondarySkill
  {
    SecondarySkillType type {};
    // Not really an enum, as shown by LC.
    std::uint8_t level {};
  };
}
