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
  Normal = 0xFF,
};

}
