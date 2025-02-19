#pragma once

#include <h3mtxt/Map/Utils/BitSet.h>

#include <type_traits>

namespace h3m
{
  // Wrapper for BitSet<N> (which is itself a wrapper for an array of N bytes) that
  // stores a bit for each constant of the specified enum.
  //
  // This is just to reduce boilerplate.
  template<class Enum, std::size_t NumBytes>
  struct EnumBitmask
  {
    static_assert(std::is_enum_v<Enum>, "Must be an enum type.");

    static constexpr std::size_t kNumBytes = NumBytes;
    static constexpr std::size_t kNumBits = NumBytes * 8;

    // Returns the value for the specified enum constant.
    // \param enum_value - input enum constant.
    // \return the value of the bit for @enum_value.
    // \throw std::out_of_range if std::size_t(enum_value) >= NumBytes * 8.
    constexpr bool operator[](Enum enum_value) const;

    // Set the value for the specified enum constant.
    // \param enum_value - input enum constant.
    // \param value - value to set.
    // \throw std::out_of_range if std::size_t(enum_value) >= NumBytes * 8.
    constexpr void set(Enum enum_value, bool value);

    BitSet<NumBytes> bitset;
  };

  template<class Enum, std::size_t NumBytes>
  constexpr bool EnumBitmask<Enum, NumBytes>::operator[](Enum enum_value) const
  {
    return bitset.at(static_cast<std::size_t>(enum_value));
  }

  template<class Enum, std::size_t NumBytes>
  constexpr void EnumBitmask<Enum, NumBytes>::set(Enum enum_value, bool value)
  {
    bitset.set(static_cast<std::size_t>(enum_value), value);
  }
}
