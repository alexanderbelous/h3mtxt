#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/ObjectClass.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/Map/Utils/SpriteTilesBitmask.h>

#include <cstdint>
#include <string>

namespace h3svg
{
  // The equivalent of h3m::ObjectTemplate stored in the saved game.
  struct ObjectTemplate
  {
    constexpr bool operator==(const ObjectTemplate&) const noexcept = default;

    // Filename of the sprite to use for objects that use this template.
    std::string def;
    // Width of the sprite (in tiles).
    std::uint8_t width {};
    // Height of the sprite (in tiles).
    std::uint8_t height {};
    // 6x8 boolean matrix, where A[i][j] indicates whether the object sprite has any visible pixels at tile (i, j).
    SpriteTilesBitmask colors;
    SpriteTilesBitmask passability;
    // 6x8 boolean matrix, where A[i][j] indicates whether the shadow sprite has any visible pixels at tile (i, j).
    SpriteTilesBitmask shadows;
    SpriteTilesBitmask actionability;
    ObjectClass16 object_class = static_cast<ObjectClass16>(ObjectClass::NONE);
    std::uint16_t object_subclass = 0;
    ReservedData<2> reserved;
    Bool is_ground {};
  };
}
