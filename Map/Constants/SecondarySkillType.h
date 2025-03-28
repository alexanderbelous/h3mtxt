#pragma once

#include <cstdint>

namespace h3m
{
  enum class SecondarySkillType : std::uint8_t
  {
    Pathfinding,    // 00
    Archery,        // 01
    Logistics,      // 02
    Scouting,       // 03
    Diplomacy,      // 04
    Navigation,     // 05
    Leadership,     // 06
    Wisdom,         // 07
    Mysticism,      // 08
    Luck,           // 09
    Ballistics,     // 0A
    EagleEye,       // 0B
    Necromancy,     // 0C
    Estates,        // 0D
    FireMagic,      // 0E
    AirMagic,       // 0F
    WaterMagic,     // 10
    EarthMagic,     // 11
    Scholar,        // 12
    Tactics,        // 13
    Artillery,      // 14
    Learning,       // 15
    Offense,        // 16
    Armorer,        // 17
    Intelligence,   // 18
    Sorcery,        // 19
    Resistance,     // 1A
    FirstAid,       // 1B

    // SecondarySkillType{35} at Basic level is equivalent to nwcnebuchadnezzar cheat
    // (1,000,000 move points). It's somewhat "buggy", though: if a hero with such skill
    // gets Wisdom later, the slot corresponding to SecondarySkillType{35} will start
    // displaying "Basic First Aid" with Widsom logo; clicking on that slot will crash the game.
    // At Advanced/Expert level it is already displayed as "Basic First Aid" with the above-mentioned behavior.
    // This is used in the map "Awakening from Abyss" by LC.
  };
}
