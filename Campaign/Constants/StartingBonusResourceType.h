#pragma once

#include <cstdint>

namespace h3m
{
  // Superset of ResourceType used in StartingBonusDetails<StartingBonusType::Resource>.
  //
  // When Resource is chosen as a starting bonus, the campaign supports 2 values in addition
  // to the enumerators defined in ResourceType. As such, ResourceType can be safely converted
  // to StartingBonusResourceType, but not the other way around.
  enum class StartingBonusResourceType : std::uint8_t
  {
    Wood = 0,
    Mercury = 1,
    Ore = 2,
    Sulfur = 3,
    Crystal = 4,
    Gems = 5,
    Gold = 6,
    WoodOre = 0xFD,
    MercurySulfurCrystalGems = 0xFE
  };
}
