#pragma once

#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/HeroPortrait.h>
#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/Map/HeroSettings.h>
#include <h3mtxt/Map/LossCondition.h>
#include <h3mtxt/Map/VictoryCondition.h>

#include <array>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

#include <map>

namespace h3m
{

struct TeamsInfo
{
  std::uint8_t num_teams {};
  // This field is only read/written if num_teams != 0.
  // Each value should be < num_teams.
  std::array<std::uint8_t, 8> team_for_player {};
};

// TODO: move to a separate header file and consider using an inline constexpr variable instead.
// \return HeroesBitmask in which all heroes are enabled.
constexpr HeroesBitmask makeAllHeroesAvailability() noexcept
{
  HeroesBitmask result;
  for (std::uint8_t hero_idx = 0; hero_idx < kNumHeroes; ++hero_idx)
  {
    result.set(static_cast<HeroType>(hero_idx), true);
  }
  return result;
}

// \return HeroesBitmask matching the default one in the Editor -
//         all heroes are enabled except special campaign heroes (e.g., Catherine, Gelu, Xeron)
//         and Lord Haart (Estates specialist).
constexpr HeroesBitmask makeDefaultHeroesAvailability() noexcept
{
  constexpr std::uint8_t kSpecialCampaignHeroFirst = 145;
  HeroesBitmask result = makeAllHeroesAvailability();
  // Disable special campaign heroes;
  for (std::uint8_t hero_idx = kSpecialCampaignHeroFirst; hero_idx < kNumHeroes; ++hero_idx)
  {
    result.set(static_cast<HeroType>(hero_idx), false);
  }
  result.set(HeroType::LORD_HAART, false);
  return result;
}

struct Rumor
{
  std::string name;
  std::string description;
};

// Stores settings for all heroes.
//
// In .h3m these are stored like std::array<std::optional<HeroSettings>, kNumHeroes> -
// a boolean value is written first, indicating if this hero has non-default settings;
// HeroSettings is only written if this boolean value is true.
//
// However, generally only a few heroes have non-default settings in MapAdditionalInfo
// (they are more likely to be customized for heroes on the adventure map), so it would
// be memory-inefficient to explicitly store 156 values (whether as std::optional or as a pointer).
class HeroesSettings
{
public:
  HeroesSettings() = default;

  inline bool hasSettings(HeroType hero) const;

  inline HeroSettings& operator[](HeroType hero);

  inline const HeroSettings& operator[](HeroType hero) const;

  inline void erase(HeroType hero);

  inline const std::map<HeroType, HeroSettings>& settings() const noexcept;

private:
  std::map<HeroType, HeroSettings> settings_;
};

bool HeroesSettings::hasSettings(HeroType hero) const
{
  return settings_.find(hero) != settings_.end();
}

HeroSettings& HeroesSettings::operator[](HeroType hero)
{
  if (static_cast<std::underlying_type_t<HeroType>>(hero) >= kNumHeroes)
  {
    throw std::runtime_error("HeroesSettings::operator[]: invalid hero.");
  }
  return settings_[hero];
}

const HeroSettings& HeroesSettings::operator[](HeroType hero) const
{
  return settings_.at(hero);
}

void HeroesSettings::erase(HeroType hero)
{
  settings_.erase(hero);
}

const std::map<HeroType, HeroSettings>& HeroesSettings::settings() const noexcept
{
  return settings_;
}

struct MapAdditionalInfo
{
  struct CustomHero
  {
    HeroType type {};
    // 0xFF for default.
    HeroPortrait portrait = HeroPortrait::DEFAULT;
    // Hero's name, or an empty string if the default name should be used instead.
    std::string name;
    // Bitmask indicating which players can hire this hero.
    PlayersBitmask can_hire;
  };

  VictoryCondition victory_condition {};
  LossCondition loss_condition {};
  TeamsInfo teams;
  // TODO: rename to enabled_heroes.
  HeroesBitmask heroes_availability;
  std::vector<HeroType> placeholder_heroes;
  std::vector<CustomHero> custom_heroes;
  // Must be all 0s; kept here to ensure compatibility.
  ReservedData<31> reserved {};
  // TODO: rename to "disabled_artifacts".
  // TODO: check what happens if you disable the spell book or war machines.
  ArtifactsBitmask artifacts_nonavailability;
  // 1 bit per spell; 1 means disabled, 0 means enabled.
  SpellsBitmask disabled_spells;
  // 1 bit per secondary skill; 1 means disabled, 0 means enabled.
  SecondarySkillsBitmask disabled_skills;
  std::vector<Rumor> rumors;
  HeroesSettings heroes_settings {};
};

}
