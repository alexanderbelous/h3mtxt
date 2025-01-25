#pragma once

#include <h3mtxt/Map/Constants/SpellType.h>
#include <h3mtxt/Map/Utils/BitSet.h>

namespace h3m
{
  // Wrapper for BitSet<9> (which is itself a wrapper for an array of 9 bytes) that
  // stores a bit for each spell.
  //
  // Note that there are only 70 spells in Shadow of Death, but this bitmask
  // stores 72 bits.
  struct SpellsBitmask
  {
    constexpr bool operator[](SpellType spell) const
    {
      return bitset.at(static_cast<std::size_t>(spell));
    }

    constexpr void set(SpellType spell, bool value)
    {
      bitset.set(static_cast<std::size_t>(spell), value);
    }

    BitSet<9> bitset;
  };
}
