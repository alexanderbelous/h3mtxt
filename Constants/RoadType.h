#pragma once

#include <cstdint>

namespace h3m
{

enum class RoadType : std::uint8_t
{
  None = 0,
  Dirt = 1,
  Gravel = 2,
  Cobblestone = 3,
};

}
