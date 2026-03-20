#pragma once

#include <cstdint>

namespace h3m
{
  // Flags used in h3m::Tile.
  // Each enumerator is a 0-based index of the bit in the bitmask.
  enum class TileFlag : std::uint8_t
  {
    // Controls whether the terrain sprite should be flipped horizontally.
    TerrainHorizontalFlip = 0,
    // Controls whether the terrain sprite should be flipped vertically.
    TerrainVerticalFlip = 1,
    // Controls whether the river sprite should be flipped horizontally.
    RiverHorizontalFlip=  2,
    // Controls whether the river sprite should be flipped vertically.
    RiverVerticalFlip = 3,
    // Controls whether the road sprite should be flipped horizontally.
    RoadHorizontalFlip = 4,
    // Controls whether the road sprite should be flipped vertically.
    RoadVerticalFlip = 5,
    // The coast bit does 2 things:
    // 1. If set to 1, it overrides the battlefield terrain for this tile (the battle will take place on the coast).
    //    * Water tiles are NOT affected - even if you set the coast bit to 1 for a Water tile,
    //      the battlefield for this tile will still be the ship deck.
    //    * Rock tiles are affected. Note that normally the game crashes if you start a battle on a Rock tile;
    //      setting the coast bit to 1 fixes this.
    // 2. It controls whether landing is possible on this tile: a hero on a boat cannot land on a tile with
    //    the coast bit set to 0.
    //    * Note that it's impossible to land on Rock or Water tiles even if they have the coast bit set to 1.
    // The Map Editor sets the coast bit to 1 for non-water tiles adjacent to water tiles (including corners),
    // 0 for all other tiles.
    Coast = 6,
    // Always set to 0 by the Map Editor; not sure if it does anything. Some parsers call it "favorable winds", idk why.
    Unknown = 7
  };
}
