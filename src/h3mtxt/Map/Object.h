#pragma once

#include <h3mtxt/Map/Coordinates.h>
#include <h3mtxt/Map/ObjectPropertiesVariant.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

#include <cstdint>

namespace h3m
{
  // Represents an object on the Adventure Map.
  struct Object
  {
    bool operator==(const Object&) const noexcept = default;

    // Coordinates of the bottom right corner.
    Coordinates coordinates;
    // 0-based index of the corresponding ObjectTemplate in Map.objects_templates.
    std::uint32_t template_idx {};
    // Should be all 0s; kept here for compatibility.
    ReservedData<5> unknown {};
    // Data specific to ObjectTemplate corresponding to this object.
    ObjectPropertiesVariant properties;
  };
}
