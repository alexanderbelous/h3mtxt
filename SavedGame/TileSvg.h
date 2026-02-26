#pragma once

#include <h3mtxt/SavedGame/TileSvg.h>
#include <h3mtxt/Map/Tile.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace h3m
{
  // The equivalent of h3m::Tile stored in the saved game.
  struct TileSvg
  {
    struct ObjectToRender
    {
      // 0-based index of the object from SavedGame::objects.
      std::uint16_t object_idx {};
      // TODO: figure out what this is.
      // Somehow determines the sprite tile of @object_idx to render.
      std::uint16_t unknown {};
    };

    TerrainType terrain_type {};
    std::uint8_t terrain_sprite {};
    RiverType river_type {};
    std::uint8_t river_sprite {};
    RoadType road_type {};
    std::uint8_t road_sprite {};
    // TODO: replace with EnumBitmask.
    // flags1 defines terrain_x, terrain_y, river_x, river_y flags:
    //   bool terrain_x = flags1 & 1;
    //   bool terrain_y = flags1 & 2;
    //   bool river_x   = flags1 & 4;
    //   bool river_y   = flags1 & 8;
    //   bool road_x    = flags1 & 16;
    //   bool road_y    = flags1 & 32;
    // hypothesis:
    //   bool no_obstacles = flags1 & 64;  // or "passable"
    std::uint8_t flags1 {};
    std::uint8_t flags2 {};
    // Note: in H3SVG it is serialized as a 16-bit integer, even though in h3m it is serialized as a 32-bit integer.
    std::uint16_t object_class {};
    // object_subclass or  0xFFFF if there's no object on this tile (i.e. if object_class == 0 || object_class == 3).
    std::uint16_t object_subclass {};
    // 0-based index of the object in SavedGame::objects that is displayed on this tile,
    // or 0xFFFF if there is no object on this tile
    std::uint16_t object_idx {};
    // TODO: figure out what this is.
    std::array<std::byte, 4> unknown {};
    // Objects whose sprites overlap with the current tile.
    // The sprites will be rendered in order the respective objects appear in the vector
    // (0th object is rendered first, then 1st object is rendered on top of it, etc).
    std::vector<ObjectToRender> objects_to_render;
  };
}
