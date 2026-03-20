#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/Map/Utils/SpriteTilesBitmask.h>

#include <cstdint>
#include <string>

namespace h3svg
{
  // The equivalent of h3m::ObjectTemplate stored in the saved game.
  struct ObjectTemplate
  {
    // Filename of the sprite to use for objects that use this template.
    std::string def;
    // Width of the sprite (in tiles).
    std::uint8_t width {};
    // Height of the sprite (in tiles).
    std::uint8_t height {};
    // TODO: identify.
    // Possibly - a 6x8 boolean matrix, where A[i][j] indicates whether the sprite tile (i, j)
    // has any visible pixels..
    SpriteTilesBitmask unknown1;
    SpriteTilesBitmask passability;
    // TODO: identify.
    // possibly - similar to @unknown1, but for shadows.
    SpriteTilesBitmask unknown2;
    SpriteTilesBitmask actionability;
    std::uint16_t object_class {};
    std::uint16_t object_subclass {};
    ReservedData<2> reserved;
    Bool is_ground {};
  };
}
