#pragma once

#include <array>
#include <string_view>

namespace h3json
{
  // Provides the names for the values of the specified Enum type, so that they can be used as
  // the names of fields for a JSON object.
  //
  // Specializations of this template can and should change the type to std::array<std::string_view, N>,
  // where N specifies the range of enum values for which the names are provided,
  // i.e. Enum{0}, Enum{1}, ... Enum{N-1}.
  //
  // This is used to serialize h3m::EnumBitmask.
  template<class Enum>
  inline constexpr std::array<std::string_view, 0> kEnumFieldNames {};
}

// TODO: move to h3json.
namespace h3m
{
  // Stores the names of JSON fields for the specified class.
  // This is to ensure that H3JsonWriter and H3JsonReader use the same names:
  // * A typo in a string will only be discovered at runtime, but a typo in a static
  //   data member will cause a compilation error.
  // * This also guarantees that these strings are only stored once in the binary,
  //   even if string pooling is disabled.
  template<class T>
  struct FieldNames;
}
