#pragma once

#include <h3mtxt/Map/MapFwd.h>

#include <cstdint>

namespace h3m
{
  enum class CampaignId : std::uint8_t;

  enum class CampaignMusic : std::uint8_t;

  enum class CrossoverFeature : std::uint8_t;

  enum class StartingBonusType : std::uint8_t;

  enum class StartingOptionsType : std::uint8_t;

  struct Campaign;

  struct CampaignHeader;

  struct CampaignScenario;

  using CrossoverFeaturesBitmask = EnumBitmask<CrossoverFeature, 1>;

  struct CrossoverOptions;

  struct CutScene;

  struct StartingBonus;

  template<StartingBonusType>
  struct StartingBonusDetails;

  struct StartingOptions;

  template<StartingOptionsType>
  struct StartingOptionsDetails;
}
