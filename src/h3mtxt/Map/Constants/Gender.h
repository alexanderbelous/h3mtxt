#pragma once

#include <cstdint>

namespace h3m
{
  enum class Gender : std::uint8_t
  {
    Male = 0,
    Female = 1,
    Default = 0xFF,
  };
}