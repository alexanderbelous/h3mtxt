#pragma once

// See https://github.com/HeroWO-js/h3m2json/blob/master/h3m-The-Corpus.txt

#include <h3mparser/Constants/Constants.h>
#include <h3mparser/Constants/HeroType.h>
#include <h3mparser/Constants/MapDifficulty.h>
#include <h3mparser/Constants/MapFormat.h>
#include <h3mparser/Base.h>
#include <h3mparser/GlobalEvent.h>
#include <h3mparser/LossCondition.h>
#include <h3mparser/PlayerSpecs.h>
#include <h3mparser/Tile.h>
#include <h3mparser/VictoryCondition.h>

#include <array>
#include <bitset>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

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
    struct CustomHero
    {
      HeroType type {};
      // 0xFF for default.
      std::uint8_t face {};
      // Hero's name, or an empty string if the default name should be used instead.
      std::string name;
      // Bitset indicating which players can hire this hero.
      std::bitset<kMaxPlayers> can_hire {};
    };

    VictoryCondition victory_condition {};
    LossCondition loss_condition {};
    // Details about the teams, std::nullopt if teams are disabled.
    std::optional<TeamsInfo> teams;
    // TODO: 20 bytes bitfield for heroes' availability.
    std::vector<HeroType> placeholder_heroes;
    std::vector<CustomHero> custom_heroes;
    // Must be all 0s; kept here to ensure compatibility.
    std::array<std::uint8_t, 31> reserved;
    // TODO: add the rest.
  };

  MapFormat format = MapFormat::ShadowOfDeath;
  MapBasicInfo basic_info;
  std::array<PlayerSpecs, kMaxPlayers> players {};
  AdditionalInfo additional_info;
  // N elements, where N = (has_two_levels ? 2 : 1) * map_size * map_size.
  std::vector<Tile> tiles;
  // TODO: add objects.
  // Global events on this map (called "Timed Events" in the Editor).
  std::vector<GlobalEvent> global_events;
  // Should be 0s. Kept here for compatibility.
  std::array<std::uint8_t, 124> padding;
};

}
