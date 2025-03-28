#pragma once

#include <array>
#include <cstdint>

// In HoMM3 experience for levels after 12 is basically given by the formula
//   f(N) = f(N-1) + floor((f(N-1) - f(N-2)) * 1.2),
// i.e. the difference (in experience points) is multiplied by 1.2 for each level.
// Credits to RoseKavalier:
// http://heroescommunity.com/viewthread.php3?TID=42328&PID=1375711#focus
//
// This works fine until level 76 where f(76) overflows int32_t. In C++ signed integer overflow is UB,
// but HoMM3 uses modular arithmetic. This function reproduces the behavior in HoMM3 by using uint32_t
// instead of int32_t for internal calculations.
//
// Then, things get even hackier at level 87 because f(N-1) - f(N-2) overflows. Note that we cannot simply
// treat f(N-1) - f(N-2) as an unsigned integer - multiplication by 1.2 is done via integer division, so
// we need to convert the difference to int32_t before dividing it by 5, and then convert the result back
// to uint32_t.
//
// FYI: without floor() the formula above could be simplified to
//   g(N) = 15500 * 1.2^(N-11) + 2000,  N >= 11  (proof by mathematical induction).
// However, the error in this approximation grows with the level: e.g.,
// g(74) returns 1,509,213,824, but in reality the experience for level 74 is 1,508,362,195.
//
// * Level 0 has well-defined behavior in the game, but it's basically a dead end.
// * Levels [1; 74] are "normal": their experience points fit into [0; 2147483647].
// * Levels after 75 are "abnormal": their experience points don't fit into [0; 2147483647].
//   The game treats overflow in an interesting way: it uses modular arithmetic, and the
//   actual formula is
//     experience(N) = max(f(i), 0 <= i <= N)
//   As a consequence, these levels have the same experience points:
//     [  75;   88] with experience = 1,810,034,207
//     [  89;  100] with experience = 2,073,739,175
//     [ 101;  108] with experience = 2,099,639,276
//     [ 109;  868] with experience = 2,144,641,867
//     [ 869; 3732] with experience = 2,146,553,679
//     [3733; 5920] with experience = 2,146,673,313
//     [5921; 6424] with experience = 2,147,293,156
//   Because of this, levels 88, 100, 108, 868, 3732, 5920, 6424 are considered "stable", and the rest are not.
//
// * Levels greater than 6424 seem to be to impossible to achieve without modding or savegame editing.
//   In theory, there are a few more "stable" levels after 6424:
//     [6425;  72924] with experience = 2,147,400,657
//     [72925; 78666] with experience = 2,147,418,494
//     [78667; +inf)  with experience = 2,147,436,852
//   All levels >= 78667 have the same experience because there is a loop in f(N):
//     f(78667) = f(167483) = f(256299) = f(345115) = ...
//   However, the game freezes if you try to set a value >= 2,147,400,657 as the hero's experience.
//   I suspect that it goes into an infinite loop trying to find the next "stable" level
//   but using a 16-bit integer for the level.
namespace h3m
{
  namespace Detail_NS
  {
    // Hard-coded values for levels [0; 12].
    // kExperienceForLevel[N] stores the experience points needed to achieve level N.
    inline constexpr std::array<std::int32_t, 13> kExperienceForLevel =
    {
      -2'147'483'648,  // Level  0
                   0,  // Level  1
               1'000,  // Level  2
               2'000,  // Level  3
               3'200,  // Level  4
               4'600,  // Level  5
               6'200,  // Level  6
               8'000,  // Level  7
              10'000,  // Level  8
              12'200,  // Level  9
              14'700,  // Level 10
              17'500,  // Level 11
              20'600,  // Level 12
    };
  }

  // Calculates the experience needed to achieve the specified level.
  // \param level - hero level.
  // \return hero experience needed to achieve level @level.
  constexpr std::int32_t getExperienceForLevel(std::uint16_t level) noexcept
  {
    // Special case for levels [0; 12].
    if (level <= 12)
    {
      return Detail_NS::kExperienceForLevel[level];
    }
    // f(i) = experience needed to achieve level i; i == 12 initially.
    std::int32_t experience = Detail_NS::kExperienceForLevel[12];
    // diff(i) = f(i) - f(i-1); i == 12 initially.
    std::int32_t exp_diff = Detail_NS::kExperienceForLevel[12] - Detail_NS::kExperienceForLevel[11];
    // For "abnormal" levels: keep track of the highest encountered experience threshold.
    std::int32_t highest_experience = 0;
    // FYI: this can be done faster for "abnormal" levels, but it would require hard-coding or precomputing them.
    for (std::uint32_t i = 12; i < level; ++i)
    {
      // Update `exp_diff` to store diff(i+1) = f(i+1) - f(i).
      // This is basically multiplying by 1.2, but overflow must be handled carefully.
      exp_diff = static_cast<std::int32_t>(
        static_cast<std::uint32_t>(exp_diff) + static_cast<std::uint32_t>(exp_diff / 5));
      // Update `experience` to store f(i+1).
      experience = static_cast<std::int32_t>(
        static_cast<std::uint32_t>(experience) + static_cast<std::uint32_t>(exp_diff));
      // Update `highest_experience` if needed.
      if (experience > highest_experience)
      {
        highest_experience = experience;
      }
    }
    // return `experience` instead if you want to get the cap for MapBasicInfo::max_hero_level.
    return highest_experience;
  }

  // Finds the hero level corresponding to the given experience points.
  // \param experience - experience points.
  // \return hero level corresponding to @experience,
  //         or 65535 if experience >= 2,147,400,657 (such values cannot be used in the game).
  constexpr std::uint16_t getLevelForExperience(const std::int32_t experience) noexcept
  {
    // FYI: this can be done faster with binary search, but it would require hard-coding or precomputing an array.

    // Special case for levels [0; 11].
    if (experience < Detail_NS::kExperienceForLevel[12])
    {
      for (std::uint16_t level = 0; level < 12; ++level)
      {
        if (experience < Detail_NS::kExperienceForLevel[level + 1])
        {
          return level;
        }
      }
    }
    // f(i) = experience needed to achieve level i; i == 12 initially.
    std::int32_t exp = Detail_NS::kExperienceForLevel[12];
    // diff(i) = f(i) - f(i-1); i == 12 initially.
    std::int32_t exp_diff = Detail_NS::kExperienceForLevel[12] - Detail_NS::kExperienceForLevel[11];
    for (std::uint16_t i = 12; i < 6425; ++i)
    {
      // Update `exp_diff` to store diff(i+1) = f(i+1) - f(i).
      // This is basically multiplying by 1.2, but overflow must be handled carefully.
      exp_diff = static_cast<std::int32_t>(
        static_cast<std::uint32_t>(exp_diff) + static_cast<std::uint32_t>(exp_diff / 5));
      // Update `exp` to store f(i+1).
      exp = static_cast<std::int32_t>(
        static_cast<std::uint32_t>(exp) + static_cast<std::uint32_t>(exp_diff));
      // Break if f(i+1) > `experience`.
      if (exp > experience)
      {
        return i;
      }
    }
    // Degenerate case: experience >= 2,147,400,657.
    return 65535;
  }

  static_assert(getExperienceForLevel(13)   ==        24'320);
  static_assert(getExperienceForLevel(14)   ==        28'784);
  static_assert(getExperienceForLevel(15)   ==        34'140);
  static_assert(getExperienceForLevel(16)   ==        40'567);
  static_assert(getExperienceForLevel(17)   ==        48'279);
  static_assert(getExperienceForLevel(18)   ==        57'533);
  static_assert(getExperienceForLevel(19)   ==        68'637);
  static_assert(getExperienceForLevel(20)   ==        81'961);
  static_assert(getExperienceForLevel(21)   ==        97'949);
  static_assert(getExperienceForLevel(22)   ==       117'134);
  static_assert(getExperienceForLevel(23)   ==       140'156);
  static_assert(getExperienceForLevel(24)   ==       167'782);
  static_assert(getExperienceForLevel(25)   ==       200'933);
  static_assert(getExperienceForLevel(26)   ==       240'714);
  static_assert(getExperienceForLevel(27)   ==       288'451);
  static_assert(getExperienceForLevel(28)   ==       345'735);
  static_assert(getExperienceForLevel(29)   ==       414'475);
  static_assert(getExperienceForLevel(30)   ==       496'963);
  static_assert(getExperienceForLevel(31)   ==       595'948);
  static_assert(getExperienceForLevel(32)   ==       714'730);
  static_assert(getExperienceForLevel(33)   ==       857'268);
  static_assert(getExperienceForLevel(34)   ==     1'028'313);
  static_assert(getExperienceForLevel(35)   ==     1'233'567);
  static_assert(getExperienceForLevel(36)   ==     1'479'871);
  static_assert(getExperienceForLevel(37)   ==     1'775'435);
  static_assert(getExperienceForLevel(38)   ==     2'130'111);
  static_assert(getExperienceForLevel(39)   ==     2'555'722);
  static_assert(getExperienceForLevel(40)   ==     3'066'455);
  static_assert(getExperienceForLevel(41)   ==     3'679'334);
  static_assert(getExperienceForLevel(42)   ==     4'414'788);
  static_assert(getExperienceForLevel(43)   ==     5'297'332);
  static_assert(getExperienceForLevel(44)   ==     6'356'384);
  static_assert(getExperienceForLevel(45)   ==     7'627'246);
  static_assert(getExperienceForLevel(46)   ==     9'152'280);
  static_assert(getExperienceForLevel(47)   ==    10'982'320);
  static_assert(getExperienceForLevel(48)   ==    13'178'368);
  static_assert(getExperienceForLevel(49)   ==    15'813'625);
  static_assert(getExperienceForLevel(50)   ==    18'975'933);
  static_assert(getExperienceForLevel(51)   ==    22'770'702);
  static_assert(getExperienceForLevel(52)   ==    27'324'424);
  static_assert(getExperienceForLevel(53)   ==    32'788'890);
  static_assert(getExperienceForLevel(54)   ==    39'346'249);
  static_assert(getExperienceForLevel(55)   ==    47'215'079);
  static_assert(getExperienceForLevel(56)   ==    56'657'675);
  static_assert(getExperienceForLevel(57)   ==    67'988'790);
  static_assert(getExperienceForLevel(58)   ==    81'586'128);
  static_assert(getExperienceForLevel(59)   ==    97'902'933);
  static_assert(getExperienceForLevel(60)   ==   117'483'099);
  static_assert(getExperienceForLevel(61)   ==   140'979'298);
  static_assert(getExperienceForLevel(62)   ==   169'174'736);
  static_assert(getExperienceForLevel(63)   ==   203'009'261);
  static_assert(getExperienceForLevel(64)   ==   243'610'691);
  static_assert(getExperienceForLevel(65)   ==   292'332'407);
  static_assert(getExperienceForLevel(66)   ==   350'798'466);
  static_assert(getExperienceForLevel(67)   ==   420'957'736);
  static_assert(getExperienceForLevel(68)   ==   505'148'860);
  static_assert(getExperienceForLevel(69)   ==   606'178'208);
  static_assert(getExperienceForLevel(70)   ==   727'413'425);
  static_assert(getExperienceForLevel(71)   ==   872'895'685);
  static_assert(getExperienceForLevel(72)   == 1'047'474'397);
  static_assert(getExperienceForLevel(73)   == 1'256'968'851);
  static_assert(getExperienceForLevel(74)   == 1'508'362'195);
  // Nonstandard levels.
  static_assert(getExperienceForLevel(75)   == 1'810'034'207);
  static_assert(getExperienceForLevel(88)   == 1'810'034'207);
  static_assert(getExperienceForLevel(100)  == 2'073'739'175);
  static_assert(getExperienceForLevel(108)  == 2'099'639'276);
  static_assert(getExperienceForLevel(868)  == 2'144'641'867);
  static_assert(getExperienceForLevel(3732) == 2'146'553'679);
  static_assert(getExperienceForLevel(5920) == 2'146'673'313);
  static_assert(getExperienceForLevel(6424) == 2'147'293'156);

  static_assert(getLevelForExperience(-2'147'483'648) ==     0);
  static_assert(getLevelForExperience(            -1) ==     0);
  static_assert(getLevelForExperience(             0) ==     1);
  static_assert(getLevelForExperience(           500) ==     1);
  static_assert(getLevelForExperience(          1000) ==     2);
  static_assert(getLevelForExperience(        17'500) ==    11);
  static_assert(getLevelForExperience(        20'599) ==    11);
  static_assert(getLevelForExperience(        20'600) ==    12);
  static_assert(getLevelForExperience(        24'319) ==    12);
  static_assert(getLevelForExperience(        24'320) ==    13);
  static_assert(getLevelForExperience( 1'508'362'195) ==    74);
  static_assert(getLevelForExperience( 1'810'034'206) ==    74);
  static_assert(getLevelForExperience( 1'810'034'207) ==    88);
  static_assert(getLevelForExperience( 2'073'739'175) ==   100);
  static_assert(getLevelForExperience( 2'099'639'276) ==   108);
  static_assert(getLevelForExperience( 2'144'641'867) ==   868);
  static_assert(getLevelForExperience( 2'146'553'679) ==  3732);
  static_assert(getLevelForExperience( 2'146'673'313) ==  5920);
  static_assert(getLevelForExperience( 2'147'293'155) ==  5920);
  static_assert(getLevelForExperience( 2'147'293'156) ==  6424);
  static_assert(getLevelForExperience( 2'147'400'656) ==  6424);
  static_assert(getLevelForExperience( 2'147'400'657) == 65535);

  // Disregard: these values are not for levels but for
  // the experience thresholds yielded by MapBasicInfo::max_hero_level.
  //static_assert(getExperienceForLevel(76) == -2'122'926'675);
  //static_assert(getExperienceForLevel(77) == -1'688'518'979);
  //static_assert(getExperienceForLevel(78) == -1'167'229'744);
  //static_assert(getExperienceForLevel(79) ==   -541'682'662);
  //static_assert(getExperienceForLevel(80) ==    208'973'836);
  //static_assert(getExperienceForLevel(85) == -1'677'658'290);
  //static_assert(getExperienceForLevel(86) ==    563'789'998);
  //static_assert(getExperienceForLevel(87) == -1'900'432'811);
}
