#pragma once

#include <h3mtxt/Map/MapFwd.h>

namespace h3m
{
  // Fills the entire map with random tiles of the specified TerrainType.
  //
  // Only non-decorative terrain sprites are used.
  // \param map - map to modify.
  // \param terrain_type - type of the terrain.
  void fillWithTerrain(Map& map, TerrainType terrain_type);
}