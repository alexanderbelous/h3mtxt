#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Constants/ResourceType.h>
#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>
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
    std::uint8_t num_towns = 0;
    // ID of the currently selected town, or -1 if there is none.
    std::int8_t current_town = -1;
    // IDs of towns owned by the player (see Town::id). Only the first @num_towns elements are meaningful - the
    // rest are usually set to 0xFF.
    // Note that the Map Editor forbids placing more than 48 towns on the Adventure Map, but this
    // array has room for 72.
    std::array<std::int8_t, 72> towns {};
    Resources resources;
    // 1 bit per Mystical Garden, indicating if the player has visited it this week.
    BitSet<4> mystical_gardens;
    // TODO: figure out what this is.
    // Really does seem to be BitSet<4> magic_springs.
    std::array<std::uint8_t, 4> unknown3 {};
    // 1 bit per Corpse, indicating if the player has visited it.
    BitSet<4> corpses;
    // 1 bit per Lean To, indicating if the player has visited it.
    BitSet<4> lean_tos;
    // TODO: figure out what this is.
    std::array<std::uint8_t, 3> unknown4 {};
  };
}
