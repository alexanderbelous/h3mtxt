#pragma once

#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Constants/ResourceType.h>

#include <array>
#include <cstdint>

namespace h3m
{
  // Represents an amount of resources.
  //
  // In SoD the amount is always stored as either int32 or uint32:
  // * In Timed Events and Pandora's Boxes it's int32.
  // * In Quest Guards and as a reward for defeating a monster it's uint32.
  template<class T>
  struct Resources
  {
    // \return the amount for the specified ResouceType.
    constexpr T& operator[](ResourceType resource_type);

    // \return the amount for the specified ResouceType.
    constexpr T operator[](ResourceType resource_type) const;

    // The amount for each resource type.
    std::array<T, kNumResources> data {};
  };

  template<class T>
  constexpr T& Resources<T>::operator[](ResourceType resource_type)
  {
    return data.at(static_cast<std::size_t>(resource_type));
  }

  template<class T>
  constexpr T Resources<T>::operator[](ResourceType resource_type) const
  {
    return data.at(static_cast<std::size_t>(resource_type));
  }
}
