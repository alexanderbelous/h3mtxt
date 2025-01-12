#pragma once

#include <array>
#include <cstdint>

namespace h3m
{

struct ObjectDetails
{
  // Coordinates of the bottom right corner.
  std::uint8_t x {};
  std::uint8_t y {};
  std::uint8_t z {};
  // 0-based index of the corresponding ObjectAttributes in Map.objects_attributes.
  std::uint32_t kind {};
  // Should be all 0s; kept here for compatibility.
  std::array<std::uint8_t, 5> unknown {};
  // TODO: add object-specific data.
};

}
