#pragma once

#include <h3mtxt/Map/Base.h>
#include <h3mtxt/Map/Constants/ObjectClass.h>
#include <h3mtxt/Map/Constants/ObjectGroup.h>

#include <array>
#include <cstdint>
#include <string>

namespace h3m
{
  struct ObjectAttributes
  {
    // Name of the *.def sprite to use.
    std::string def;
    std::array<std::uint8_t, 6> passability{};
    std::array<std::uint8_t, 6> actionability{};
    // TODO: replace with a wrapper class around BitSet.
    std::uint16_t allowed_landscapes {};
    // Bitfield.
    std::uint16_t landscape_group {};
    ObjectClass object_class {};
    std::uint32_t object_number {};
    ObjectGroup object_group {};
    Bool is_ground {};
    // Should be 0s. Kept here for compatibility.
    std::array<std::uint8_t, 16> unknown {};
  };
}
