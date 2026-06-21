#pragma once

#include <h3mtxt/Map/MapFwd.h>

#include <type_traits>

namespace h3m
{
  // Represents a quantity of items of a specific type.
  //
  // Structures like this appear in multiple places in H3M/H3C, mostly with CreatureType or ResourceType.
  template<class Enum, class Quantity>
  struct TypedQuantity
  {
    static_assert(std::is_enum_v<Enum>, "Enum must be an enumerator type.");
    static_assert(std::is_integral_v<Quantity>, "Quantity must be an integral type.");

    constexpr bool operator==(const TypedQuantity&) const noexcept = default;

    Enum type {};
    Quantity quantity {};
  };
}
