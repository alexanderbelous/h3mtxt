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

  // Returns the number of valid sprites for the specified RoadType.
  //
  // \param road_type - type of the road.
  // \return the number N of valid sprites for @road_type, or 0 if @road_type is not a valid road type.
  //         The values [0; N) are safe to use in Tile::road_sprite for @road_type.
  constexpr std::uint8_t countSprites(RoadType road_type) noexcept
  {
    switch (road_type)
    {
    case RoadType::None:
      return 1;
    case RoadType::Dirt:
    case RoadType::Gravel:
    case RoadType::Cobblestone:
      return 17;
    default:
      return 0;
    }
  }
}
