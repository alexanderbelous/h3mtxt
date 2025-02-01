#pragma once

#include <h3mtxt/Map/MapFwd.h>

namespace h3m
{
  // Replaces the sprites of "pure" Lava tiles with random animated Lava sprites.
  //
  // "Pure" Lava tiles are tiles with the sprites [49; 72], which are only used by
  // the Map Editor for Lava tiles that only have Lava tiles (no matter the sprite)
  // as immediate neighbors.
  // \param map - map to modify.
  void makeUltimateLava(h3m::Map& map);
}
