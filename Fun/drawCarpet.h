#pragma once

#include <h3mtxt/Map/MapFwd.h>

namespace h3m
{
  // Draws a "carpet" on the overground level of the input map.
  //
  // Here, a "carpet" is a pattern in which all tiles have the same sprite but different mirroring.
  // Specifically, the pattern is:
  //   01230123
  //   23012301
  //   01230123
  //   23012301
  //   01230123
  //
  // By changing the @initial_mirroring parameter you can change the pattern to
  //   1032   2301   3210
  //   3210   0123   1032
  //
  // You can notice that the pattern creates a roughly hexagonal grid:
  // +--+--+--+--+--+  where all 2x2 blocks are identical. For some terrain sprites
  // |  |--|  |--|  |  this can create interesting patterns.
  // +--|  |--|  |--+
  // |  |--|  |--|  |
  // +--|  |--|  |--+
  // |  |--|  |--|  |
  // +--+--+--+--+--+
  //
  // \param map - map to modify.
  // \param terrain_type - terrain type to use.
  // \param terrain_sprite - sprite to use for @terrain_type.
  // \param initial_mirroring - terrain mirroring for the top left tile.
  void drawCarpet(Map& map, TerrainType terrain_type, std::uint8_t terrain_sprite, std::uint8_t initial_mirroring = 0);

  // Similar to drawCarpet() above, but only draws a single 2x2 block at the specified location.
  void drawCarpetBlock(Map& map, TerrainType terrain_type, std::uint8_t terrain_sprite,
                       std::uint32_t x, std::uint32_t y, std::uint32_t z,
                       std::uint8_t initial_mirroring = 0);
}
