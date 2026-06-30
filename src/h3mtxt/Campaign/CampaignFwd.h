#pragma once

// Forward declarations for the Campaign library.

#include <h3mtxt/Map/MapFwd.h>

#include <cstdint>

namespace h3m
{
  enum class CampaignFormat : std::uint32_t;

  enum class CampaignId : std::uint8_t;

  enum class CampaignMusic : std::uint8_t;

  enum class CampaignVideo : std::uint8_t;

  enum class CrossoverFeature : std::uint8_t;

  enum class StartingBonusType : std::uint8_t;

  enum class StartingOptionsType : std::uint8_t;

  // Bitmask storing a bit for each creature type.
  //
  // There are 150 creature types in Shadow of Death (the last 5 of them are war machines and arrow towers),
  // but this bitmask stores 152 bits.
  //
  // This is only used in CrossoverOptions.
  using CreaturesBitmask = EnumBitmask<CreatureType, 19>;

  using CrossoverFeaturesBitmask = EnumBitmask<CrossoverFeature, 1>;

  struct Campaign;

  struct CampaignHeader;

  struct CampaignScenario;

  struct CrossoverOptions;

  struct CutScene;

  struct HeroCrossoverOption;

  struct StartingBonus;

  template<StartingBonusType>
  struct StartingBonusDetails;

  struct StartingHeroOption;

  struct StartingOptions;

  template<StartingOptionsType>
  struct StartingOptionsDetails;
}
