#pragma once

#include <array>
#include <cstddef>
#include <type_traits>

namespace h3svg
{
  namespace Detail_NS
  {
    // Constructs an array in which all elements are initialized with the same value.
    //
    // This is just to replace boilerplate when adding member initializers - the same can
    // be achieved via lambda functions, but doing that every time leads to code duplication.
    //
    // \param N - the number of elements in the array.
    // \param T - type of elements (cv and ref qualifiers will be dropped).
    // \param value - the value to initialize the elements with.
    // \return the constructed array.
    template<std::size_t N, class T>
    constexpr std::array<std::remove_cvref_t<T>, N> makeArrayOfDuplicates(const T& value)
    {
      std::array<T, N> result;
      result.fill(value);
      return result;
    }
  }
}
