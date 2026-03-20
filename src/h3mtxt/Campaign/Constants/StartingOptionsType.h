#pragma once

#include <cstdint>

namespace h3m
{
  enum class StartingOptionsType : std::uint8_t
  {
    // The Campaign Editor doesn't allow selecting None for existing scenarios,
    // but this is nevertheless the value used for absent scenarios.
    None = 0,
    StartingBonus = 1,
    HeroCrossover = 2,
    StartingHero = 3
  };
}
