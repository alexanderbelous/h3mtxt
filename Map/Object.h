#pragma once

#include <h3mtxt/Map/ObjectDetailsDataVariant.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

#include <cstdint>

namespace h3m
{
  // Represents an object on the Adventure Map.
  // TODO: consider renaming:
  // * ObjectDetailsData -> ObjectDetails.
  struct Object
  {
    // Coordinates of the bottom right corner.
    std::uint8_t x {};
    std::uint8_t y {};
    std::uint8_t z {};
    // 0-based index of the corresponding ObjectTemplate in Map.objects_templates.
    std::uint32_t kind {};
    // Should be all 0s; kept here for compatibility.
    ReservedData<5> unknown {};
    // Object-specific data.
    // TODO: consider renaming to additional_info.
    ObjectDetailsDataVariant details;
  };
}
