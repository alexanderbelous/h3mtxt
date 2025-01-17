#pragma once

#include <cstdint>

namespace h3m
{
  enum class RewardType : std::uint8_t
  {
    None = 0,
    Experience = 1,
    SpellPoints = 2,
    Morale = 3,
    Luck = 4,
    Resource = 5,
    PrimarySkill = 6,
    SecondarySkill = 7,
    Artifact = 8,
    Spell = 9,
    Creature = 10,
  };
}
