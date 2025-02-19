#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace h3m
{

// Bitset.
//
// Bitsets are used a lot in H3M. While I could use the standard std::bitset class, it doesn't
// provide access to the underlying bytes, so this class is used instead.
//
// \param NumBytes - the number of bytes.
template<std::size_t NumBytes>
struct BitSet
{
  static constexpr std::size_t kNumBits = NumBytes * 8;

  // Read-only access to the specified bit.
  // \param index - 0-based index of the bit. No bounds checking is performed; the behavior is undefined if
  //        index >= kNumBits.
  // \return the value of the specified bit.
  constexpr bool operator[](std::size_t index) const;

  // Same as above, but throws std::out_of_range if index >= kNumBits.
  constexpr bool at(std::size_t index) const;

  // Assigns a value to the specified bit.
  // \param index - 0-based index of the bit.
  // \param value - value to assign.
  // \throw std::out_of_range if index >= kNumBits.
  constexpr void set(std::size_t index, bool value);

  // 0th bit is the LSB of the 0th byte.
  // 7th bit is the MSB of the 0th byte.
  // 8th bit is the LSB of the 1st byte.
  // ...
  std::array<std::uint8_t, NumBytes> data {};
};

template<std::size_t NumBytes>
constexpr bool BitSet<NumBytes>::operator[](std::size_t index) const
{
  const std::size_t byte_index = index / 8;
  const std::size_t bit_index_in_byte = index % 8;
  const std::uint8_t mask = 1 << bit_index_in_byte;
  return data[byte_index] & mask;
}

template<std::size_t NumBytes>
constexpr bool BitSet<NumBytes>::at(std::size_t index) const
{
  if (index >= kNumBits)
  {
    throw std::out_of_range("BitSet::at(): index is out of range");
  }
  return (*this)[index];
}

template<std::size_t NumBytes>
constexpr void BitSet<NumBytes>::set(std::size_t index, bool value)
{
  if (index >= kNumBits)
  {
    throw std::out_of_range("BitSet::set(): index is out of range");
  }
  const std::size_t byte_index = index / 8;
  const std::size_t bit_index_in_byte = index % 8;
  // Bitmask with all bits except @bit_index_in_byte set to 0.
  const std::uint8_t mask = 1 << bit_index_in_byte;
  if (value)
  {
    data[byte_index] |= mask;
  }
  else
  {
    data[byte_index] &= (~mask);
  }
}

}
