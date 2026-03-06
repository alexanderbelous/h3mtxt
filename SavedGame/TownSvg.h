#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

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
    std::array<std::uint8_t, 2> unknown1 {}; // unknown1[0] is probably Bool built_this_turn
    TownType type {};
    Coordinates coordinates;
    // X and Y coordinates of the tile where the boat will be generated when built via the town's
    // Shipyard, or {0xFF, 0xFF} if this town cannot build ships.
    std::uint8_t generated_boat_x {};
    std::uint8_t generated_boat_y {};
    TroopsSvg garrison;
    // TODO: reverse-engineer.
    // Apparently:
    //   unknown2[0] -> HeroType garrisoned_hero.
    //   unknown2[1] -> HeroType visiting_hero.
    //   unknown2[2] -> std::uint8_t mage_guild_level.
    //   unknown2[3] -> ReservedData<1> reserved.
    std::array<std::uint8_t, 4> unknown2 {};
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
