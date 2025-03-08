#pragma once

#include <array>
#include <cstdint>

namespace h3m
{
  // Provides experience points for each hero level.
  struct ExperienceLevels
  {
    // Hard-coded values for levels [0; 12].
    // kHardcodedLevels[N] stores the experience points needed to achieve level N.
    static constexpr std::array<std::int32_t, 13> kHardcodedLevels =
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

    // Levels after 75 are weird: the experience points don't fit into int32_t, but the game
    // uses modular arithmetic, so there are a few "stable" levels.
    static constexpr std::int32_t kLevel88   =  1'810'034'207;
    static constexpr std::int32_t kLevel100  =  2'073'739'175;
    static constexpr std::int32_t kLevel108  =  2'099'639'276;
    static constexpr std::int32_t kLevel868  =  2'144'641'867;
    static constexpr std::int32_t kLevel3732 =  2'146'553'679;
    static constexpr std::int32_t kLevel5920 =  2'146'673'313;
    static constexpr std::int32_t kLevel6424 =  2'147'293'156;

    // Calculates the experience needed to achieve the specified level.
    // \param level - hero level.
    // \return hero experience needed to achieve level @level.
    //         Note that most values > 74 are unstable in the game. Stable levels are
    //         {0-75, 88, 100, 108, 868, 3732, 5920, 6424}.
    static constexpr std::int32_t getExperienceForLevel(std::uint16_t level) noexcept;
  };

  constexpr std::int32_t ExperienceLevels::getExperienceForLevel(std::uint16_t level) noexcept
  {
    // Credits to RoseKavalier:
    // http://heroescommunity.com/viewthread.php3?TID=42328&PID=1375711#focus
    //
    // In HoMM3 experience for levels after 12 is basically given by the formula:
    //   f(N) = f(N-1) + floor((f(N-1) - f(N-2)) * 1.2),
    // i.e. the difference (in experience points) is multiplied by 1.2 for each level.
    //
    // This works fine until level 75 where f(75) overflows int32_t. In C++ signed integer overflow is UB,
    // but HoMM3 uses modulo arithmetic. This function reproduces the behavior in HoMM3 by using uint32_t
    // instead of int32_t for internal calculations.
    //
    // Then things get even hackier at level 87 because f(N-1) - f(N-2) overflows. Note that we cannot simply
    // treat f(N-1) - f(N-2) as an unsigned integer - multiplication by 1.2 is done via integer division, so
    // we need to convert the difference to int32_t before dividing it by 5, and then convert the result back
    // to uint32_t.

    // FYI: an approximation can be calculated much faster.
    // After level 11 the formula is approximately:
    //     f(N+1) = f(N)*1.2 - 400,
    // i.e.
    //     f(11+N) = 15500*(1.2^N) + 2000  (proof by mathematical induction).
    // The error grows with the level. It's relatively small for levels [12; 74]:
    // f(74) returns 1,509,213,824, which is close enough to 1,508,362,195.

    // Special case for levels [0; 12].
    if (level <= 12)
    {
      return kHardcodedLevels[level];
    }
    // Special case for non-standard "stable" levels.
    // TODO: this should be in the formula below, but it doesn't match for some reason.
    switch (level)
    {
      case 88:   return kLevel88;
      case 100:  return kLevel100;
      case 108:  return kLevel108;
      case 868:  return kLevel868;
      case 3732: return kLevel3732;
      case 5920: return kLevel5920;
      case 6424: return kLevel6424;
      default:
        break;
    }
    // Experience needed to achieve level 12.
    std::int32_t experience = ExperienceLevels::kHardcodedLevels[12];
    // Difference (in experience points) between level 12 and level 11.
    std::int32_t exp_diff_prev = ExperienceLevels::kHardcodedLevels[12] - ExperienceLevels::kHardcodedLevels[11];
    for (std::uint16_t i = 12; i < level; ++i)
    {
      const std::uint32_t experience_prev_unsigned = static_cast<std::uint32_t>(experience);
      // Calculate the difference between f(i) and f(i+1).
      // This is basically exp_diff_prev * 1.2, but overflow must be handled carefully.
      const std::uint32_t exp_diff_unsigned =
        static_cast<std::uint32_t>(exp_diff_prev) + static_cast<std::uint32_t>(exp_diff_prev / 5);
      const std::uint32_t experience_unsigned = experience_prev_unsigned + exp_diff_unsigned;
      // Update experience to store f(i+1).
      experience = static_cast<std::int32_t>(experience_unsigned);
      // Update exp_diff_prev to store f(i+1) - f(i).
      // This is equivalent to static_cast<std::int32_t>(experience_unsigned - experience_prev_unsigned).
      exp_diff_prev = static_cast<std::int32_t>(exp_diff_unsigned);
    }
    return experience;
  }

  // Level  Exp[N] uint32   Exp[N] int32     Diff[N]=Exp[N]-Exp[N-1]   Diff[N]*1.2 uint32   Diff[N]*1.2 int32
  //
  // 73:    1'256'968'851                    209'494'454               251'393'344.8
  // 74:    1'508'362'195                    251'393'344               301'672'012.8
  // 75:    1'810'034'207                    301'672'012               362'006'414.4
  // 76:    2'172'040'621   -2'122'926'675   362'006'414               434'407'696.8
  // 77:    2'606'448'317   -1'688'518'979   434'407'696               521'289'235.2
  // 86:    563'789'998
  // 87:    2'394'534'485   -1'900'432'811   1'830'744'487             2'196'893'384.4      -2'098'073'912
  // 88:    ?

  static_assert(ExperienceLevels::getExperienceForLevel(13) ==        24'320);
  static_assert(ExperienceLevels::getExperienceForLevel(14) ==        28'784);
  static_assert(ExperienceLevels::getExperienceForLevel(15) ==        34'140);
  static_assert(ExperienceLevels::getExperienceForLevel(16) ==        40'567);
  static_assert(ExperienceLevels::getExperienceForLevel(17) ==        48'279);
  static_assert(ExperienceLevels::getExperienceForLevel(18) ==        57'533);
  static_assert(ExperienceLevels::getExperienceForLevel(19) ==        68'637);
  static_assert(ExperienceLevels::getExperienceForLevel(20) ==        81'961);
  static_assert(ExperienceLevels::getExperienceForLevel(21) ==        97'949);
  static_assert(ExperienceLevels::getExperienceForLevel(22) ==       117'134);
  static_assert(ExperienceLevels::getExperienceForLevel(23) ==       140'156);
  static_assert(ExperienceLevels::getExperienceForLevel(24) ==       167'782);
  static_assert(ExperienceLevels::getExperienceForLevel(25) ==       200'933);
  static_assert(ExperienceLevels::getExperienceForLevel(26) ==       240'714);
  static_assert(ExperienceLevels::getExperienceForLevel(27) ==       288'451);
  static_assert(ExperienceLevels::getExperienceForLevel(28) ==       345'735);
  static_assert(ExperienceLevels::getExperienceForLevel(29) ==       414'475);
  static_assert(ExperienceLevels::getExperienceForLevel(30) ==       496'963);
  static_assert(ExperienceLevels::getExperienceForLevel(31) ==       595'948);
  static_assert(ExperienceLevels::getExperienceForLevel(32) ==       714'730);
  static_assert(ExperienceLevels::getExperienceForLevel(33) ==       857'268);
  static_assert(ExperienceLevels::getExperienceForLevel(34) ==     1'028'313);
  static_assert(ExperienceLevels::getExperienceForLevel(35) ==     1'233'567);
  static_assert(ExperienceLevels::getExperienceForLevel(36) ==     1'479'871);
  static_assert(ExperienceLevels::getExperienceForLevel(37) ==     1'775'435);
  static_assert(ExperienceLevels::getExperienceForLevel(38) ==     2'130'111);
  static_assert(ExperienceLevels::getExperienceForLevel(39) ==     2'555'722);
  static_assert(ExperienceLevels::getExperienceForLevel(40) ==     3'066'455);
  static_assert(ExperienceLevels::getExperienceForLevel(41) ==     3'679'334);
  static_assert(ExperienceLevels::getExperienceForLevel(42) ==     4'414'788);
  static_assert(ExperienceLevels::getExperienceForLevel(43) ==     5'297'332);
  static_assert(ExperienceLevels::getExperienceForLevel(44) ==     6'356'384);
  static_assert(ExperienceLevels::getExperienceForLevel(45) ==     7'627'246);
  static_assert(ExperienceLevels::getExperienceForLevel(46) ==     9'152'280);
  static_assert(ExperienceLevels::getExperienceForLevel(47) ==    10'982'320);
  static_assert(ExperienceLevels::getExperienceForLevel(48) ==    13'178'368);
  static_assert(ExperienceLevels::getExperienceForLevel(49) ==    15'813'625);
  static_assert(ExperienceLevels::getExperienceForLevel(50) ==    18'975'933);
  static_assert(ExperienceLevels::getExperienceForLevel(51) ==    22'770'702);
  static_assert(ExperienceLevels::getExperienceForLevel(52) ==    27'324'424);
  static_assert(ExperienceLevels::getExperienceForLevel(53) ==    32'788'890);
  static_assert(ExperienceLevels::getExperienceForLevel(54) ==    39'346'249);
  static_assert(ExperienceLevels::getExperienceForLevel(55) ==    47'215'079);
  static_assert(ExperienceLevels::getExperienceForLevel(56) ==    56'657'675);
  static_assert(ExperienceLevels::getExperienceForLevel(57) ==    67'988'790);
  static_assert(ExperienceLevels::getExperienceForLevel(58) ==    81'586'128);
  static_assert(ExperienceLevels::getExperienceForLevel(59) ==    97'902'933);
  static_assert(ExperienceLevels::getExperienceForLevel(60) ==   117'483'099);
  static_assert(ExperienceLevels::getExperienceForLevel(61) ==   140'979'298);
  static_assert(ExperienceLevels::getExperienceForLevel(62) ==   169'174'736);
  static_assert(ExperienceLevels::getExperienceForLevel(63) ==   203'009'261);
  static_assert(ExperienceLevels::getExperienceForLevel(64) ==   243'610'691);
  static_assert(ExperienceLevels::getExperienceForLevel(65) ==   292'332'407);
  static_assert(ExperienceLevels::getExperienceForLevel(66) ==   350'798'466);
  static_assert(ExperienceLevels::getExperienceForLevel(67) ==   420'957'736);
  static_assert(ExperienceLevels::getExperienceForLevel(68) ==   505'148'860);
  static_assert(ExperienceLevels::getExperienceForLevel(69) ==   606'178'208);
  static_assert(ExperienceLevels::getExperienceForLevel(70) ==   727'413'425);
  static_assert(ExperienceLevels::getExperienceForLevel(71) ==   872'895'685);
  static_assert(ExperienceLevels::getExperienceForLevel(72) == 1'047'474'397);
  static_assert(ExperienceLevels::getExperienceForLevel(73) == 1'256'968'851);
  static_assert(ExperienceLevels::getExperienceForLevel(74) == 1'508'362'195);
  // Nonstandard levels.
  static_assert(ExperienceLevels::getExperienceForLevel(75) ==  1'810'034'207);
  static_assert(ExperienceLevels::getExperienceForLevel(76) == -2'122'926'675);
  static_assert(ExperienceLevels::getExperienceForLevel(77) == -1'688'518'979);
  static_assert(ExperienceLevels::getExperienceForLevel(78) == -1'167'229'744);
  static_assert(ExperienceLevels::getExperienceForLevel(79) ==   -541'682'662);
  static_assert(ExperienceLevels::getExperienceForLevel(80) ==    208'973'836);
  static_assert(ExperienceLevels::getExperienceForLevel(85) == -1'677'658'290);
  static_assert(ExperienceLevels::getExperienceForLevel(86) ==    563'789'998);
  static_assert(ExperienceLevels::getExperienceForLevel(87) == -1'900'432'811);
}
