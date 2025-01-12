#pragma once

#include <h3mparser/Map/Constants/HeroType.h>
#include <h3mparser/Map/Constants/PlayerBehavior.h>
#include <h3mparser/Map/Constants/TownType.h>
#include <h3mparser/Map/Base.h>

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace h3m
{

// Information about the player's main town.
struct MainTown
{
  // True if "Generate hero at main town" is set, false otherwise.
  Bool generate_hero {};
  // Type of the player's main town.
  TownType town_type;
  // X-coordinate of the main town.
  std::uint8_t x;
  // Y-coordinate of the main town.
  std::uint8_t y;
  // Z-coordinate of the main town.
  std::uint8_t z;
};

// Information about the player's starting hero.
struct StartingHero
{
  Bool is_random {};
  // 0xFF if random.
  HeroType type {};
  // TODO: probably should be an enum; 0xFF for default.
  std::uint8_t face {};
  // Hero's name. Empty string means that the default name is used.
  std::string name;
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

struct PlayerSpecs
{
  Bool can_be_human {};
  Bool can_be_computer {};
  PlayerBehavior behavior {};
  Bool customized_alignments {};
  // (bitfield: Castle, Rampart, Tower, Inferno, Necropolis, Dungeon, Stronghold, Fortress; Complete: 8 Conflux)
  // TODO: replace with BitSet.
  std::uint8_t town_types {};
  // Bitfield with 1 LSB bit.
  std::uint8_t town_conflux {};
  // True if the player's alignment is random, false otherwise.
  // If true, implies that all town types are enabled.
  Bool random_town {};
  // Info about the main town, std::nullopt if the player doesn't have a main town.
  std::optional<MainTown> main_town;
  StartingHero starting_hero;
  AdditionalPlayerInfo additional_info;
};

}
