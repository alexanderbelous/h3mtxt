#pragma once

#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/Constants/HeroPortrait.h>
#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Constants/MapFormat.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/Map/HeroSettings.h>
#include <h3mtxt/Map/LossCondition.h>
#include <h3mtxt/Map/Teams.h>
#include <h3mtxt/Map/VictoryCondition.h>

#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace h3m
{
  struct CustomHero
  {
    constexpr bool operator==(const CustomHero&) const noexcept = default;

    HeroType type{};
    // 0xFF for default.
    HeroPortrait portrait = HeroPortrait::Default;
    // Hero's name, or an empty string if the default name should be used instead.
    std::string name;
    // Bitmask indicating which players can hire this hero.
    PlayersBitmask can_hire;
  };

  struct Rumor
  {
    constexpr bool operator==(const Rumor&) const noexcept = default;

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

    bool operator==(const HeroesSettings&) const = default;

  private:
    std::map<HeroType, HeroSettings> settings_;
  };

  struct MapAdditionalInfo
  {
    bool operator==(const MapAdditionalInfo&) const = default;

    // \return the number of meaningful bytes in MapAdditionalInfo::disabled_artifacts for @map_format.
    static constexpr std::uint8_t getDisabledArtifactsBitmaskLength(MapFormat map_format) noexcept;

    static constexpr bool supportsCustomHeroes(MapFormat map_format) noexcept;

    static constexpr bool supportsDisabledSpells(MapFormat map_format) noexcept;

    static constexpr bool supportsDisabledSkills(MapFormat map_format) noexcept;

    static constexpr bool supportsHeroesSettings(MapFormat map_format) noexcept;

    VictoryCondition victory_condition;
    LossCondition loss_condition;
    Teams teams;
    // 1 bit per hero:
    // * 0 if the hero is disabled (Map Specifications -> Heroes in the Map Editor) or already placed on the map.
    // * 1 otherwise.
    HeroesBitmask heroes_availability;
    std::vector<HeroType> placeholder_heroes;
    // Only meaningful for MapFormat::ShadowOfDeath.
    std::vector<CustomHero> custom_heroes;
    // Reserved data; 0s by default.
    ReservedData<31> reserved;
    // 1 bit per artifact; 1 means disabled, 0 means enabled.
    // Spell Book, War Machines and Grail are not affected by this bitmask: they are enabled by default
    // by the Map Editor, but you will be able to purchase them (or dig them out in case of Grail) even
    // if you disable them manually.
    ArtifactsBitmask disabled_artifacts;
    // 1 bit per spell; 1 means disabled, 0 means enabled.
    // Only meaningful for MapFormat::ShadowOfDeath.
    SpellsBitmask disabled_spells;
    // 1 bit per secondary skill; 1 means disabled, 0 means enabled.
    // Only meaningful for MapFormat::ShadowOfDeath.
    SecondarySkillsBitmask disabled_skills;
    std::vector<Rumor> rumors;
    // Only meaningful for MapFormat::ShadowOfDeath.
    HeroesSettings heroes_settings;
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

  constexpr std::uint8_t MapAdditionalInfo::getDisabledArtifactsBitmaskLength(MapFormat map_format) noexcept
  {
    switch (map_format)
    {
    case MapFormat::ShadowOfDeath:
      return ArtifactsBitmask::kNumBytes;
    case MapFormat::ArmageddonsBlade:
      return ArtifactsBitmask::kNumBytes - 1;
    // In RoE disabled_artifacts is not serialized at all, which is equivalent
    // to saying that it has 0 meaningful bytes.
    case MapFormat::RestorationOfErathia:
    default:
      return 0;
    }
  }

  constexpr bool MapAdditionalInfo::supportsCustomHeroes(MapFormat map_format) noexcept
  {
    return map_format == MapFormat::ShadowOfDeath;
  }

  constexpr bool MapAdditionalInfo::supportsDisabledSpells(MapFormat map_format) noexcept
  {
    return map_format == MapFormat::ShadowOfDeath;
  }

  constexpr bool MapAdditionalInfo::supportsDisabledSkills(MapFormat map_format) noexcept
  {
    return map_format == MapFormat::ShadowOfDeath;
  }

  constexpr bool MapAdditionalInfo::supportsHeroesSettings(MapFormat map_format) noexcept
  {
    return map_format == MapFormat::ShadowOfDeath;
  }
}
