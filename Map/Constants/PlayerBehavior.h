#pragma once

#include <cstdint>

namespace h3m
{

enum class PlayerBehavior : std::uint8_t
{
  Random = 0,
  Warrior = 1,
  Builder = 2,
  Explorer = 3,
};

}
