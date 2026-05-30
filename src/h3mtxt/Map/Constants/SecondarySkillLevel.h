#pragma once

#include <h3mtxt/Map/Constants/SecondarySkillType.h>

#include <cstdint>

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
  //   std::uint32_t mysticism[4]    = {1,    2,    3,    4};  // 23E9C8
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
  //   const SecondarySkillEffects table;
  //   std::uint32_t leadership_ff = table.leadership[-1];
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
  //   integer, its value is 1'050'253'722, i.e. the hero will regenerate more than 1 billion
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

  // Changes the hero's scouting radius (the default scouting radius is 5).
  template<>
  struct SecondarySkillLevel<SecondarySkillType::Scouting>
  {
    // | Level (decimal)                             | Level (hex) | Effect        | Source        |
    // | ------------------------------------------- | ----------- | ------------- | ------------- |
    static constexpr std::int8_t k4Tiles   = -1;  // | 0xFF        | 4             | mysticism[3]  |
    static constexpr std::int8_t k3Tiles   = -2;  // | 0xFE        | 3             | mysticism[2]  |
    static constexpr std::int8_t k2Tiles   = -3;  // | 0xFD        | 2             | mysticism[1]  |
    static constexpr std::int8_t k1Tile    = -4;  // | 0xFC        | 1             | mysticism[0]  |
    static constexpr std::int8_t kFullMap  = -7;  // | 0xF9        | 1,036,831,949 | necromancy[1] |
    static constexpr std::int8_t kFullMap2 = -5;  // | 0xFB        | 1,050,253,722 | necromancy[3] |
  };

  // Increases morale of the hero's troops by the specified number.
  //
  // During combat morale will always be clamped to [-3; 3], i.e. even with
  // "hexed" Leadership you cannot increase the odds of getting Good/Bad morale.
  // However, such "hexed" skills can still be useful if you want to ensure that a hero
  // will have +3 morale even if it's decreased due to some factors (e.g., troops of 7
  // different alignments decrease morale by 5; presence of Undead decreases it by 1;
  // Bone/Ghost Dragons in the opposing army decrease it by 1, etc).
  template<>
  struct SecondarySkillLevel<SecondarySkillType::Leadership>
  {
    // | Level (decimal)                               | Level (hex) | Effect      |
    // | --------------------------------------------- | ----------- | ----------- |
    static constexpr std::int8_t k101058054 = -14;  // | 0xF2        | 101,058,054 |
    static constexpr std::int8_t k100860675 = -20;  // | 0xEC        | 100,860,675 |
  };

  // Changes the maximum level of spells that the hero can learn (the default is 2).
  template<>
  struct SecondarySkillLevel<SecondarySkillType::Wisdom>
  {
    // | Level (decimal)                              | Level (hex) | Effect |
    // | ---------------------------------------------| ----------- | -------|
    static constexpr std::int8_t kMaxLevel1 = -1;  // | 0xFF        | 1      |
    static constexpr std::int8_t kNoSpells  = -2;  // | 0xFE        | 0      |
  };

  // Allows your hero to regenerate the specified number of spell points per day.
  //
  // Note that the Mysticism never exceeds the hero's normal maximum spell points:
  // for example, if the hero's normal maximum spell points is 100, and the hero currently has
  // 99 spell points, even with Expert Mysticism the hero will have 100 spell points on the next day.
  template<>
  struct SecondarySkillLevel<SecondarySkillType::Mysticism>
  {
    // | Level (decimal)                              | Level (hex) | Effect        | Source        |
    // | -------------------------------------------- | ----------- | ------------- | ------------- |
    static constexpr std::int8_t kFull      = -1;  // | 0xFF        | 1,050,253,722 | necromancy[3] |
    static constexpr std::int8_t kFull2     = -2;  // | 0xFE        | 1,045,220,557 | necromancy[2] |
    static constexpr std::int8_t kFull3     = -3;  // | 0xFD        | 1,036,831,949 | necromancy[1] |
    static constexpr std::int8_t kNoPoints  = -4;  // | 0xFC        | 0             | necromancy[0] |
    static constexpr std::int8_t kNoPoints2 = -8;  // | 0xF8        | 0             | leadership[0] |
    static constexpr std::int8_t kNoPoints3 = -12; // | 0xF4        | 0             | luck[0]       |
  };

  // Increases luck of the hero's troops by the specified number.
  //
  // During combat luck will always be clamped to [-3; 3], i.e. even with
  // "hexed" Luck you cannot increase the odds of getting Good/Bad luck.
  // However, such "hexed" skills can still be useful if you want to ensure that a hero
  // will have +3 luck even if it's decreased due to some factors.
  template<>
  struct SecondarySkillLevel<SecondarySkillType::Luck>
  {
    // | Level (decimal)                                | Level (hex) | Effect      |
    // | ---------------------------------------------- | ----------- | ----------- |
    static constexpr std::int8_t k101058054 = -10;   // | 0xF6        | 101,058,054 |
    static constexpr std::int8_t k100860675 = -16;   // | 0xF0        | 100,860,675 |
    static constexpr std::int8_t k1028      = -104;  // | 0x98        | 1028        |
    static constexpr std::int8_t k771       = -105;  // | 0x97        | 771         |
    static constexpr std::int8_t k33686018  = -112;  // | 0x90        | 33,686,018  |
  };

  template<>
  struct SecondarySkillLevel<SecondarySkillType::Ballistics>
  {
    static constexpr std::int8_t k8Shots     = -1;  // 0xFF;
    static constexpr std::int8_t k0Shots1    = -3;  // 0xFD;
    static constexpr std::int8_t k0Shots2    = -4;  // 0xFC;
    static constexpr std::int8_t k0Shots3    = -5;  // 0xFB;
    static constexpr std::int8_t k0Shots4    = -7;  // 0xF9;
    static constexpr std::int8_t k0Shots5    = -8;  // 0xF8;
    static constexpr std::int8_t k0Shots6    = -9;  // 0xF7;
    static constexpr std::int8_t kInstakill  = -10; // 0xF6;
    static constexpr std::int8_t kInstakill2 = -15; // 0xF1;
  };

  // The hero contributes the specified amount of gold per day to your cause.
  template<>
  struct SecondarySkillLevel<SecondarySkillType::Estates>
  {
    // | Level (decimal)                                  | Level (hex) | Effect        | Source     |
    // | ------------------------------------------------ | ----------- | ------------- | ---------- |
    static constexpr std::int8_t kBillionPerDay = -1;  // | 0xFF        | 1,041,865,114 | armorer[3] |
  };

  // Increases all hand-to-hand damage inflicted by the hero's troops by the specified amount.
  template<>
  struct SecondarySkillLevel<SecondarySkillType::Offense>
  {
    // | Level (decimal)                              | Level (hex) | Effect | Source     |
    // | -------------------------------------------- | ----------- | ------ | ---------- |
    static constexpr std::int8_t k50Percent = -1;  // | 0xFF        | 50%    | archery[3] |
  };

  // Reduces all damage inflicted against the hero's troops by the specified amount.
  template<>
  struct SecondarySkillLevel<SecondarySkillType::Armorer>
  {
    // | Level (decimal)                              | Level (hex) | Effect | Source     |
    // | -------------------------------------------- | ----------- | ------ | ---------- |
    static constexpr std::int8_t k50Percent = -5;  // | 0xFB        | 50%    | archery[3] |
  };

  // Increases the hero's normal maximum spell points by the specified amount.
  template<>
  struct SecondarySkillLevel<SecondarySkillType::Intelligence>
  {
    // | Level (decimal)                                | Level (hex) | Effect | Source       |
    // | ---------------------------------------------- | ----------- | ------ | ------------ |
    static constexpr std::int8_t k15Percent  = -1;   // | 0xFF        | 15%    | sorcery[3]   |
    static constexpr std::int8_t k10Percent  = -2;   // | 0xFE        | 10%    | sorcery[2]   |
    static constexpr std::int8_t k5Percent   = -3;   // | 0xFD        | 5%     | sorcery[1]   |
    static constexpr std::int8_t k30Percent  = -5;   // | 0xFB        | 30%    | logistics[3] |
    static constexpr std::int8_t k20Percent  = -6;   // | 0xFA        | 20%    | logistics[2] |
    static constexpr std::int8_t k10Percent1 = -7;   // | 0xF9        | 10%    | logistics[1] |
    static constexpr std::int8_t k60Percent  = -17;  // | 0xEF        | 60%    | diplomacy[3] |
    static constexpr std::int8_t k40Percent  = -23;  // | 0xE9        | 40%    | eagle_eye[1] |
  };

  // Endows hero's troops with magic resistance of the specified strength.
  template<>
  struct SecondarySkillLevel<SecondarySkillType::Resistance>
  {
    // | Level (decimal)                               | Level (hex) | Effect | Source       |
    // | --------------------------------------------- | ----------- | ------ | ------------ |
    static constexpr std::int8_t k60Percent  = -1;  // | 0xFF        | 60%    | diplomacy[3] |
    static constexpr std::int8_t k60Percent2 = -5;  // | 0xFB        | 60%    | eagle_eye[3] |
    static constexpr std::int8_t k40Percent  = -2;  // | 0xFE        | 40%    | diplomacy[2] |
    static constexpr std::int8_t k40Percent2 = -7;  // | 0xF9        | 40%    | eagle_eye[1] |
  };

  // Causes the hero's spells to inflict the specified amount of additional damage in combat.
  //
  // FYI: if the hero's speciality is Sorcery, the bonus from a "hexed" level is still constant:
  // e.g., Gird at level 40 with Sorcery{0xF3} will inflict 60% extra damage from spells, not
  // 60% * (1 + 0.05 * 40) = 180%.
  template<>
  struct SecondarySkillLevel<SecondarySkillType::Sorcery>
  {
    // | Level (decimal)                                | Level (hex) | Effect | Source        |
    // | ---------------------------------------------- | ----------- | ------ | ------------- |
    static constexpr std::int8_t k20Percent  = -2;   // | 0xFE        | 20%    | logistics[2]  |
    static constexpr std::int8_t k20Percent2 = -9;   // | 0xF7        | 20%    | resistance[3] |
    static constexpr std::int8_t k20Percent3 = -15;  // | 0xF1        | 20%    | diplomacy[1]  |
    static constexpr std::int8_t k30Percent  = -1;   // | 0xFF        | 30%    | logistics[3]  |
    static constexpr std::int8_t k40Percent  = -14;  // | 0xF2        | 40%    | diplomacy[2]  |
    static constexpr std::int8_t k40Percent2 = -19;  // | 0xED        | 40%    | eagle_eye[1]  |
    static constexpr std::int8_t k50Percent  = -18;  // | 0xEE        | 50%    | eagle_eye[2]  |
    static constexpr std::int8_t k50Percent2 = -33;  // | 0xDF        | 50%    | archery[3]    |
    static constexpr std::int8_t k60Percent  = -13;  // | 0xF3        | 60%    | diplomacy[3]  |
    static constexpr std::int8_t k60Percent2 = -17;  // | 0xEF        | 60%    | eagle_eye[3]  |
  };
}
