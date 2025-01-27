#pragma once

#include <h3mtxt/Map/Constants/SecondarySkillType.h>

namespace h3m
{
  // Levels of secodary skills are normally within [1; 3]. However, the game has
  // well-defined behavior for some values outside of this range for some skills,
  // as shown by LC:
  //   https://www.youtube.com/watch?v=X_xVEXGGqbw
  //   https://docs.google.com/spreadsheets/d/1JwdFy51rODCJ_3WT8iVBRX7QeblD0BPK11qYH5jhkO0
  //
  // Note that 0 is a valid value for all secondary skills. It is equivalent to not having
  // that secondary skill at all, but it nevertheless occupies a slot and the hero won't be
  // offered to increase the level when gaining experience. However, if the hero visits a
  // Scholar/Witch Hut that grants the same secondary skill (Basic), this skill (Basic) will
  // be added to the first free slot. The slot that was originally occupied by the Level0 skill
  // will contain junk after that.
  //
  // For values > 3 the rules are interesting:
  // * The hero cannot change the level of that secondary skill when gaining experience.
  // * If you visit a Witch Hut that grants the same secondary skill, it will have no effect
  //   (it is considered that the hero has already learned it).
  // * If you visit a Scholar that grants the same secondary skill, this skill will added
  //   to the first free slot at Basic level. The slot that was originally occupied by the "hexed"
  //   skill (i.e. with the value > 3) will contain junk after that.
  template<SecondarySkillType T>
  struct SecondarySkillLevel;

  template<>
  struct SecondarySkillLevel<SecondarySkillType::Scouting>
  {
    // Allows your hero to see 4 squares further into the shroud. 
    static constexpr std::uint8_t k4Tiles = 0xFF;
    // Reveals the entire map.
    static constexpr std::uint8_t kFullMap = 0xF9;
  };

  template<>
  struct SecondarySkillLevel<SecondarySkillType::Wisdom>
  {
    // The hero will only be able to learn Level 1 spells.
    static constexpr std::uint8_t kMaxLevel1 = 0xFF;
    // The hero won't be able to learn any spells.
    static constexpr std::uint8_t kNoSpells = 0xFE;
  };

  template<>
  struct SecondarySkillLevel<SecondarySkillType::Mysticism>
  {
    // Regenerates all spell points per day (same as Wizard's Well).
    static constexpr std::uint8_t kFull = 0xFF;
    static constexpr std::uint8_t kFull2 = 0xFE;
    static constexpr std::uint8_t kFull3 = 0xFD;
    // The hero won't regenerate any spell points.
    static constexpr std::uint8_t kNoPoints = 0xFC;
    static constexpr std::uint8_t kNoPoints2 = 0xF8;
    static constexpr std::uint8_t kNoPoints3 = 0xF4;
  };

  template<>
  struct SecondarySkillLevel<SecondarySkillType::Ballistics>
  {
    static constexpr std::uint8_t k8Shots = 0xFF;
    static constexpr std::uint8_t k0Shots1 = 0xFD;
    static constexpr std::uint8_t k0Shots2 = 0xFC;
    static constexpr std::uint8_t k0Shots3 = 0xFB;
    static constexpr std::uint8_t k0Shots4 = 0xF9;
    static constexpr std::uint8_t k0Shots5 = 0xF8;
    static constexpr std::uint8_t k0Shots6 = 0xF7;
    static constexpr std::uint8_t kInstakill = 0xF6;
    static constexpr std::uint8_t kInstakill2 = 0xF1;
  };

  template<>
  struct SecondarySkillLevel<SecondarySkillType::Estates>
  {
    // The hero contributes 1,000,000,000 gold per day to your cause.
    static constexpr std::uint8_t kBillionPerDay = 0xFF;
  };

  template<>
  struct SecondarySkillLevel<SecondarySkillType::Offense>
  {
    // Increases all hand-to-hand damage inflicted by the hero's troops by 50%.
    static constexpr std::uint8_t k50Percent = 0xFF;
  };

  template<>
  struct SecondarySkillLevel<SecondarySkillType::Armorer>
  {
    // Reduces all damage inflicted against the hero's troops by 50%.
    static constexpr std::uint8_t k50Percent = 0xFB;
  };

  template<>
  struct SecondarySkillLevel<SecondarySkillType::Resistance>
  {
    // Endows a hero's troops with 60% magic resistance.
    static constexpr std::uint8_t k60Percent = 0xFF;
    static constexpr std::uint8_t k60Percent2 = 0xFB;
    // Endows a hero's troops with 40% magic resistance.
    static constexpr std::uint8_t k40Percent = 0xFE;
    static constexpr std::uint8_t k40Percent2 = 0xF9;
  };

  // TODO: add the rest.
}
