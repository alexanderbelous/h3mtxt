#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Map/MapFwd.h>

#include <array>
#include <type_traits>

namespace h3m
{
  // Wrapper for std::array<h3m::Bool, N> that allows using values of the specified enum type as
  // indices without explicitly casting them to integers.
  //
  // This is similar to h3m::EnumBitmask, but doesn't pack bits.
  // 
  // In H3SVG there are a few places where arrays of boolean values are used instead of bitmasks -
  // this is not space-efficient, but h3mtxt aims to represent the saved game losslessly - if H3SVG
  // uses a byte to represent a boolean, then so should we.
  template<class Enum, std::size_t NumElements>
  struct EnumBoolmask
  {
    static_assert(std::is_enum_v<Enum>, "Must be an enum type.");

    // Mutable access to the value for the specified enum constant.
    // \param enum_value - input enum constant.
    // \return a mutable reference to the boolean value for @enum_value.
    // \throw std::out_of_range if std::size_t(enum_value) >= NumElements.
    constexpr Bool& operator[](Enum enum_value);

    // Read-only access to the value for the specified enum constant.
    // \param enum_value - input enum constant.
    // \return a const reference to the boolean value for @enum_value.
    // \throw std::out_of_range if std::size_t(enum_value) >= NumElements.
    constexpr const Bool& operator[](Enum enum_value) const;

    std::array<Bool, NumElements> data {};
  };

  template<class Enum, std::size_t NumElements>
  constexpr Bool& EnumBoolmask<Enum, NumElements>::operator[](Enum enum_value)
  {
    return data.at(static_cast<std::size_t>(enum_value));
  }

  template<class Enum, std::size_t NumElements>
  constexpr const Bool& EnumBoolmask<Enum, NumElements>::operator[](Enum enum_value) const
  {
    return data.at(static_cast<std::size_t>(enum_value));
  }
}
