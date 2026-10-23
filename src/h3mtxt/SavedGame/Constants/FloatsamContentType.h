#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3svg
{
  enum class FloatsamContentType : std::int32_t
  {
    // // Used in ObjectProperties<ObjectPropertiesType::Floatsam> for non-actionable tiles
    // of nonstandard Floatsam objects.
    // NonActionableTile = -1,
    None = 0,
    Wood5 = 1,
    Wood5Gold200 = 2,
    Wood10Gold500 = 3
  };
}
