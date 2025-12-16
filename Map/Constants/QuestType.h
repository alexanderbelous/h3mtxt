#pragma once

#include <cstdint>

namespace h3m
{
  enum class QuestType : std::uint8_t
  {
    None = 0,
    Level = 1,
    PrimarySkills = 2,
    DefeatHero = 3,
    DefeatMonster = 4,
    Artifacts = 5,
    Creatures = 6,
    Resources = 7,
    BeHero = 8,
    BePlayer = 9
    // FYI: there seem to be no "hidden" types here. If you try using values outside [0; 9],
    // the game will treat them the same way as None, but the Map Editor will crash while
    // trying to open the map.
    // Note that h3mtxt itself does not support values outside [0; 9]: h3m::Quest cannot represent
    // such quests, so attempting to read or write maps with such quests will lead to an error.
  };

  inline constexpr std::uint8_t kNumQuestTypes = 10;
}
