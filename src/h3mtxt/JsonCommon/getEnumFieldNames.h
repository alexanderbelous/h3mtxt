#pragma once

#include <h3mtxt/JsonCommon/JsonCommonFwd.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <span>
#include <string_view>
#include <type_traits>
#include <vector>

namespace h3json
{
  namespace Detail_NS
  {
    template<class T>
    struct IsStdArray : std::false_type {};

    template<class T, std::size_t N>
    struct IsStdArray<std::array<T, N>> : std::true_type {};

    // Checks if the input array of strings contains duplicates.
    // \param fields - input array of strings.
    // \return true if there are duplicates in @fields, false otherwise.
    consteval bool hasDuplicates(std::span<const std::string_view> fields)
    {
      // This is not optimal: it has O(N*logN) time complexity, even though
      // this check can be done in O(N). However, std::unordered_set is not
      // constexpr, so we cannot use it for compile-time checks.
      std::vector<std::string_view> data{ fields.begin(), fields.end() };
      std::sort(data.begin(), data.end());
      return std::adjacent_find(data.begin(), data.end()) != data.end();
    }
  }

  // Safely gets the names for the first N constants of the specified Enum type.
  //
  // A compilation error will be triggered if any of these conditions is not satisfied:
  // * The type of kEnumFieldNames<Enum> is std::array<std::string_view, M> for some number M.
  // * M >= N.
  // * kEnumFieldNames<Enum> doesn't have duplicates.
  //
  // \return the first N elements from h3json::kEnumFieldNames<Enum>.
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
    // Check that there are no duplicates.
    static_assert(!Detail_NS::hasDuplicates(kEnumFieldNames<Enum>), "kEnumFieldNames<Enum> has duplicates.");
    // Check that the number of elements is greater than or equal to N.
    // TODO: consider auto-generating names for padding bits for EnumBitmask.
    static_assert(kEnumFieldNames<Enum>.size() >= N,
                  "The number of elements in kEnumFieldNames<Enum> must be greater than or equal to N.");
    return std::span<const std::string_view, N>{kEnumFieldNames<Enum>.data(), N};
  }
}
