#pragma once

#include <cstdint>

namespace h3m
{
  enum class CrossoverFeature : std::uint8_t
  {
    Experience = 0,
    PrimarySkills = 1,
    SecondarySkills = 2,
    Spells = 3,
    Artifacts = 4
  };
}
