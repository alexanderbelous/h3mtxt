#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/RiverType.h>
#include <h3mtxt/Map/Constants/RoadType.h>
#include <h3mtxt/Map/Constants/TerrainType.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/SavedGame/Constants/TileFlag.h>
#include <h3mtxt/SavedGame/ObjectPropertiesVariant.h>

#include <cstdint>
#include <vector>

namespace h3svg
{
  // Represents a sprite tile of an object on the Adventure Map.
  // This is used in Tile::objects_to_render to specify which objects to render on that tile.
  struct TileRenderInfo
  {
    constexpr bool operator==(const TileRenderInfo&) const noexcept = default;

    // 0-based index of the object from SavedGame::objects.
    std::uint16_t object_idx {};
    // Coordinates of the sprite tile of @object_idx to render.
    // The bottom right corner of the sprite is used as the reference (0, 0);
    // the X axis points left, the Y axis points up.
    std::uint8_t x : 4 {};
    std::uint8_t y : 4 {};
    // Establishes the order in which to render Tile::objects_to_render;
    // * By default, the value is almost always equal to `y-1`.
    // * 0 is a special value used for objects that are part of the ground.
    // * Values >= 7 don't appear by default.
    // * Objects with the same `z_buffer` value will be rendered in order of their appearence
    //   in in Tile::objects_to_render.
    std::uint8_t z_buffer {};
  };

  // The equivalent of h3m::Tile stored in the saved game.
  struct Tile
  {
    bool operator==(const Tile&) const noexcept = default;

    TerrainType terrain_type {};
    std::uint8_t terrain_sprite {};
    RiverType river_type = RiverType::None;
    std::uint8_t river_sprite = 0;
    RoadType road_type = RoadType::None;
    std::uint8_t road_sprite = 0;
    TileFlags flags;
    // Subclass of the object at this tile (whose object_class is object_properties.objectClass()).
    // * Refugee Camp is an exception: instead of storing the sublass of the object (which is always 0),
    //   it stores CreatureType of the currently available creature.
    // * The value is usually 0xFFFF if there's no object on this tile.
    std::uint16_t object_subclass = static_cast<std::uint16_t>(-1);
    // 0-based index of the object in SavedGame::objects that is displayed on this tile,
    // or 0xFFFF if there is no object on this tile.
    std::uint16_t object_idx = static_cast<std::uint16_t>(-1);
    // ObjectClass and the "simple" properties of the object at this tile.
    ObjectPropertiesVariant object_properties;
    // Objects whose sprites overlap with the current tile.
    // The sprites will be rendered in order of TileRenderInfo::z_buffer; sprites with the same Z-buffer value
    // will be rendered in order of their appearance in this array.
    std::vector<TileRenderInfo> objects_to_render;
  };
}
