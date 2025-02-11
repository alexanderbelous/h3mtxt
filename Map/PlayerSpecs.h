#pragma once

#include <h3mtxt/Map/Constants/HeroPortrait.h>
#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Constants/PlayerBehavior.h>
#include <h3mtxt/Map/Constants/TownType.h>
#include <h3mtxt/Map/Base.h>
#include <h3mtxt/Map/TownsBitmask.h>

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
  // 0xFF is a special value that means Random.
  TownType town_type {};
  // X-coordinate of the main town.
  std::uint8_t x {};
  // Y-coordinate of the main town.
  std::uint8_t y {};
  // Z-coordinate of the main town.
  std::uint8_t z {};
};

// Information about the player's starting hero (displayed when starting a new game).
struct StartingHero
{
  // HeroType of the starting hero, or 0xFF if None (i.e. if
  // the game shouldn't display the starting hero when starting a new game).
  HeroType type {0xFF};

  // The fields below are only read/written if type != 0xFF.

  // Portrait of the starting hero, or 0xFF for default.
  HeroPortrait portrait = HeroPortrait::DEFAULT;
  // Hero's name. Empty string means that the default name is used.
  std::string name;
};

struct PlayerSpecs
{
  struct HeroInfo
  {
    HeroType type{};
    // If empty, the default name is implied.
    std::string name;
  };

  Bool can_be_human {};
  // The Editor doesn't allow unchecking "Can be Computer".
  Bool can_be_computer {};
  PlayerBehavior behavior {};
  Bool customized_alignments {};
  TownsBitmask allowed_alignments;
  // True if the player's alignment is random, false otherwise.
  // If true, implies that all town types are enabled.
  Bool random_town {};
  // Info about the main town, std::nullopt if the player doesn't have a main town.
  std::optional<MainTown> main_town;
  // 1 if the player starts with at least 1 Random Hero, 0 otherwise.
  Bool has_random_heroes {};
  StartingHero starting_hero;
  // The number of non-specific placeholder heroes (i.e. configured as "Power Rating" rather than "Specific hero")
  // at the beginning of the game.
  std::uint8_t num_nonspecific_placeholder_heroes {};
  // Specific heroes that the player has at the beginning of the game:
  // * Includes Visiting heroes and regular hero objects (not random).
  // * Includes placeholder heroes configured as "Specific hero" rather than "Power rating".
  std::vector<HeroInfo> heroes;
};

}
