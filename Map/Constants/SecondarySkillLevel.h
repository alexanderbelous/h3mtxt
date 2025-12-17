#pragma once

#include <h3mtxt/Map/Constants/SecondarySkillType.h>

namespace h3m
{
  // Levels of secodary skills are expected to be within [1; 3]. However, Heroes3.exe
  // has well-defined behavior for some values outside of this range for some skills,
  // as shown by LC:
  //   https://www.youtube.com/watch?v=X_xVEXGGqbw
  //   https://docs.google.com/spreadsheets/d/1JwdFy51rODCJ_3WT8iVBRX7QeblD0BPK11qYH5jhkO0
  //
  // ===============================================================================
  //  ____      ____  _       _______     ____  _____  _____  ____  _____   ______
  // |_  _|    |_  _|/ \     |_   __ \   |_   \|_   _||_   _||_   \|_   _|.' ___  |
  //   \ \  /\  / / / _ \      | |__) |    |   \ | |    | |    |   \ | | / .'   \_|
  //    \ \/  \/ / / ___ \     |  __ /     | |\ \| |    | |    | |\ \| | | |   ____
  //     \  /\  /_/ /   \ \_  _| |  \ \_  _| |_\   |_  _| |_  _| |_\   |_\ `.___]  |
  //      \/  \/|____| |____||____| |___||_____|\____||_____||_____|\____|`._____.'
  //
  // This is outright hacking. These "hexed" skills rely on buffer over-read, which
  // just happens to work because Heroes3.exe doesn't perform bounds checking when
  // reading the "effect" of a secondary skill at the specified level.
  //
  // There is no guarantee whatsoever that such "hexed" secondary skills would work
  // as described below (or work at all) in any program other than the official
  // Heroes3.exe.
  //
  // Since the game was written in C++ and in C++ accessing elements outside of array
  // bounds is undefined behavior, the compiled binary (Heroes3.exe) was not required
  // to have any particular behavior for such "hexed" secondary skills - it's merely
  // a coincidence that they behave as described below.
  //
  // Hypothetically, if you were to recompile the source code of Heroes3.exe and try
  // playing a map that uses such "hexed" secondary skills, there would be no
  // guarantee whatsoever that they would work as described below. For example, the
  // compiler would be allowed to insert code that deletes all files on your computer.
  // ===============================================================================
  // --------------------------- Why and how this works ----------------------------
  // -------------------------------------------------------------------------------
  //
  // In Heroes3.exe the "effects" of secondary skills are stored at specific
  // memory addresses in the executable itself.
  // * Credits to BTB for reverse-engineering: see http://heroescommunity.com/viewthread.php3?TID=46202
  //                                           and http://btb2.free.fr/mods/h3/hacking.txt
  //
  // For each secondary skill Heroes3.exe stores 4 successive 32-bit values. These
  // values define, respectively, the effects of:
  //   x[0]: No skill
  //   x[1]: Basic
  //   x[2]: Advanced,
  //   x[3]: Expert
  //
  // For some secondary skills the effect is described by an integer; for others,
  // it is desribed by a floating-point number. Floating-point numbers are encoded
  // as described by the IEEE-754 standard.
  //
  // The addresses in Heroes3.exe for different secondary skills:
  //   Luck        23E998      Offense     23E9F8      Learning        23EA58
  //   Leadership  23E9A8      Armorer     23EA08      Logistics       23EA68
  //   Necromancy  23E9B8      Estates     23EA18      Sorcery         23EA78
  //   Mysticism   23E9C8      Eagle Eye   23EA28      Intelligence    23EA88
  //   Scouting    23E9D8      Diplomacy   23EA38      First Aid       23EA98
  //   Archery     23E9E8      Resistance  23EA48      Artillery       23B810
  //
  // These addresses point to the .rdata section of Heroes3.exe, which represents
  // statically-allocated constant variables. This section is loaded into the
  // process memory when Heroes3.exe starts.
  //
  // This is equivalent to the following data structure in C++ (ignoring Artillery):
  //
  // struct SecondarySkillEffects
  // {
  //   std::uint32_t luck[4]         = {0,    1,    2,    3};  // 23E998
  //   std::uint32_t leadership[4]   = {0,    1,    2,    3};  // 23E9A8
  //   float         necromancy[4]   = {0,  0.1,  0.2,  0.3};  // 23E9B8
  //   std::uint32_t mysticism[4]    = {0,    1,    2,    3};  // 23E9C8
  //   std::uint32_t scouting[4]     = {5,    6,    7,    8};
  //   float         archery[4]      = {0,  0.1, 0.25,  0.5};
  //   float         offense[4]      = {0,  0.1,  0.2,  0.3};
  //   float         armorer[4]      = {0, 0.05,  0.1, 0.15};
  //   std::uint32_t estates[4]      = {0,  125,  250,  500};
  //   float         eagle_eye[4]    = {0,  0.4,  0.5,  0.6};
  //   float         diplomacy[4]    = {0,  0.2,  0.4,  0.6};
  //   float         resistance[4]   = {0, 0.05,  0.1,  0.2};
  //   float         learning[4]     = {0, 0.05,  0.1, 0.15};
  //   float         logistics[4]    = {0,  0.1,  0.2,  0.3};
  //   float         sorcery[4]      = {0, 0.05,  0.1, 0.15};
  //   float         intelligence[4] = {0, 0.25,  0.5,  1.0};
  //   float         first_aid[4]    = {0,  1.0,  2.0,  3.0};
  // };
  //
  // Note that
  //   offsetof(SecondarySkillEffects, luck)       == 0,
  //   offsetof(SecondarySkillEffects, leadership) == 16,
  //   offsetof(SecondarySkillEffects, necromancy) == 32,
  //   offsetof(SecondarySkillEffects, mysticism)  == 48,
  //   ...
  //
  // Heroes3.exe is a Win32 program, and in Win32 it's guaranteed that
  //   sizeof(std::uint32_t) == 4
  //   sizeof(float) == 4
  //   alignof(std::uint32_t) == 4
  //   alignof(float) == 4
  // so leadership[0] is guaranteed to be allocated immediately after luck[3].
  //
  // Heroes3.exe treats the secondary skill level in .h3m as a signed integer:
  // for example, 0xFF is interpreted as -1, not as 255.
  //
  // Now comes the undefined behavior (UB) part:
  // 1) In C++ writing the following is undefined behavior:
  //   SecondarySkillEffects table;
  //   std::uint32_t leadership_ff = leadership[-1];
  // 2) In Heroes3.exe, however, the program doesn't check if the element index
  //    is within [0; 3], it simply reads the value at the computed address. Since
  //    we have already established that there are no bytes between luck[3] and leadership[0],
  //    * leadership[-1] happens to return the value stored at luck[3], which is equal to 3
  //    * leadership[-2] happens to return the value stored at luck[2], which is equal to 2
  //    * leadership[-3] happens to return the value stored at luck[1], which is equal to 1
  //    * leadership[-4] happens to return the value stored at luck[0], which is equal to 0
  //
  // Levels [-4; -1] aren't very useful for Leadership, because the resulting Morale bonuses
  // are the same that you can get from normal levels [0; 3].
  //
  // However, for other secondary skills we can get effects that cannot be achieved
  // from levels [0; 3]:
  // * resistance[-1] happens to return the value stored at diplomacy[3], which is equal to 0.6.
  //   This increases Magic resistance of all creatures in the army by 60%.
  //   No hero except Torgrim can achieve this level of Magic resistance, even if they
  //   have Expert Resistance and equip all resistance-increasing artifacts (i.e.
  //   Garniture of Interference, Surcoat of Counterpoise and Boots of Polarity).
  // * mysticism[-1] happens to return the value stored at necromancy[3], which is reprsented by
  //   the bytes {0x9A, 0x99, 0x99, 0x3E}. When interpreted as a little-endian 32-bit unsigned
  //   integer, its value is 1'050'253'722, i.e. the hero will regenerate more than 1 million
  //   spell points per day. In practice, it means that the hero will replenish all their spell
  //   points every day.
  //
  // There is a limitation, though: while the "effect" can be read safely for any level
  // within [-128; -1] (as long as the resulting address refers to bytes within .rdata),
  // we need to remember that the level is also used in a few other places:
  // * It defines the appropriate icon for this secondary skill on the Hero screen.
  // * It defines the text label for this secondary skill on the Hero screen.
  // * It defines the description for this secondary skill on the Hero screen.
  // Because of this, "hexed" secondary skills are usually displayed as nonsense on the Hero screen:
  // * e.g., Leadership{-1} is displayed as "Cancel Leadership"
  //                        with the icon of Advanced Navigation
  //                        and the description of Expert Navigation.
  // Even worse, Heroes3.exe may crash for some "hexed" secondary skills if it fails to read those values
  // (icon, name and description).
  //
  // Specializations of the template SecondarySkillLevel below only provide levels
  // that don't cause errors when used in Heroes3.exe.
  // ===============================================================================
  //
  // Note that 0 is a valid value for all secondary skills. It is equivalent to not having
  // that secondary skill at all, but it nevertheless occupies a slot.
  //
  // * The hero won't be offered an opportunity to change the level of the secondary skill
  //   when gaining experience.
  // * If the hero visits a Scholar or a University that grants the same secondary skill, this skill will added
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

  // During combat morale will always be clamped to [-3; 3], i.e. even with
  // a "hexed" secondary skill you cannot increase the odds of getting Good/Bad morale.
  // However, such "hexed" skills can still be useful if you want to ensure that a hero
  // will have +3 morale even if it's decreased due to some factors (e.g., troops of 7
  // different alignments decrease morale by 5; presence of Undead decreases it by 1;
  // Bone/Ghost Dragons in the opposing army decrease it by 1, etc).
  template<>
  struct SecondarySkillLevel<SecondarySkillType::Leadership>
  {
    // Increases your hero's troops' morale by 101,058,054.
    static constexpr std::uint8_t k101058054 = 0xF2;
    // Increases your hero's troops' morale by 100,860,675.
    static constexpr std::uint8_t k100860675 = 0xEC;
    // Increases your hero's troops' morale by 33,554,432.
    // This is commented out because it causes a crash when right-clicking on the skill.
    //static constexpr std::uint8_t k33554432 = 0x80;
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

  // During combat luck will always be clamped to [-3; 3], i.e. even with
  // a "hexed" secondary skill you cannot increase the odds of getting Good/Bad luck.
  // However, such "hexed" skills can still be useful if you want to ensure that a hero
  // will have +3 luck even if it's decreased due to some factors.
  template<>
  struct SecondarySkillLevel<SecondarySkillType::Luck>
  {
    // Increases your hero's troops' luck by 101,058,054.
    // "Defense Luck"
    static constexpr std::uint8_t k101058054 = 0xF6;
    // Increases your hero's troops' luck by 100,860,675.
    // "Dark blue Luck"
    static constexpr std::uint8_t k100860675 = 0xF0;
    // Increases your hero's troops' luck by 1028.
    // "Create strong guardians Luck"
    static constexpr std::uint8_t k1028 = 0x98;
    // Increases your hero's troops' luck by 771.
    // "const_strong_monsters, Luck"
    static constexpr std::uint8_t k771 = 0x97;
    // Increases your hero's troops' luck by 33,686,018.
    // "Include a random amount of water Luck"
    static constexpr std::uint8_t k33686018 = 0x90;
    // Increases your hero's troops' luck by 1280.
    // This is commented out because it causes a crash when right-clicking on the skill.
    //static constexpr std::uint8_t k1280 = 0x80;
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
    static constexpr std::uint8_t k50Percent2 = 0xDF;
    // Causes a hero's spells to inflict an additional 60% damage in combat.
    static constexpr std::uint8_t k60Percent = 0xF3;
    static constexpr std::uint8_t k60Percent2 = 0xEF;
  };

  // TODO: apparently, there is a way to learn level 5 spells via hexed Eagle Eye:
  // https://www.reddit.com/r/heroes3/comments/1iv6kkh/eagle_eye_level_5_spells_catching_in_sod_not_hota/
}
