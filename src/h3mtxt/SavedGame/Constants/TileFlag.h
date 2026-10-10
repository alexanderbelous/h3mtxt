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
    // Indicates whether this is a passable tile, i.e. that this is not TerrainType::Rock
    // and that there are no impassible non-actionable objects on it.
    // * Note that this doesn't necessarily mean that a hero can move on this tile: for example,
    //   a hero can never move on the actionable tile of a Shipwreck.
    IsPassable = 6,
    // TODO: reverse-engineer.
    // Seems to always be set for Water tiles, but appears on ground tiles as well.
    Unknown7 = 7,
    // Indicates whether the tile is obstructed, i.e. that there's an obstacle on it
    // or that this is TerrainType::Rock.
    // * Note that actionable tiles of objects are not considered obstacles, even if heroes
    //   cannot move on them (e.g., the actionable tiles of Shipwrecks).
    // * The value of the bit seems to be always the opposite of IsPassable.
    //   TODO: try modifying them manually and check how the game uses them.
    IsObstructed = 8,
    // TODO: reverse-engineer.
    // Seems to have something to do with coast: the bit is set for ground tiles adjacent to water
    // and for water tiles adjacent to ground.
    Unknown9 = 9,
    // Indicates if this is an actionable tile of some visible object (i.e. excluding Events and Grail).
    IsActionable = 12
  };
}
