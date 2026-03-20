#pragma once

#include <h3mtxt/JsonCommon/JsonCommonFwd.h>

#include <array>
#include <cstddef>
#include <span>
#include <string_view>
#include <type_traits>

namespace h3json
{
  namespace Detail_NS
  {
    template<class T>
    struct IsStdArray : std::false_type {};

    template<class T, std::size_t N>
    struct IsStdArray<std::array<T, N>> : std::true_type {};
  }

  // Safely gets the names for the first N constants of the specified Enum type.
  //
  // A compilation error will be triggered if the type of kEnumFieldNames<Enum> is not std::array<std::string_view, M>
  // for some number M, or if M < N.
  //
  // \return the names of the first N Enum constants from h3json::kEnumFieldNames<Enum>.
  template<class Enum, std::size_t N>
  consteval std::span<const std::string_view, N> getEnumFieldNames()
  {
    // The type of h3json::kEnumFieldNames<Enum> without const, volatile and reference qualifiers.
    using EnumFieldNamesType = std::remove_cvref_t<decltype(kEnumFieldNames<Enum>)>;
    // Check that h3json::kEnumFieldNames<Enum> is an std::array.
    static_assert(Detail_NS::IsStdArray<EnumFieldNamesType>::value,
                  "kEnumFieldNames<Enum> must be an std::array.");
    // Check that its elements have the type std::string_view.
    static_assert(std::is_same_v<typename EnumFieldNamesType::value_type, std::string_view>,
                  "The type of elements in kEnumFieldNames<Enum> must be std::string_view.");
    // Check that the number of elements is greater than or equal to N.
    // TODO: consider auto-generating names for padding bits for EnumBitmask.
    static_assert(kEnumFieldNames<Enum>.size() >= N,
                  "The number of elements in kEnumFieldNames<Enum> must be greater than or equal to N.");
    return std::span<const std::string_view, N>{kEnumFieldNames<Enum>.data(), N};
  }
}
