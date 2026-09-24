#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/SecondarySkillType.h>

#include <array>

namespace h3svg
{
  struct University
  {
    constexpr bool operator==(const University&) const noexcept = default;

    // The number of secondary skills offered in a University.
    static constexpr std::size_t kNumSkills = 4;    

    // FYI: the game crashes at start if there's a University on the Adventure Map but fewer than 4 skills
    // are enabled. There doesn't seem to be any stable way to make some slot empty: 0xFFFFFFFF is not equivalent
    // to None. However, the game correctly handles duplicate skills (which are never offered in normal gameplay).
    std::array<SecondarySkillType32, kNumSkills> skills {};
  };
}
