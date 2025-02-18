#pragma once

#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>

namespace h3m
{
  // HeroesBitmask in which all heroes are enabled.
  inline constexpr HeroesBitmask kAllHeroesAvailability =
    []() consteval
    {
      HeroesBitmask result;
      for (std::uint8_t hero_idx = 0; hero_idx < kNumHeroes; ++hero_idx)
      {
        result.set(static_cast<HeroType>(hero_idx), true);
      }
      return result;
    }();

  // HeroesBitmask matching the default one in the Editor -
  // all heroes are enabled except special campaign heroes (e.g., Catherine, Gelu, Xeron)
  // and Lord Haart (Estates specialist). Sir Mullich is enabled.
  inline constexpr HeroesBitmask kDefaultHeroesAvailability =
    []() consteval
    {
      constexpr std::uint8_t kSpecialCampaignHeroFirst = static_cast<std::uint8_t>(HeroType::ADRIENNE);
      HeroesBitmask result = kAllHeroesAvailability;
      // Disable special campaign heroes;
      for (std::uint8_t hero_idx = kSpecialCampaignHeroFirst; hero_idx < kNumHeroes; ++hero_idx)
      {
        result.set(static_cast<HeroType>(hero_idx), false);
      }
      result.set(HeroType::LORD_HAART, false);
      return result;
    }();
}
