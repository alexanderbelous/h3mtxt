#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Constants/ResourceType.h>
#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>
#include <h3mtxt/SavedGame/Constants/PlayerPersonality.h>
#include <h3mtxt/SavedGame/Utils.h>

#include <array>
#include <cstdint>

namespace h3svg
{
  // Represents the current state of a player.
  struct Player
  {
    PlayerColor player_color {};
    std::uint8_t num_heroes = 0;
    // HeroType of the currently active hero, 0xFF if there is none.
    HeroType active_hero = HeroType{0xFF};
    // All heroes on the Adventure Map (i.e. not garrisoned inside towns).
    // If the player has fewer than 8 heroes, 0xFF is used in empty slots.
    std::array<HeroType, 8> heroes = Detail_NS::makeArrayOfDuplicates<8>(HeroType{ 0xFF });
    std::array<HeroType, 2> heroes_in_tavern = Detail_NS::makeArrayOfDuplicates<2>(HeroType{ 0xFF });
    // TODO: figure out what this is.
    std::uint8_t unknown1 {};
    PlayerPersonality personality {};
    // TODO: figure out what this is.
    std::array<std::uint8_t, 5> unknown2 {};
    // The number of days left to live without a town, or -1 if the player has at least 1 town.
    std::int8_t days_left = -1;
    // The number of towns owned by the player.
    std::uint8_t num_towns = 0;
    // ID of the currently selected town, or -1 if there is none.
    std::int8_t current_town = -1;
    // IDs of towns owned by the player (see Town::id). Only the first @num_towns elements are
    // meaningful - the rest are usually set to 0xFF.
    // Note that the Map Editor forbids placing more than 48 towns on the Adventure Map,
    // but this array has room for 72.
    std::array<std::int8_t, 72> towns = Detail_NS::makeArrayOfDuplicates<72>(std::int8_t{ -1 });
    Resources resources;
    // 1 bit per Mystical Garden, indicating if the player has visited it this week.
    BitSet<4> mystical_gardens;
    // 1 bit per Magic Spring, indicating if the player has visited it this week.
    // * This indicates whether the player *knows* the state of the Magic Spring (drained / not drained),
    //   not the state itself. For example, a Magic Spring may have been drained by another player, but the current
    //   player won't know that until they visit the Magic Spring.
    // * This describes the entire Magic Spring object on the Adventure Map, not a specific actionable tile
    //   of the object (Magic Springs normally have 2 actionable tiles).
    BitSet<4> magic_springs;
    // 1 bit per Corpse, indicating if the player has visited it.
    BitSet<4> corpses;
    // 1 bit per Lean To, indicating if the player has visited it.
    BitSet<4> lean_tos;
    // TODO: figure out what this is.
    std::array<std::uint8_t, 3> unknown3 {};
  };
}
