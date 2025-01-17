#pragma once

#include <cstdint>

namespace h3m
{
  enum class QuestType : std::uint8_t
  {
    None = 0,
    Level = 1,
    PrimarySkills = 2,
    DefeatHero = 3,
    DefeatMonster = 4,
    Artifacts = 5,
    Creatures = 6,
    Resources = 7,
    BeHero = 8,
    BePlayer = 9
  };

  inline constexpr std::uint8_t kNumQuestTypes = 10;
}
