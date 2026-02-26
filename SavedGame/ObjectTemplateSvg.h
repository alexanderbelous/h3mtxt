#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Map/MapFwd.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace h3m
{
  // The equivalent of h3m::ObjectTemplate stored in the saved game.
  struct ObjectTemplateSvg
  {
    // Length-prefixed string; length is serialized as a 16-bit little-endian integer.
    std::string def;
    // Width of the sprite (in tiles).
    std::uint8_t width {};
    // Height of the sprite (in tiles).
    std::uint8_t height {};
    // TODO: identify.
    // Possibly - a 6x8 boolean matrix, where A[i][j] indicates whether the sprite tile (i, j)
    // has any visible pixels..
    std::array<std::byte, 6> unknown1 {};
    std::array<std::uint8_t, 6> passability {};
    // TODO: identify.
    // possibly - similar to @unknown1, but for shadows.
    std::array<std::byte, 6> unknown2 {};
    std::array<std::uint8_t, 6> actionability {};
    std::uint16_t object_class {};
    std::uint16_t object_subclass {};
    // TODO: identify.
    // Seems to always be {0, 0}, so it makes sense to replace it with ReservedData<2>, or
    // to define object_sublcass as uint32_t. The latter would be inconsistent, because
    // TileSvg::object_subclass is clearly a 16-bit integer.
    std::array<std::byte, 2> unknown3 {};
    Bool is_ground {};
  };
}
