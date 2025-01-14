#pragma once

#include <h3mparser/Map/Constants/CreatureType.h>

#include <cstdint>

namespace h3m
{
  struct CreatureStack
  {
    // 0xFFFF means "no creature".
    CreatureType type{};
    std::uint16_t count{};
  };
}
