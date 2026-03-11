#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3svg
{
  // The equivalent of h3m::PlayerBehavior in H3SVG.
  //
  // Note that the constants for the player's behavior in H3SVG differ from the ones in H3M.
  // However, both enums are used in the saved games (h3svg::PlayerSpecs uses h3m::PlayerBehavior), so
  // we shouldn't reuse the same name.
  //
  // Since this is called "Personality" in the game (in the Tavern / Den of Thieves), I will do the same.
  enum class PlayerPersonality : std::uint32_t
  {
    Warrior = 0,
    Builder = 1,
    Exporer = 2,
    Human = 3
  };
}
