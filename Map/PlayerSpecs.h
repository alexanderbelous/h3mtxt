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

// Information about the player's starting hero.
struct StartingHero
{
  Bool is_random {};
  // 0xFF if random.
  HeroType type {};
  // 0xFF for default.
  HeroPortrait portrait = HeroPortrait::DEFAULT;
  // Hero's name. Empty string means that the default name is used.
  std::string name;
};

struct AdditionalPlayerInfo
{
  struct HeroInfo
  {
    HeroType type {};
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
  TownsBitmask allowed_alignments;
  // True if the player's alignment is random, false otherwise.
  // If true, implies that all town types are enabled.
  Bool random_town {};
  // Info about the main town, std::nullopt if the player doesn't have a main town.
  std::optional<MainTown> main_town;
  StartingHero starting_hero;
  // AdditionalPlayerInfo is not always present - see the comments for
  // shouldHaveAdditionalPlayerInfo() below.
  AdditionalPlayerInfo additional_info;
};

// Checks if AdditionalPlayerInfo should be read/written for the given PlayerSpecs.
//
// AdditionalPlayerInfo is not always present in PlayerSpecs. The external description of the H3M file format
// is somewhat unclear on when exactly it's missing. This function seems to determine the condition correctly,
// but it would be nice to verify it somehow.
// \param player_specs - input PlayerSpecs.
constexpr bool shouldHaveAdditionalPlayerInfo(const PlayerSpecs& player_specs) noexcept
{
  // The Editor doesn't allow unchecking "Can be Computer";
  // Both can_be_human and can_be_computer are false for players that are not present on the map
  // at all.
  // TODO: this condition might be redundant - the Editor always sets starting_hero.type to 0xFF for
  // players that are not present on the map.
  if (!player_specs.can_be_human && !player_specs.can_be_computer)
  {
    return false;
  }
  // If the starting hero is not random - AdditionalPlayerInfo should be present.
  if (player_specs.starting_hero.type != HeroType{ 0xFF })
  {
    return true;
  }
  return false;
}

}
