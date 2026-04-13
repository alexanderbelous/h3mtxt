#pragma once

#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Constants/MapFormat.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>
#include <h3mtxt/Map/MapBasicInfo.h>
#include <h3mtxt/Map/ObjectTemplate.h>
#include <h3mtxt/Map/Object.h>
#include <h3mtxt/Map/PlayerSpecs.h>
#include <h3mtxt/Map/Tile.h>
#include <h3mtxt/Map/TimedEvent.h>

#include <vector>

namespace h3m
{
  // Represents a *.h3m map.
  struct Map
  {
    // Equality comparison.
    //
    // Two maps are considered equal if their representation in the H3M file format is identical.
    // This function doesn't serialize the maps, though - instead, it compares the subobjects. This
    // has lower space complexity (O(1)) and is guaranteed not to throw exceptions.
    //
    // \param other - map to compare with.
    // \return true if *this is equal to @other, false otherwise.
    bool operator==(const Map& other) const noexcept = default;

    // Returns the tile with the specified coordinates.
    // \param x - X-coordinate of the tile.
    // \param y - Y-coordinate of the tile.
    // \param z - Z-coordinate of the tile.
    // \return the tile with coordinates (x, y, z).
    // \throw std::out_of_range if the coordinates (x, y, z) do not refer to a valid tile
    //        or if this->tiles is too short.
    constexpr Tile& getTile(std::uint32_t x, std::uint32_t y, std::uint32_t z);

    // Returns the tile with the specified coordinates.
    // \param x - X-coordinate of the tile.
    // \param y - Y-coordinate of the tile.
    // \param z - Z-coordinate of the tile.
    // \return the tile with coordinates (x, y, z).
    // \throw std::out_of_range if the coordinates (x, y, z) do not refer to a valid tile
    //        or if this->tiles is too short.
    constexpr const Tile& getTile(std::uint32_t x, std::uint32_t y, std::uint32_t z) const;

    // Format of the map ("Map Specifications"/"Map version" in the Editor).
    MapFormat format = MapFormat::ShadowOfDeath;
    // Basic information about the map ("Map Specifications"/"General" tab in the Editor).
    MapBasicInfo basic_info;
    // Settings for each player ("Map Specifications"/"Player specs" tab in the Editor).
    EnumIndexedArray<PlayerColor, PlayerSpecs, kMaxPlayers> players {};
    // Additional information about the map ("Special Victory Condition", "Special Loss Condition",
    // "Teams", "Heroes", "Artifacts", "Spells", "Secondary Skills" and "Rumors" tabs in the Editor).
    MapAdditionalInfo additional_info;
    // Terrain data for each tile on the map.
    // The number of elements must be equal to countTiles(basic_info).
    std::vector<Tile> tiles;
    // "Templates" for objects on the Adventure Map.
    // .h3m splits objects' properties into 2 structures: a template (called "Advanced Properties"
    // in Unleashed Editor), which can be shared between multiple objects, and everything else
    // (called "Properties" in the Map Editor and Unleashed Editor).
    std::vector<ObjectTemplate> objects_templates;
    // Objects on the Adventure Map.
    std::vector<Object> objects;
    // Global events on this map ("Map Specifications"/"Timed Events" tab in the Editor).
    std::vector<TimedEvent> global_events;
    // Should be 0s. Kept here for compatibility.
    ReservedData<124> padding;
  };

  constexpr Tile& Map::getTile(std::uint32_t x, std::uint32_t y, std::uint32_t z)
  {
    return const_cast<Tile&>(static_cast<const Map&>(*this).getTile(x, y, z));
  }

  constexpr const Tile& Map::getTile(std::uint32_t x, std::uint32_t y, std::uint32_t z) const
  {
    if (x >= basic_info.map_size || y >= basic_info.map_size || z >= countLevels(basic_info))
    {
      throw std::out_of_range("Map::getTile(): invalid coordinates.");
    }
    const std::size_t tile_idx = (static_cast<std::size_t>(z) * basic_info.map_size + y) * basic_info.map_size + x;
    return tiles.at(tile_idx);
  }
}
