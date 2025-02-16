#pragma once

#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Constants/TownType.h>

namespace h3m
{
  // Wrapper for BitSet<2> (which is itself a wrapper for an array of 2 bytes) that
  // stores a bit for each TownType.
  //
  // Note that there are only 9 towns in Shadow of Death, but this bitmask
  // stores 16 bits. The last 7 bits are normally set to 0 in .h3m regardless of the meaning
  // of the bitmask.
  struct TownsBitmask
  {
    // Constructs a bitset with all town types disabled.
    constexpr TownsBitmask() noexcept = default;

    explicit constexpr TownsBitmask(const BitSet<2>& bitset) noexcept;

    // Returns the value for the specified town type.
    // \param town - input town type.
    // \return the value of the bit for @town.
    // \throw std::out_of_range if int(town) >= 16.
    constexpr bool operator[](TownType town) const;

    // Set the value for the specified town type.
    // \param town - input town type.
    // \param value - value to set.
    // \throw std::out_of_range if int(town) >= 16.
    constexpr void set(TownType town, bool value);

    BitSet<2> bitset {};
  };

  constexpr TownsBitmask::TownsBitmask(const BitSet<2>& bitset) noexcept :
    bitset(bitset)
  {}

  constexpr bool TownsBitmask::operator[](TownType town) const
  {
    return bitset.at(static_cast<std::underlying_type_t<TownType>>(town));
  }

  constexpr void TownsBitmask::set(TownType town, bool value)
  {
    bitset.set(static_cast<std::underlying_type_t<TownType>>(town), value);
  }
}
