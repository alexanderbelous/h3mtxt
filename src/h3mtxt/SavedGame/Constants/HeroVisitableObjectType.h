#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

namespace h3svg
{
  // Enum type used to index the elements of h3svg::Hero::visited_objects.
  enum class HeroVisitableObjectType : std::uint8_t
  {
    LearningStones           = 0,
    MarlettoTowers           = 1,
    GardensOfRevelation      = 2,
    MercenaryCamps           = 3,
    StarAxes                 = 4,
    TreesOfKnowledge         = 5,
    LibrariesOfEnlightenment = 6,
    Arenas                   = 7,
    SchoolsOfMagic           = 8,
    SchoolsOfWar             = 9
  };
}
