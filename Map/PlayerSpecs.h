#pragma once

#include <h3mparser/Map/Constants/HeroType.h>
#include <h3mparser/Map/Constants/PlayerBehavior.h>
#include <h3mparser/Map/Constants/TownType.h>
#include <h3mparser/Map/Base.h>

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace h3m
{

// Stores allowed alignments for a player.
//
// This is simply a wrapper around BitSet<2>.
class AllowedAlignments
{
public:
  // Constructs a bitset with all town types disabled.
  constexpr AllowedAlignments() noexcept = default;

  constexpr explicit AllowedAlignments(const BitSet<2>& town_types) noexcept;

  // Checks if the given town type is allowed.
  // \param town - town type to check.
  // \return true if the given town type is allowed, false otherwise.
  // \throw std::out_of_range if int(town) >= 16.
  constexpr bool isAllowed(TownType town) const;

  // Enable/disable the specified town type.
  // \param town - town type to set.
  // \throw std::out_of_range if int(town) >= 16.
  constexpr void set(TownType town, bool is_allowed);

  BitSet<2> town_types {};
};

constexpr AllowedAlignments::AllowedAlignments(const BitSet<2>& town_types) noexcept:
  town_types(town_types)
{}

constexpr bool AllowedAlignments::isAllowed(TownType town) const
{
  return town_types.at(static_cast<std::underlying_type_t<TownType>>(town));
}

constexpr void AllowedAlignments::set(TownType town, bool is_allowed)
{
  town_types.set(static_cast<std::underlying_type_t<TownType>>(town), is_allowed);
}

// Information about the player's main town.
struct MainTown
{
  // True if "Generate hero at main town" is set, false otherwise.
  Bool generate_hero {};
  // Type of the player's main town.
  // 0xFF is a special value that means Random.
  TownType town_type;
  // X-coordinate of the main town.
  std::uint8_t x;
  // Y-coordinate of the main town.
  std::uint8_t y;
  // Z-coordinate of the main town.
  std::uint8_t z;
};

// Information about the player's starting hero.
struct StartingHero
{
  Bool is_random {};
  // 0xFF if random.
  HeroType type {};
  // TODO: probably should be an enum; 0xFF for default.
  std::uint8_t face {};
  // Hero's name. Empty string means that the default name is used.
  std::string name;
};

struct AdditionalPlayerInfo
{
  struct HeroInfo
  {
    HeroType type;
    // If empty, the default name is implied.
    std::string name;
  };

  std::uint8_t num_placeholder_heroes {};
  // Includes Visiting heroes and regular hero objects (not random);
  // includes placeholder heroes configured as "Specific hero" rather than "Power rating";
  // type/name match the object's.
  std::vector<HeroInfo> heroes;
};

struct PlayerSpecs
{
  Bool can_be_human {};
  Bool can_be_computer {};
  PlayerBehavior behavior {};
  Bool customized_alignments {};
  AllowedAlignments allowed_alignments;
  // True if the player's alignment is random, false otherwise.
  // If true, implies that all town types are enabled.
  Bool random_town {};
  // Info about the main town, std::nullopt if the player doesn't have a main town.
  std::optional<MainTown> main_town;
  StartingHero starting_hero;
  // TODO: AdditionalPlayerInfo seems to be missing if !can_be_human && !can_be_computer.
  // This is not well-documented; the actual condition might be more complicated.
  AdditionalPlayerInfo additional_info;
};

}
