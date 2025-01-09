#pragma once

#include <h3mparser/HeroType.h>

#include <array>
#include <bitset>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace h3m
{

// The number of resources (Wood, Mercury, Ore, Sulfur, Crystal, Gems, Gold).
inline constexpr std::uint8_t kNumResources = 7;

// The maximum number of players.
inline constexpr std::uint8_t kMaxPlayers = 8;

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
  bool is_playable = true;
  // Width and height of the map.
  std::uint32_t map_size {};
  // False if there is only 1 level on the map, true if there are 2 levels.
  bool has_two_levels = false;
  // The name of the map.
  std::string name;
  // Description of the map.
  std::string description;
  // Difficulty level.
  MapDifficulty difficulty {};
  // Maximum allowed level for all heroes.
  std::uint8_t max_hero_level {};
};

enum class PlayerBehavior : std::uint8_t
{
  Random = 0,
  Warrior = 1,
  Builder = 2,
  Explorer = 3,
};

struct AdditionalPlayerInfo
{
  struct HeroInfo
  {
    HeroType type;
    // If empty, the default name is implied.
    std::string name;
  };

  std::uint8_t num_placeholder_heroes {};
  // Includes Visiting heroes and regular hero objects (not random);
  // includes placeholder heroes configured as "Specific hero" rather than "Power rating";
  // type/name match the object's.
  std::vector<HeroInfo> heroes;
};

struct PlayerInfo
{
  bool can_be_human {};
  bool can_be_computer {};
  PlayerBehavior behavior {};
  std::uint8_t customized_alignments {};
  std::uint8_t town_types {};
  // Bitfield with 1 LSB bit.
  std::uint8_t town_conflux {};
  std::uint8_t random_town {};
  bool has_main_town {};
  // TODO: starting hero info
  AdditionalPlayerInfo additional_info;
};

enum class VictoryConditionType : std::uint8_t
{
  AcquireArtifact = 0,
  AccumulateCreatures = 1,
  AccumulateResources = 2,
  UpgradeTown = 3,
  BuildGrail = 4,
  DefeatHero = 5,
  CaptureTown = 6,
  DefeatMonster = 7,
  FlagDwellings = 8,
  FlagMines = 9,
  TransportArtifact = 10,
  Normal = 0xFF,
};

enum class LossConditionType : std::uint8_t
{
  LoseTown = 0,
  LoseHero = 1,
  TimeExpires = 2,
  Normal = 0xFF,
};

struct TeamsInfo
{
  std::uint8_t num_teams {};
  // Each value should be < num_teams.
  std::array<std::uint8_t, 8> team_for_player {};
};

enum class TerrainType : std::uint8_t
{
  Dirt = 0,
  Sand = 1,
  Grass = 2,
  Snow = 3,
  Swamp = 4,
  Rough = 5,
  Subterranean = 6,
  Lava = 7,
  Water = 8,
  Rock = 9,
};

enum class RiverType : std::uint8_t
{
  None = 0,
  Clear = 1,
  Icy = 2,
  Muddy = 3,
  Lava = 4,
};

enum class RoadType : std::uint8_t
{
  None = 0,
  Dirt = 1,
  Gravel = 2,
  Cobblestone = 3,
};

struct Tile
{
  TerrainType terrain_type {};
  // Object subclass.
  std::uint8_t terrain_sprite {};
  RiverType river_type {};
  // (0-3 corners, 4 + , 5 6 T, 7 8 |-, 9 10 | , 11 12--)
  std::uint8_t river_sprite {};
  RoadType road_type {};
  // (0-5 corners, 6 7 |-, 8 9 T, 10 11 | , 12 13 --, 14 ', 15 -, 16 +)
  std::uint8_t road_sprite {};
  // Bitfield: horizontal terrain, vertical terrain, horizontal river, vertical river,
  //           horizontal road, vertical road, coast, favorable winds
  std::uint8_t mirroring {};
};

struct GlobalEvent
{
  // Event name as shown in the Editor.
  std::string name;
  std::string message;
  // Given/taken resources.
  std::array<std::int32_t, kNumResources> resources {};
  std::bitset<kMaxPlayers> affected_players {};
  bool applies_to_human {};
  bool applies_to_computer {};
  // 0-based day of first occurence (e.g., 0 stands for Day 1).
  std::uint16_t day_of_first_occurence {};
  // 0 means that the event doesn't repeat.
  std::uint8_t repeat_after_days {};
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

  MapFormat format_ = MapFormat::ShadowOfDeath;
  MapBasicInfo basic_info;
  std::array<PlayerInfo, 8> players {};
  AdditionalInfo additional_info;
  // N elements, where N = (has_two_levels ? 2 : 1) * map_size * map_size.
  std::vector<Tile> tiles;
  // TODO: add objects.
  std::vector<GlobalEvent> global_events;
};

}
