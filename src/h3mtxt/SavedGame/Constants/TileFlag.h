#pragma once

#include <cstdint>

namespace h3svg
{
  // Flags used in h3svg::Tile.
  //
  // Each enumerator is a 0-based index of the bit in the bitmask.
  // Note that this is different from h3m::TileFlag.
  enum class TileFlag : std::uint8_t
  {
    // Controls whether the terrain sprite should be flipped horizontally.
    TerrainHorizontalFlip = 0,
    // Controls whether the terrain sprite should be flipped vertically.
    TerrainVerticalFlip = 1,
    // Controls whether the river sprite should be flipped horizontally.
    RiverHorizontalFlip = 2,
    // Controls whether the river sprite should be flipped vertically.
    RiverVerticalFlip = 3,
    // Controls whether the road sprite should be flipped horizontally.
    RoadHorizontalFlip = 4,
    // Controls whether the road sprite should be flipped vertically.
    RoadVerticalFlip = 5,
    // Indicates whether digging is possible on this tile.
    // * Note that this is a necessary but not a sufficient condition: e.g., digging is never possible
    //   on Water tiles or on actionable tiles of objects.
    IsDiggable = 6,
    // Indicates whether the tile is animated.
    // * By default, this is equivalent to
    //     (terrain_type == TerrainType::Water) ||
    //     (terrain_type == TerrainType::Lava) ||
    //     (river_type != RiverType::None)
    //   Note that the game treats all Lava sprites as animated, even though only a few of them are.
    // * The game seems to ignore this flag anyway: manually setting the value to 0 for an animated
    //   tile does not make it static.
    IsAnimated = 7,
    // Indicates whether the tile is obstructed, i.e. that there's an obstacle on it
    // or that this is TerrainType::Rock.
    // * Note that actionable tiles of objects are not considered obstacles, even if heroes
    //   cannot move on them (e.g., the actionable tiles of Shipwrecks).
    IsObstructed = 8,
    // Indicates whether this is a ground tile adjacent to water OR a water tile adjacent to ground.
    IsWaterEdge = 9,
    // Indicates if this is an actionable tile of some visible object (i.e. excluding Events and Grail).
    IsActionable = 12
  };
}
