#pragma once

#include <cstdint>

namespace h3m
{

enum class MapDifficulty : std::uint8_t
{
  Easy = 0,
  Normal = 1,
  Hard = 2,
  Expert = 3,
  Impossible = 4,
};

}
