#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Constants/TownType.h>
#include <h3mtxt/Map/Coordinates.h>

#include <h3mtxt/SavedGame/TroopsSvg.h>

#include <array>
#include <cstdint>
#include <string>

namespace h3m
{
  // Information about a town stored in H3SVG.
  // Credits to RoseKavalier: instead of figuring out the meaning of every byte, I followed the already
  // reverse-engineered representation of the town in the process memory
  //   https://github.com/RoseKavalier/H3API/blob/master/include/h3api/H3Towns/H3Town.hpp
  // and it seems that they are very similar.
  struct TownSvg
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
    TroopsSvg garrison;
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
    // TODO: reverse-engineer
    std::array<std::uint8_t, 282> unknown3 {};
  };
}
