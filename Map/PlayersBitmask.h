#pragma once

#include <h3mtxt/Map/Constants/PlayerColor.h>

#include <cstdint>
#include <stdexcept>

namespace h3m
{
  // Bit array storing a bit for each player.
  //
  // .h3m file format uses such bitmasks in multiple places, e.g. which players can hire
  // a specific hero, Global Event, Event object on the adventure map, or a Event in a town).
  struct PlayersBitmask
  {
  private:
    // Constructs a bitmask for the given player.
    // \param player - player for which to construct a bitmask.
    // \return an 8-bit unsigned integer with all bits except int(player) set to 0,
    //         or 0 if @player is not a valid PlayerColor.
    static constexpr std::uint8_t getBitmask(PlayerColor player) noexcept;

  public:
    // Checks if the bit is set for the specified player.
    // \param player - player to check.
    // \return true if the bit is set in the bitmask for @player, false otherwise.
    constexpr bool operator[](PlayerColor player) const;

    // Sets the value of the bit for the specified player.
    // \param player - player for which to set the bit.
    // \param value - value to set.
    constexpr void set(PlayerColor player, bool value);

    std::uint8_t bitset {};
  };

  constexpr std::uint8_t PlayersBitmask::getBitmask(PlayerColor player) noexcept
  {
    const auto bit_index = static_cast<std::underlying_type_t<PlayerColor>>(player);
    if (bit_index >= 8)
    {
      return 0;
    }
    return std::uint8_t{1} << static_cast<std::uint8_t>(bit_index);
  }

  constexpr bool PlayersBitmask::operator[](PlayerColor player) const
  {
    const std::uint8_t mask = getBitmask(player);
    if (!mask)
    {
      throw std::out_of_range("PlayersBitmask::operator[](): player is out of range.");
    }
    return (bitset & mask) != 0;
  }

  constexpr void PlayersBitmask::set(PlayerColor player, bool value)
  {
    const std::uint8_t mask = getBitmask(player);
    if (!mask)
    {
      throw std::out_of_range("PlayersBitmask::set(): player is out of range.");
    }
    if (value)
    {
      bitset |= mask;
    }
    else
    {
      bitset &= (~mask);
    }
  }
}
