#pragma once

#include <cstdint>

namespace h3m
{
  enum class PlayerColor : std::uint8_t
  {
    Red    = 0,
    Blue   = 1,
    Tan    = 2,
    Green  = 3,
    Orange = 4,
    Purple = 5,
    Teal   = 6,
    Pink   = 7,
    // Special value indicating no owner.
    None   = 0xFF
  };

  // The maximum number of players in the game.
  inline constexpr std::uint8_t kMaxPlayers = 8;
}
