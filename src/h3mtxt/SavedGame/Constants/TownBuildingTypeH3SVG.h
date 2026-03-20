#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3svg
{
  // Enum for bitmasks used in h3svg::Town.
  //
  // Note that the values differ from the ones in h3m::TownBuildingType.
  enum class TownBuildingTypeH3SVG : std::uint8_t
  {
    MageGuild1   = 0,
    MageGuild2   = 1,
    MageGuild3   = 2,
    MageGuild4   = 3,
    MageGuild5   = 4,
    Tavern       = 5,
    Wharf        = 6,
    Fort         = 7,

    Citadel      = 8,
    Castle       = 9,
    VillageHall  = 10,
    TownHall     = 11,
    CityHall     = 12,
    Capitol      = 13,
    Market       = 14,
    ResourceSilo = 15,

    Blacksmith   = 16,
    Special17    = 17,
    Horde1       = 18,
    Horde1U      = 19,
    Wharf2       = 20,
    Special21    = 21,
    Special22    = 22,
    Special23    = 23,

    Horde2       = 24,
    Horde2U      = 25,
    Grail        = 26,
    Decor27      = 27,
    Decor28      = 28,
    Decor29      = 29,
    Dwelling1    = 30,
    Dwelling2    = 31,

    Dwelling3    = 32,
    Dwelling4    = 33,
    Dwelling5    = 34,
    Dwelling6    = 35,
    Dwelling7    = 36,
    Dwelling1U   = 37,
    Dwelling2U   = 38,
    Dwelling3U   = 39,

    Dwelling4U   = 40,
    Dwelling5U   = 41,
    Dwelling6U   = 42,
    Dwelling7U   = 43,
  };
}