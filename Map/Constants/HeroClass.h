#pragma once

#include <h3mtxt/Mao/MapFwd.h>

#include <cstdint>

namespace h3m
{
  // Not used directly in the Map library, but this enum represents the valid values for
  // ObjectTemplate::object_sublcass when ObjectTemplate::object_class is a hero.
  //
  // In the future I might add comments for object_subclass when printing JSON.
  //
  // It is used explicitly in H3SVG though.
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
