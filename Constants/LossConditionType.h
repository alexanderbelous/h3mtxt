#pragma once

#include <cstdint>

namespace h3m
{

enum class LossConditionType : std::uint8_t
{
  LoseTown = 0,
  LoseHero = 1,
  TimeExpires = 2,
  Normal = 0xFF,
};

}
