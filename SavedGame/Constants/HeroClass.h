#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3svg
{
  enum class HeroClass : std::uint8_t
  {
    Knight       = 0,
    Cleric       = 1,
    Ranger       = 2,
    Druid        = 3,
    Alchemist    = 4,
    Wizard       = 5,
    Demoniac     = 6,
    Heretic      = 7,
    DeathKnight  = 8,
    Necromancer  = 9,
    Overlord     = 10,
    Warlock      = 11,
    Barbarian    = 12,
    BattleMage   = 13,
    Beastmaster  = 14,
    Witch        = 15,
    Planeswalker = 16,
    Elementalist = 17
  };
}
