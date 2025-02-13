#pragma once

#include <h3mtxt/Map/Base.h>
#include <h3mtxt/Map/Constants/MapDifficulty.h>

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
  // Maximum allowed level for all heroes. 0 means to limit.
  std::uint8_t max_hero_level {};
};

// Computes the number of levels on the map.
// \param basic_info - input map.
// \return the number of levels (i.e. 1 if there's no subterranean level, 2 otherwise).
constexpr std::uint8_t countLevels(const MapBasicInfo& basic_info) noexcept
{
  return basic_info.has_two_levels ? 2 : 1;
}

// Computes the total number of tiles on the map.
// \param basic_info - input map.
// \return the total number of tiles (including the tiles on the subterranean level, if present).
constexpr std::size_t countTiles(const MapBasicInfo& basic_info) noexcept
{
  return static_cast<std::size_t>(countLevels(basic_info)) * basic_info.map_size * basic_info.map_size;
}

}
