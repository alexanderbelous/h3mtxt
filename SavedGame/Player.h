#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Resources.h>
#include <h3mtxt/SavedGame/Constants/PlayerPersonality.h>

#include <array>
#include <cstdint>

namespace h3svg
{
  // Represents the current state of a player.
  struct Player
  {
    PlayerColor player_color {};
    std::uint8_t num_heroes {};
    // HeroType of the currently active hero, 0xFF if there is none.
    HeroType active_hero {};
    // All heroes on the Adventure Map (i.e. not garrisoned inside towns).
    // If the player has fewer than 8 heroes, 0xFF is used in empty slots.
    std::array<HeroType, 8> heroes {};
    std::array<HeroType, 2> heroes_in_tavern {};
    // TODO: figure out what this is.
    std::uint8_t unknown1 {};
    PlayerPersonality personality {};
    // TODO: figure out what this is.
    std::array<std::uint8_t, 5> unknown2 {};
    // The number of days left to live without a town, or -1 if the player has at least 1 town.
    std::int8_t days_left {};
    // The number of towns owned by the player.
    std::uint8_t num_towns {};
    // ID of the currently selected town, or -1 if there is none.
    std::int8_t current_town {};
    // IDs of towns owned by the player (see Town::id). Only the first @num_towns elements are meaningful - the
    // rest are usually set to 0xFF.
    std::array<std::int8_t, 48> towns {};
    // TODO: figure out what this is.
    // Each element seems to always be 0xFF. Maybe reserved for more towns?
    std::array<std::uint8_t, 24> unknown3 {};
    Resources resources;
    // 1 bit per Mystical Garden, indicating if the player has visited it this week.
    BitSet<4> mystical_gardens;
    // TODO: figure out what this is.
    std::array<std::uint8_t, 4> unknown4 {};
    // 1 bit per Corpse, indicating if the player has visited it.
    BitSet<4> corpses;
    // 1 bit per Lean To, indicating if the player has visited it.
    BitSet<4> lean_tos;
    // TODO: figure out what this is.
    std::array<std::uint8_t, 3> unknown5 {};
  };
}
