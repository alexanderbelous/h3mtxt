#pragma once

#include <h3mtxt/Map/Utils/BitSet.h>

#include <type_traits>

namespace h3m
{
  // Wrapper for BitSet<N> (which is itself a wrapper for an array of N bytes) that
  // stores a bit for each constant of the specified enum.
  //
  // This is just to reduce boilerplate.
  //
  // Note that the class treats the underlying enum values as unsigned integers even if the declaration of
  // Enum uses a signed integer for the underlying type. This is to address the following issue:
  //   enum class ArtifactType8 : std::int8_t
  //   {
  //     Spellbook                   = 0,                              // 0x00
  //     SpellScroll                 = 1,                              // 0x01
  //     ...
  //     ArmageddonsBlade            = static_cast<std::int8_t>(128),  // 0x80
  //     ...
  //     IronfistOfTheOgre           = static_cast<std::int8_t>(143),  // 0x8F
  //     None                        = -1                              // 0xFF
  //   };
  //
  //   static_assert(static_cast<std::size_t>(ArtifactType8::ArmageddonsBlade) == 18446744073709551488;
  //   static_assert(static_cast<std::uint8_t>(ArtifactType8::ArmageddonsBlade) = 128;
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

    constexpr bool operator==(const EnumBitmask& other) const noexcept = default;

    BitSet<NumBytes> bitset;
  };

  template<class Enum, std::size_t NumBytes>
  constexpr bool EnumBitmask<Enum, NumBytes>::operator[](Enum enum_value) const
  {
    using UnderlyingTypeUnsigned = std::make_unsigned_t<std::underlying_type_t<Enum>>;
    return bitset.at(static_cast<UnderlyingTypeUnsigned>(enum_value));
  }

  template<class Enum, std::size_t NumBytes>
  constexpr void EnumBitmask<Enum, NumBytes>::set(Enum enum_value, bool value)
  {
    using UnderlyingTypeUnsigned = std::make_unsigned_t<std::underlying_type_t<Enum>>;
    bitset.set(static_cast<UnderlyingTypeUnsigned>(enum_value), value);
  }
}
