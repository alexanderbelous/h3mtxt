#pragma once

#include <h3mtxt/Map/Constants/PlayerColor.h>

#include <cstdint>
#include <stdexcept>

namespace h3m
{
  // Indicates which players are affected by an event
  // (GlobalEvent, Event object on the adventure map, or a Event in a town).
  struct AffectedPlayers
  {
  private:
    // Constructs a bitmask for the given player.
    // \param player - player for which to construct a bitmask.
    // \return an 8-bit unsigned integer with all bits except int(player) set to 0,
    //         or 0 if @player is not a valid PlayerColor.
    static constexpr std::uint8_t getBitmask(PlayerColor player) noexcept;

  public:
    constexpr bool isAffected(PlayerColor player) const;

    constexpr void setAffected(PlayerColor player, bool is_affected);

    std::uint8_t bitset {};
  };

  constexpr std::uint8_t AffectedPlayers::getBitmask(PlayerColor player) noexcept
  {
    const auto bit_index = static_cast<std::underlying_type_t<PlayerColor>>(player);
    if (bit_index >= 8)
    {
      return 0;
    }
    return std::uint8_t{1} << static_cast<std::uint8_t>(bit_index);
  }

  constexpr bool AffectedPlayers::isAffected(PlayerColor player) const
  {
    const std::uint8_t mask = getBitmask(player);
    if (!mask)
    {
      throw std::out_of_range("AffectedPlayers::isAffected(): player is out of range.");
    }
    return (bitset & mask) != 0;
  }

  constexpr void AffectedPlayers::setAffected(PlayerColor player, bool is_affected)
  {
    const std::uint8_t mask = getBitmask(player);
    if (!mask)
    {
      throw std::out_of_range("AffectedPlayers::setAffected(): player is out of range.");
    }
    if (is_affected)
    {
      bitset |= mask;
    }
    else
    {
      bitset &= (~mask);
    }
  }
}
