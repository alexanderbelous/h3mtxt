#pragma once

#include <cstdint>

namespace h3m
{
  enum class ObjectGroup : std::uint8_t
  {
    Terrain = 0,
    Town = 1,
    Monster = 2,
    Hero = 3,
    Artifact = 4,
    Treasure = 5,
  };
}
