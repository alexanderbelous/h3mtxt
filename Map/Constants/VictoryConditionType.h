#pragma once

#include <cstdint>

namespace h3m
{

enum class VictoryConditionType : std::uint8_t
{
  AcquireArtifact = 0,
  AccumulateCreatures = 1,
  AccumulateResources = 2,
  UpgradeTown = 3,
  BuildGrail = 4,
  DefeatHero = 5,
  CaptureTown = 6,
  DefeatMonster = 7,
  FlagDwellings = 8,
  FlagMines = 9,
  TransportArtifact = 10,
  // Undocumented types
  // (credits to LC: https://www.reddit.com/r/heroes3/comments/1iuna7q/hidden_conditions_of_victory_have_been_found/ ).
  // The Map Editor doesn't support them, but the game does.
  DefeatAllMonsters = 11,
  SurviveBeyondATimeLimit = 12,
  //
  Normal = 0xFF,
};

}
