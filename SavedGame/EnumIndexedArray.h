#pragma once

#include <array>
#include <cstddef>
#include <type_traits>

namespace h3svg
{
  // Wrapper for std::array<T, N> which allows indexing elements of the array via
  // values of the specified enum type without explicitly casting them to integers.
  //
  // This is semantically equivalent to std::map<Enum, T> whose keys are
  // { Enum{0}, Enum{1}, Enum{2}, ..., Enum{N-1} }.
  //
  // Such structures appear in multiple places in H3SVG.
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
    return data.at(static_cast<std::size_t>(key));
  }

  template<class Enum, class T, std::size_t NumElements>
  constexpr const T& EnumIndexedArray<Enum, T, NumElements>::operator[](Enum key) const
  {
    return data.at(static_cast<std::size_t>(key));
  }
}
