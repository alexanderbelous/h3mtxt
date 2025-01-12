#pragma once

#include <cstdint>

namespace h3m
{

enum class RiverType : std::uint8_t
{
  None = 0,
  Clear = 1,
  Icy = 2,
  Muddy = 3,
  Lava = 4,
};

}
