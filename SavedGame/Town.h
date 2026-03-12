#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Constants/TownType.h>
#include <h3mtxt/Map/Coordinates.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/SavedGame/Constants/TownBuildingTypeH3SVG.h>
#include <h3mtxt/SavedGame/Troops.h>

#include <array>
#include <cstdint>
#include <string>

namespace h3svg
{
  // Information about a town stored in H3SVG.
  // Credits to RoseKavalier: instead of figuring out the meaning of every byte, I followed the already
  // reverse-engineered representation of the town in the process memory
  //   https://github.com/RoseKavalier/H3API/blob/master/include/h3api/H3Towns/H3Town.hpp
  // and it seems that they are very similar.
  struct Town
  {
    // 0-based index of this town in SavedGame::towns.
    std::uint8_t id {};
    PlayerColor owner {};
    // 1 if a building has already been built in this town this turn, 0 otherwise.
    Bool built_this_turn {};
    std::uint8_t unknown1 {};
    TownType type {};
    Coordinates coordinates;
    // X and Y coordinates of the tile where the boat will be generated when built via the town's
    // Shipyard, or {0xFF, 0xFF} if this town cannot build ships.
    std::uint8_t generated_boat_x {};
    std::uint8_t generated_boat_y {};
    Troops garrison;
    // HeroType of the garrisoned hero or 0xFF if there is none.
    HeroType garrisoned_hero {};
    // HeroType of the visiting hero or 0xFF if there is none.
    HeroType visiting_hero {};
    // The current level of the Mage Guild (within [0; 5]).
    std::uint8_t mage_guild_level {};
    // Seems to always be 0.
    std::uint8_t unknown2 {};
    std::string name;
    // The number of non-upgraded creatures available for hire for each creature level.
    // The values are 0 for creatures whose dwellings are upgraded.
    std::array<std::uint16_t, 7> recruits_nonupgraded {};
    // The number of upgraded creatures available for hire for each creature level.
    std::array<std::uint16_t, 7> recruits_upgraded {};
    // The number of external dwellings for each creature level.
    std::array<std::uint32_t, 7> num_external_dwellings {};
    // Duplicates num_external_dwellings for some reason.
    // TODO: check what modifying either field does.
    std::array<std::uint32_t, 7> num_external_dwellings2 {};
    // TODO: figure out what this is.
    std::array<std::uint8_t, 13> unknown3 {};
    EnumBitmask<TownBuildingTypeH3SVG, 6> built;
    ReservedData<2> reserved1;
    EnumBitmask<TownBuildingTypeH3SVG, 6> can_be_built;
    ReservedData<2> reserved2;
    // 6 spells for each level of the Mage Guild.
    // Note that the values for nonexistent slots likely contain junk bytes (e.g., spells[1][5] is not even
    // guarantred to be a valid SpellType).
    std::array<std::array<SpellType32, 6>, 5> spells {};
    // 1 bit per SpellType, indicating whether it is banned (1 - banned, 0 - not banned).
    SpellsBitmask banned_spells;
    // TODO: reverse-engineer
    // unknown3[61] & 1 seems to indicate if the Mana Vortex has NOT been used this week
    std::array<std::uint8_t, 68> unknown4 {};
  };
}
