#pragma once

#include <h3mparser/Map/BitSet.h>
#include <h3mparser/Map/Constants/HeroType.h>
#include <h3mparser/Map/HeroSettings.h>
#include <h3mparser/Map/LossCondition.h>
#include <h3mparser/Map/VictoryCondition.h>

#include <array>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

#include <map>

namespace h3m
{

struct TeamsInfo
{
  std::uint8_t num_teams {};
  // Each value should be < num_teams.
  std::array<std::uint8_t, 8> team_for_player {};
};

class HeroesAvailability
{
public:
  constexpr HeroesAvailability() noexcept = default;

  constexpr explicit HeroesAvailability(const BitSet<20>& data) noexcept:
    data(data)
  {}

  constexpr bool operator[](HeroType hero) const
  {
    return data.at(static_cast<std::size_t>(hero));
  }

  constexpr void set(HeroType hero, bool is_available)
  {
    data.set(static_cast<std::size_t>(hero), is_available);
  }

  BitSet<20> data;
};

struct Rumor
{
  std::string name;
  std::string description;
};

// Stores settings for all heroes.
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
    std::uint8_t face {};
    // Hero's name, or an empty string if the default name should be used instead.
    std::string name;
    // 1-byte bitset indicating which players can hire this hero.
    BitSet<1> can_hire;
  };

  VictoryCondition victory_condition {};
  LossCondition loss_condition {};
  // Details about the teams, std::nullopt if teams are disabled.
  std::optional<TeamsInfo> teams;
  HeroesAvailability heroes_availability;
  std::vector<HeroType> placeholder_heroes;
  std::vector<CustomHero> custom_heroes;
  // Must be all 0s; kept here to ensure compatibility.
  std::array<std::uint8_t, 31> reserved;
  // TODO: add a wrapper class
  BitSet<18> artifacts_nonavailability;
  // TODO: add a wrapper class
  BitSet<9> spells_nonavailability;
  // TODO: add a wrapper class
  BitSet<4> skills_nonavailability;
  std::vector<Rumor> rumors;
  HeroesSettings heroes_settings {};
};

}
