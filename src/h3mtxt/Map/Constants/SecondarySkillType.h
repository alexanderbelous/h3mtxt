#pragma once

#include <cstdint>

namespace h3m
{
  enum class SecondarySkillType : std::uint8_t
  {
    Pathfinding  = 0,  // 0x00
    Archery      = 1,  // 0x01
    Logistics    = 2,  // 0x02
    Scouting     = 3,  // 0x03
    Diplomacy    = 4,  // 0x04
    Navigation   = 5,  // 0x05
    Leadership   = 6,  // 0x06
    Wisdom       = 7,  // 0x07
    Mysticism    = 8,  // 0x08
    Luck         = 9,  // 0x09
    Ballistics   = 10, // 0x0A
    EagleEye     = 11, // 0x0B
    Necromancy   = 12, // 0x0C
    Estates      = 13, // 0x0D
    FireMagic    = 14, // 0x0E
    AirMagic     = 15, // 0x0F
    WaterMagic   = 16, // 0x10
    EarthMagic   = 17, // 0x11
    Scholar      = 18, // 0x12
    Tactics      = 19, // 0x13
    Artillery    = 20, // 0x14
    Learning     = 21, // 0x15
    Offense      = 22, // 0x16
    Armorer      = 23, // 0x17
    Intelligence = 24, // 0x18
    Sorcery      = 25, // 0x19
    Resistance   = 26, // 0x1A
    FirstAid     = 27  // 0x1B

    // SecondarySkillType{35} at Basic level is equivalent to nwcnebuchadnezzar cheat
    // (1,000,000 move points). It's somewhat "buggy", though: if a hero with such skill
    // gets Wisdom later, the slot corresponding to SecondarySkillType{35} will start
    // displaying "Basic First Aid" with Widsom logo; clicking on that slot will crash the game.
    // At Advanced/Expert level it is already displayed as "Basic First Aid" with the above-mentioned behavior.
    // This is used in the map "Awakening from Abyss" by LC.
  };
}
