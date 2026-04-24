#pragma once

#include <cstdint>

namespace h3m
{
  // Represents the absolute or relative values of the hero's primary skills.
  //
  // This is used in HeroSettings, hero objects on the adventure map,
  // Events on the adventure map, Pandora's Boxes, and quests.
  //
  // The game always interprets these as signed integers; in the Map Editor
  // there are only 2 places where they are (incorrectly) displayed as unsigned integers:
  // HeroSettings and hero objects on the adventure map.
  struct PrimarySkills
  {
    constexpr bool operator==(const PrimarySkills&) const noexcept = default;

    std::int8_t attack = 0;
    std::int8_t defense = 0;
    std::int8_t spell_power = 0;
    std::int8_t knowledge = 0;
  };
}
