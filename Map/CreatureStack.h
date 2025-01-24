#pragma once

#include <h3mtxt/Map/Constants/CreatureType.h>

#include <cstdint>

namespace h3m
{
  struct CreatureStack
  {
    // 0xFFFF means "no creature".
    CreatureType type {0xFFFF};
    std::uint16_t count{};
  };
}
