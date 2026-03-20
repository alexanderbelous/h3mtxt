#pragma once

#include <cstdint>

namespace h3m
{

enum class ResourceType : std::uint8_t
{
  Wood = 0,
  Mercury = 1,
  Ore = 2,
  Sulfur = 3,
  Crystal = 4,
  Gems = 5,
  Gold = 6,
};

}
