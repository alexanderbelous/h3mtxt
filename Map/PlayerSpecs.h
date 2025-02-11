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
//
// The logic is quite interesting:
// * If type == 0xFF, then the starting hero will not be displayed (the game will show "None"
//   instead).
// * Even if type != 0xFF but portrait == 0xFF, then the starting hero will not be displayed (also "None").
// * You can "lie" about any detail about the starting hero (type, portrait, name),
//   e.g., claim that the player starts with Gelu even though Gelu is not one of the starting heroes.
struct StartingHero
{
  // HeroType of the starting hero, or 0xFF if None (i.e. if
  // the game shouldn't display the starting hero when starting a new game).
  HeroType type {0xFF};

  // The fields below are only read/written if type != 0xFF.

  // Portrait of the starting hero.
  // The starting hero will not be displayed if portrait == 0xFF. However, the Editor
  // does sometimes set this to 0xFF, which causes "None" to be displayed instead of the
  // starting hero.
  //
  // If portrait == 163 (the value immediately after the last valid portrait), a portrait
  // with a question mark ('?') will be displayed.
  // If portrait is within [164; 254], the game will crash when you go to advanced options
  // in the main menu.
  HeroPortrait portrait = HeroPortrait::DEFAULT;
  // Hero's name. Empty string means that the default name is used.
  std::string name;
};

// "Map Specifications" -> "Player Specs" in the Editor.
// The Editor doesn't allow to modify some fields, though.
//
// Note that some other H3M parsers have a different interpretation of this
// structure: they assume that StartingHero always has @portrait and @name
// fields, yet @num_nonspecific_placeholder_heroes and @heroes might be
// missing. However, they are wrong and I'm right, lol. It's a lucky
// coincidence that when starting_hero.type = 0xFF and the player has no
// specific heroes in the beginning, the binary data is "compatible" - the
// length of the string in StartingHero::name is serialized as uint32, same as
// the number of elements in @heroes. If, however, the player does start with
// specific placeholder heroes (which is common in campaigns), then the
// other interpretation is incorrect.
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
  // 1 if the player starts with at least one Random Hero, 0 otherwise.
  // This only affects the main menu when you start a new game; if has_random_heroes != 0,
  // then you will be offered to select the starting hero, otherwise you won't be.
  // If has_random_heroes != 0 but the player doesn't actually have random heroes (on the
  // adventure map or generated in the main town) you will still be offered to select the
  // starting hero, but this will have no effect.
  Bool has_random_heroes {};
  // Starting hero as displayed when starting a new game.
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
