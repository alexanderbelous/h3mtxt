#pragma once

#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Constants/ResourceType.h>

#include <array>
#include <cstdint>

namespace h3m
{
  // Represents an amount of resources.
  //
  // In H3M the amount is always interpreted as int32, even though the Map Editor
  // doesn't allow entering negative values in some contexts (Quest Guard and
  // as a reward for defeating a monster).
  struct Resources
  {
    // \return the amount for the specified ResouceType.
    constexpr std::int32_t& operator[](ResourceType resource_type);

    // \return the amount for the specified ResouceType.
    constexpr std::int32_t operator[](ResourceType resource_type) const;

    // The amount for each resource type.
    std::array<std::int32_t, kNumResources> data {};
  };

  constexpr std::int32_t& Resources::operator[](ResourceType resource_type)
  {
    return data.at(static_cast<std::size_t>(resource_type));
  }

  constexpr std::int32_t Resources::operator[](ResourceType resource_type) const
  {
    return data.at(static_cast<std::size_t>(resource_type));
  }
}
