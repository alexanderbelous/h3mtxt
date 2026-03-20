#pragma once

#include <cstdint>

namespace h3m
{
  enum class RewardType : std::uint8_t
  {
    None = 0,
    Experience = 1,
    SpellPoints = 2,
    Morale = 3,
    Luck = 4,
    Resource = 5,
    PrimarySkill = 6,
    SecondarySkill = 7,
    Artifact = 8,
    Spell = 9,
    Creature = 10,
    // FYI: there seem to be no "hidden" types here. If you try using values outside [0; 10],
    // the game will treat them the same way as None, but the Map Editor will crash while
    // trying to open the map.
    // Note that h3mtxt itself does not support values outside [0; 10]: h3m::Reward cannot represent
    // such rewards, so attempting to read or write maps with such rewards will lead to an error.
  };

  inline constexpr std::uint8_t kNumRewardTypes = 11;
}
