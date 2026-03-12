#pragma once

#include <h3mtxt/Map/MapFwd.h>

#include <array>
#include <cstddef>
#include <type_traits>

namespace h3m
{
  // Wrapper for std::array<T, N> which allows indexing elements of the array via
  // values of the specified enum type without explicitly casting them to integers.
  //
  // This is semantically equivalent to std::map<Enum, T> whose keys are
  // { Enum{0}, Enum{1}, Enum{2}, ..., Enum{N-1} }.
  //
  // Note that the class treats the underlying enum values as unsigned integers even if the declaration of
  // Enum uses a signed integer for the underlying type. This is to address the following issue:
  //   enum class HeroTypeSigned : std::int8_t
  //   {
  //     Orrin = 0x00,
  //     Valeska = 0x01,
  //     ...
  //     Pasis = 0x80,
  //     ...
  //     Xeron = 0x9B,
  //     None = 0xFF
  //   };
  //
  //   static_assert(static_cast<std::size_t>(HeroTypeSigned::Pasis) == 18446744073709551488;
  //   static_assert(static_cast<std::uint8_t>(HeroTypeSigned::Pasis) = 128;
  template<class Enum, class T, std::size_t NumElements>
  struct EnumIndexedArray
  {
    static_assert(std::is_enum_v<Enum>, "Must be an enum type.");

    // Mutable access to the value for the specified enum constant.
    // \param key - input enum constant.
    // \return a mutable reference to the mapped value for @key.
    // \throw std::out_of_range if std::size_t(key) >= NumElements.
    constexpr T& operator[](Enum key);

    // Read-only access to the value for the specified enum constant.
    // \param key - input enum constant.
    // \return a const reference to the mapped value for @key.
    // \throw std::out_of_range if std::size_t(key) >= NumElements.
    constexpr const T& operator[](Enum key) const;

    // The underlying array.
    std::array<T, NumElements> data {};
  };

  template<class Enum, class T, std::size_t NumElements>
  constexpr T& EnumIndexedArray<Enum, T, NumElements>::operator[](Enum key)
  {
    using UnderlyingTypeUnsigned = std::make_unsigned_t<std::underlying_type_t<Enum>>;
    return data.at(static_cast<UnderlyingTypeUnsigned>(key));
  }

  template<class Enum, class T, std::size_t NumElements>
  constexpr const T& EnumIndexedArray<Enum, T, NumElements>::operator[](Enum key) const
  {
    using UnderlyingTypeUnsigned = std::make_unsigned_t<std::underlying_type_t<Enum>>;
    return data.at(static_cast<UnderlyingTypeUnsigned>(key));
  }
}
