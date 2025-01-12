#pragma once

#include <h3mparser/Map/Base.h>
#include <h3mparser/Map/Constants/MapDifficulty.h>

#include <cstdint>
#include <string>

namespace h3m
{

struct MapBasicInfo
{
  // False if there are no heroes and towns on the map, true otherwise.
  Bool is_playable {};
  // Width and height of the map.
  std::uint32_t map_size {};
  // False if there is only 1 level on the map, true if there are 2 levels.
  Bool has_two_levels {};
  // The name of the map.
  std::string name;
  // Description of the map.
  std::string description;
  // Difficulty level.
  MapDifficulty difficulty {};
  // Maximum allowed level for all heroes.
  std::uint8_t max_hero_level {};
};

}
