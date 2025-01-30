#pragma once

#include <h3mtxt/Map/MapFwd.h>

namespace h3m
{
  // Draws a "fake" island at the specified location.
  //
  // A "fake" island is a 4x4 region with specific Water tiles, which
  // look like a diamond-shaped spot of land, but actually it's all water.
  // \param map - map to modify.
  // \param x - X coordinate of the top left corner of the region.
  // \param y - Y coordinate of the top left corner of the region.
  void drawFakeIsland(Map& map, std::uint32_t x, std::uint32_t y);

  // Draws a "fake" mini-island at the specified location.
  //
  // A "fake" mini-island is a 2x2 region with specific Water tiles, which
  // look as if there's a small spot of land in the center, but actually it's all water.
  // \param map - map to modify.
  // \param x - X coordinate of the top left corner of the mini-island.
  // \param y - Y coordinate of the top left corner of the mini-island.
  void drawFakeMiniIsland(Map& map, std::uint32_t x, std::uint32_t y);

  // Draws a "fake" vertical strip of land at the specified location.
  //
  // A "fake" vertical strip of land is a 2xN region with specific Water tiles, which
  // look as if it's thin strip of land, but actually it's all water.
  // \param map - map to modify.
  // \param x - X coordinate of the top left corner of the strip.
  // \param y - Y coordinate of the top left corner of the strip.
  // \param length - the length of the strip in H3M tiles.
  void drawFakeVerticalLandStrip(Map& map, std::uint32_t x, std::uint32_t y, std::uint32_t length);

  // Draws a "fake" diagonal strip of land at the specified location.
  //
  // A "fake" diagonal strip of land is a (N+4)xN region with specific Water tiles,
  // which looks like a diagonal strip of land from NW to SE, but actually it's all water.
  void drawFakeDiagonalLandStripSE(Map& map, std::uint32_t x, std::uint32_t y, std::uint32_t length);
}