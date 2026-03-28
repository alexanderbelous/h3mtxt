#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

namespace h3svg
{
  // Flags used in h3svg::Hero.
  // Each enumerator is a 0-based index of the bit in the bitmask.
  enum class HeroFlag
  {
    MagicWell = 0,                // Visited Magic Well
    Stables = 1,                  // Visited Stables
    Buoy = 2,                     // Visited Buoy
    SwanPond = 3,                 // Visited Swan Pond
    IdolOfFortuneMorale = 4,      // Visited Idol of Fortune, getting +1 Morale
    FountainOfFortuneBadLuck = 5, // Visited Fountain of Fortune, getting -1 Luck.
    WateringHole = 6,             // Visited Watering Hole
    Oasis = 7,                    // Visited Oasis
    Temple = 8,                   // Visited Temple on days 1-6, getting +1 Morale
    Shipwreck = 9,                // Morale penalty from visiting a Shipwreck
    Crypt = 10,                   // Morale penalty from visting a Crypt
    DerelictShip = 11,            // Morale penalty from visiting a Derelict Ship
    Pyramid = 12,                 // Morale penalty from visiting a Pyramid
    FaeireRing = 13,              // Visited Faerie Ring
    FountainOfYouth = 14,         // Visited Fountain of Youth
    Mermaids = 15,                // Visited Mermaids
    RallyFlag = 16,               // Visited Rally Flag
    Tavern = 17,                  // Hero is in a Tavern
    Boat = 18,                    // Hero is on a Boat
                                  // Bit 19 is unknown / not used
    Sirens = 20,                  // Visited Sirens
    WarriorsTomb = 21,            // Morale penalty from visiting Warrior's Tomb
    LuckCheat = 22,               // Used Luck cheat
    MoraleCheat = 23,             // Used Morale cheat
    MovementCheat = 24,           // Used Movement cheat
    IdolOfFortuneLuck = 25,       // Visited Idol of Fortune, getting +1 Luck
    Temple2 = 26,                 // Visited Temple on day 7, getting +2 Morale
    FountainOfFortune1 = 27,      // Visited Fountain of Fortune, getting +1 Luck
    FountainOfFortune2 = 28,      // Visited Fountain of Fortune, getting +2 Luck
    FountainOfFortune3 = 29,      // Visited Fountain of Fortune, getting +3 Luck
                                  // Bits 30-31 are unknown / not used
  };
}
