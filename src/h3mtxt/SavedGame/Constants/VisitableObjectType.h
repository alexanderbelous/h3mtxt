#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3svg
{
  // Enum type used to index the elements of h3svg::SavedGame::visited_objects.
  enum class VisitableObjectType : std::uint8_t
  {
    Buoy                     =  0,
    SwanPond                 =  1,
    FaerieRing               =  2,
    FountainOfFortune        =  3,
    GardenOfRevelation       =  4,
    LearningStone            =  5,
    LibraryOfEnlightenment   =  6,
    MarlettoTower            =  7,
    MercenaryCamp            =  8,
    SchoolOfMagic            =  9,
    SchoolOfWar              = 10,
    StarAxis                 = 11,
    WitchHut                 = 12,
    FountainOfYouth          = 13,
    HillFort                 = 14,
    MagicSpring              = 15,
    Mermaids                 = 16,
    RallyFlag                = 17,
    TreeOfKnowledge          = 18,
    ShrineOfMagicIncantation = 19,  // Level 1 spell
    ShrineOfMagicGesture     = 20,  // Level 2 spell
    ShrineOfMagicThought     = 21,  // Level 3 spell
    IdolOfFortune            = 22,
    Temple                   = 23,
    University               = 24,
    MagicWell                = 25,
    Oasis                    = 26,
    WateringHole             = 27,
    AltarOfSacrifice         = 28
  };
}
