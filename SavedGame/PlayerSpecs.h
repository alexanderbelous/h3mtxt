#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/PlayerSpecs.h>
#include <h3mtxt/Map/Coordinates.h>

#include <optional>

namespace h3svg
{
  // The equivalent of h3m::PlayersSpecs stored in the saved game.
  struct PlayerSpecs
  {
    Bool can_be_human {};
    Bool can_be_computer {};
    PlayerBehavior behavior {};
    TownsBitmask allowed_alignments;
    // True if Random alignment is enabled, false otherwise.
    Bool allow_random_alignment {};
    // Initial coordinates of the hero that was generated for this player at the start of the game,
    // or std::nullopt if no hero was generated.
    // Note that a hero can only be generated inside the main town, so this can also be interpreted
    // as the coordinates of the main town.
    std::optional<Coordinates> generated_hero_coordinates;
    StartingHero starting_hero;
  };
}
