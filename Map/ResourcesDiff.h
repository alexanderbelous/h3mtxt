#pragma once

#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Constants/ResourceType.h>

#include <array>
#include <cstdint>

namespace h3m
{
  // Given/taken resources.
  // This appears in at least 2 places: Timed Events and Pandora's Boxes.
  struct ResourcesDiff
  {
    // \return the given/taken amount for the specified ResouceType.
    constexpr std::int32_t& operator[](ResourceType resource_type);

    // \return the given/taken amount for the specified ResouceType.
    constexpr std::int32_t operator[](ResourceType resource_type) const;

    // Given/taken amount for each resource type.
    std::array<std::int32_t, kNumResources> data {};
  };

  constexpr std::int32_t& ResourcesDiff::operator[](ResourceType resource_type)
  {
    return data.at(static_cast<std::size_t>(resource_type));
  }

  constexpr std::int32_t ResourcesDiff::operator[](ResourceType resource_type) const
  {
    return data.at(static_cast<std::size_t>(resource_type));
  }
}
