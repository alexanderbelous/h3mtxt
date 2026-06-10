#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3svg
{
  // Reuse some constants from H3M.
  using ::h3m::kNumResourceTypes;
  //using ::h3m::kMaxPlayers;
  //using ::h3m::kNumHeroes;

  // TODO: move to Map.
  inline constexpr std::uint8_t kNumSecondarySkills = 28;
  inline constexpr std::uint8_t kNumSpells = 70;
}
