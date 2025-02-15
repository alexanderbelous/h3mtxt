#pragma once

#include <cstdint>

namespace h3m
{
  enum class StartingBonusType : std::uint8_t
  {
    Spell = 0,
    Creature = 1,
    Building = 2,
    Artifact = 3,
    SpellScroll = 4,
    PrimarySkills = 5,
    SecondarySkill = 6,
    Resource = 7,
  };
}
