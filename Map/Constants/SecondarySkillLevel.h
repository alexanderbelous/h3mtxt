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
  // that secondary skill at all, but it nevertheless occupies a slot.
  //
  // * The hero won't be offered an opportunity to change the level of the secondary skill
  //   when gaining experience.
  // * If the hero visits a Scholar that grants the same secondary skill, this skill will added
  //   to the first free slot at Basic level. The slot that was originally occupied by the "hexed"
  //   skill (i.e. with the value outside [1; 3]) will contain junk after that.
  // * If the hero visits a Witch Hut / visits a Seer's Hut / triggers an Event / opens a Pandora's Box
  //   that grants the same secondary skill (at level N):
  //     * If level == 0, this skill (at level N) will be added to the first free slot.
  //       The original slot will contain junk after that.
  //     * Otherwise (if level > 3), it will have no effect (it is considered that the hero has already learned it).
  //
  // By saying "will contain junk after that" I mean that the hero screen will display some nonsense instead
  // of the original skill (likely "Basic First Aid"); clicking on the details will cause the game to crash.
  // TODO: check the behavior when getting the same secondary skill from University.
  template<SecondarySkillType T>
  struct SecondarySkillLevel;

  template<>
  struct SecondarySkillLevel<SecondarySkillType::Scouting>
  {
    // Decreases the scouting radius by 1 square (the new scouting radius = 4).
    static constexpr std::uint8_t k4Tiles = 0xFF;
    // Decreases the scouting radius by 2 squares (the new scouting radius = 3).
    static constexpr std::uint8_t k3Tiles = 0xFE;
    // Decreases the scouting radius by 3 squares (the new scouting radius = 2).
    static constexpr std::uint8_t k2Tiles = 0xFD;
    // Decreases the scouting radius by 4 squares (the new scouting radius = 1).
    static constexpr std::uint8_t k1Tile = 0xFC;
    // Reveals the entire map.
    static constexpr std::uint8_t kFullMap = 0xF9;
    static constexpr std::uint8_t kFullMap2 = 0xFB;
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
  struct SecondarySkillLevel<SecondarySkillType::Intelligence>
  {
    // Increases a hero's normal maximum spell points by 15%
    static constexpr std::uint8_t k15Percent = 0xFF;
    // Increases a hero's normal maximum spell points by 10%
    static constexpr std::uint8_t k10Percent = 0xFE;
    // Increases a hero's normal maximum spell points by 5%
    static constexpr std::uint8_t k5Percent = 0xFD;
    // Increases a hero's normal maximum spell points by 30%
    static constexpr std::uint8_t k30Percent = 0xFB;
    // Increases a hero's normal maximum spell points by 20%
    static constexpr std::uint8_t k20Percent = 0xFA;
    // Increases a hero's normal maximum spell points by 10%
    static constexpr std::uint8_t k10Percent1 = 0xF9;
    // Increases a hero's normal maximum spell points by 60%
    static constexpr std::uint8_t k60Percent = 0xEF;
    // Increases a hero's normal maximum spell points by 40%
    static constexpr std::uint8_t k40Percent = 0xE9;
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

  template<>
  struct SecondarySkillLevel<SecondarySkillType::Sorcery>
  {
    // Causes a hero's spells to inflict an additional 20% damage in combat.
    static constexpr std::uint8_t k20Percent = 0xFE;
    static constexpr std::uint8_t k20Percent2 = 0xF7;
    static constexpr std::uint8_t k20Percent3 = 0xF1;
    // Causes a hero's spells to inflict an additional 30% damage in combat.
    static constexpr std::uint8_t k30Percent = 0xFF;
    // Causes a hero's spells to inflict an additional 40% damage in combat.
    static constexpr std::uint8_t k40Percent = 0xF2;
    static constexpr std::uint8_t k40Percent2 = 0xED;
    // Causes a hero's spells to inflict an additional 50% damage in combat.
    static constexpr std::uint8_t k50Percent = 0xEE;
    // Causes a hero's spells to inflict an additional 60% damage in combat.
    static constexpr std::uint8_t k60Percent = 0xF3;
    static constexpr std::uint8_t k60Percent2 = 0xEF;
  };

  // TODO: add the rest.
}
