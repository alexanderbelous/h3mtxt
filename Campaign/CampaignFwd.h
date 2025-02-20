#pragma once

#include <cstdint>

namespace h3m
{
  enum class CampaignId : std::uint8_t;

  enum class StartingBonusType : std::uint8_t;

  enum class StartingOptionsType : std::uint8_t;

  struct Campaign;

  struct CampaignScenario;

  struct StartingBonus;

  template<StartingBonusType>
  struct StartingBonusDetails;

  struct StartingOptions;

  template<StartingOptionsType>
  struct StartingOptionsDetails;
}
