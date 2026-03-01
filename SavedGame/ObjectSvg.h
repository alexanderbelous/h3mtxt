#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/SavedGame/Coordinates.h>

#include <cstdint>

namespace h3m
{
  // The equivalent of h3m::Object stored in the saved game.
  // Unlike H3M, H3SVG stores the properties of the object separately from the object itself.
  struct ObjectSvg
  {
    // Coordinates of the bottom right corner.
    Coordinates coordinates;
    // 0-based index of the corresponding element in SavedGame::objects_templates.
    std::uint16_t template_idx {};
  };
}
