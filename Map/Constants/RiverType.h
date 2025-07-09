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

  // Returns the number of valid sprites for the specified RiverType.
  //
  // \param river_type - type of the river.
  // \return the number N of valid sprites for @river_type, or 0 if @river_type is not a valid river type.
  //         The values [0; N) are safe to use in Tile::river_sprite for @river_type.
  constexpr std::uint8_t countSprites(RiverType river_type) noexcept
  {
    switch (river_type)
    {
    case RiverType::None:
      return 1;
    case RiverType::Clear:
    case RiverType::Icy:
    case RiverType::Muddy:
    case RiverType::Lava:
      return 13;
    default:
      return 0;
    }
  }
}
