#pragma once

#include <cstdint>

namespace h3m
{
  // Likelyhood of a monster joining a hero.
  enum class Disposition : std::uint8_t
  {
    Compliant = 0,
    Friendly = 1,
    Aggressive = 2,
    Hostile = 3,
    Savage = 4,
  };
}
