#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Map/PlayerSpecs.h>

#include <cstdint>
#include <optional>

namespace h3m
{
  struct Coordinates
  {
    std::uint8_t x{};
    std::uint8_t y{};
    std::uint8_t z{};
  };

  // The equivalent of h3m::PlayersSpecs stored in the saved game.
  struct PlayerSpecsSvg
  {
    Bool can_be_human{};
    Bool can_be_computer{};
    PlayerBehavior behavior{};
    TownsBitmask allowed_alignments;
    // TODO: figure out what this is (has_random_heroes?).
    std::byte unknown;
    // Initial coordinates of the hero that was generated for this player at the start of the game,
    // or std::nullopt if no hero was generated.
    // Note that a hero can only be generated inside the main town, so this can also be interpreted
    // as the coordinates of the main town.
    std::optional<Coordinates> generated_hero_coordinates;
    // Note that in saved games the length of the string StartingHero::name is
    // serialized as a 16-bit integer (in .h3m it's serialized as a 32-bit integer).
    StartingHero starting_hero;
  };
}
