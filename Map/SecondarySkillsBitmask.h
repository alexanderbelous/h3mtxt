#pragma once

#include <h3mtxt/Map/Constants/SecondarySkillType.h>
#include <h3mtxt/Map/Utils/BitSet.h>

namespace h3m
{
  // Wrapper for BitSet<4> (which is itself a wrapper for an array of 4 bytes) that
  // stores a bit for each secondary skill.
  struct SecondarySkillsBitmask
  {
    constexpr bool operator[](SecondarySkillType secondary_skill) const
    {
      return bitset.at(static_cast<std::size_t>(secondary_skill));
    }

    constexpr void set(SecondarySkillType secondary_skill, bool value)
    {
      bitset.set(static_cast<std::size_t>(secondary_skill), value);
    }

    BitSet<4> bitset;
  };
}
