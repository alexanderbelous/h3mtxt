#pragma once

#include <h3mparser/BitSet.h>
#include <h3mparser/Constants/HeroType.h>
#include <h3mparser/LossCondition.h>
#include <h3mparser/VictoryCondition.h>

#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

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
  // TODO: add heroes.
};

}
