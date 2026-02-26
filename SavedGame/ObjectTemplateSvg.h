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
    // possibly - a 6x8 boolean matrix, where A[i][j] indicates whether the sprite tile (i, j)
    // exists, i.e. A[i][j] = (5 - i < height) && (7 - j < width).
    // Actually, it's not necessarily redundant - it's possible that sprite tiles with no visible
    // pixels are filtered out.
    std::array<std::byte, 6> unknown1 {};
    std::array<std::uint8_t, 6> passability {};
    // TODO: identify.
    // possibly - similar to @unknown1, but for shadows.
    std::array<std::byte, 6> unknown2{};
    std::array<std::uint8_t, 6> actionability {};
    std::uint16_t object_class {};
    std::uint16_t object_subclass {};
    // TODO: identify.
    std::array<std::byte, 2> unknown3 {};
    Bool is_ground {};
  };
}
