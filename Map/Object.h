#pragma once

#include <h3mtxt/Map/ObjectDetailsVariant.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

#include <cstdint>

namespace h3m
{
  // Represents an object on the Adventure Map.
  struct Object
  {
    // Coordinates of the bottom right corner.
    std::uint8_t x {};
    std::uint8_t y {};
    std::uint8_t z {};
    // 0-based index of the corresponding ObjectTemplate in Map.objects_templates.
    std::uint32_t template_idx {};
    // Should be all 0s; kept here for compatibility.
    ReservedData<5> unknown {};
    // Data specific to ObjectTemplate corresponding to this object.
    ObjectDetailsVariant details;
  };
}
