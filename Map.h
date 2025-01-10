#pragma once

// See https://github.com/HeroWO-js/h3m2json/blob/master/h3m-The-Corpus.txt

#include <h3mparser/Constants/Constants.h>
#include <h3mparser/Constants/HeroType.h>
#include <h3mparser/Constants/LossConditionType.h>
#include <h3mparser/Constants/RiverType.h>
#include <h3mparser/Constants/RoadType.h>
#include <h3mparser/Constants/TerrainType.h>
#include <h3mparser/Constants/VictoryConditionType.h>
#include <h3mparser/Base.h>
#include <h3mparser/GlobalEvent.h>
#include <h3mparser/PlayerSpecs.h>
#include <h3mparser/Tile.h>

#include <array>
#include <bitset>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace h3m
{

enum class MapFormat : std::uint32_t
{
  RestorationOfErathia = 0x0E,
  ArmageddonsBlade = 0x15,
  ShadowOfDeath = 0x1C,
};

enum class MapDifficulty : std::uint8_t
{
  Easy = 0,
  Normal = 1,
  Hard = 2,
  Expert = 3,
  Impossible = 4,
};

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

struct TeamsInfo
{
  std::uint8_t num_teams {};
  // Each value should be < num_teams.
  std::array<std::uint8_t, 8> team_for_player {};
};

struct Map
{
  struct AdditionalInfo
  {
    VictoryConditionType victory_condition_type {};
    // TODO: add details for special victory conditions.
    LossConditionType loss_condition_type {};
    // TODO: add details for special loss conditions.
    // std::nullopt if teams are disabled.
    std::optional<TeamsInfo> teams;
    // TODO: 20 bytes bitfield for heroes' availability.
    std::uint32_t num_placeholder_heroes {};
    // TODO: add the rest.
  };

  MapFormat format = MapFormat::ShadowOfDeath;
  MapBasicInfo basic_info;
  std::array<PlayerSpecs, 8> players {};
  AdditionalInfo additional_info;
  // N elements, where N = (has_two_levels ? 2 : 1) * map_size * map_size.
  std::vector<Tile> tiles;
  // TODO: add objects.
  std::vector<GlobalEvent> global_events;
};

}
