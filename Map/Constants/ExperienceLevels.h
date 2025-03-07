#pragma once

#include <array>
#include <cstdint>

namespace h3m
{
  // Provides experience points for each hero level.
  //
  // After level 11 the formula is approximately:
  //     f(N+1) = f(N)*1.2 - 400,
  // i.e.
  //     f(11+N) = 15500*(1.2^N) + 2000  (proof by mathematical induction).
  //
  // This formula is not exact, though. The recurrent relation is very close:
  //   level_73 = 1,256,968,851
  //   level_74 = 1,508,362,195
  //   level_73 * 1.2 - 400 = 1,508,362,221.2
  // The error in the non-recurrent formula grows with the level:
  //   f(74)    = 1,509,213,824.435...
  struct ExperienceLevels
  {
    // kNormalLevels[N] contains the experience points needed to achieve level N.
    static constexpr std::array<std::int32_t, 75> kNormalLevels =
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
              24'320,  // Level 13
              28'784,  // Level 14
              34'140,  // Level 15
              40'567,  // Level 16
              48'279,  // Level 17
              57'533,  // Level 18
              68'637,  // Level 19
              81'961,  // Level 20
              97'949,  // Level 21
             117'134,  // Level 22
             140'156,  // Level 23
             167'782,  // Level 24
             200'933,  // Level 25
             240'714,  // Level 26
             288'451,  // Level 27
             345'735,  // Level 28
             414'475,  // Level 29
             496'963,  // Level 30
             595'948,  // Level 31
             714'730,  // Level 32
             857'268,  // Level 33
           1'028'313,  // Level 34
           1'233'567,  // Level 35
           1'479'871,  // Level 36
           1'775'435,  // Level 37
           2'130'111,  // Level 38
           2'555'722,  // Level 39
           3'066'455,  // Level 40
           3'679'334,  // Level 41
           4'414'788,  // Level 42
           5'297'332,  // Level 43
           6'356'384,  // Level 44
           7'627'246,  // Level 45
           9'152'280,  // Level 46
          10'982'320,  // Level 47
          13'178'368,  // Level 48
          15'813'625,  // Level 49
          18'975'933,  // Level 50
          22'770'702,  // Level 51
          27'324'424,  // Level 52
          32'788'890,  // Level 53
          39'346'249,  // Level 54
          47'215'079,  // Level 55
          56'657'675,  // Level 56
          67'988'790,  // Level 57
          81'586'128,  // Level 58
          97'902'933,  // Level 59
         117'483'099,  // Level 60
         140'979'298,  // Level 61
         169'174'736,  // Level 62
         203'009'261,  // Level 63
         243'610'691,  // Level 64
         292'332'407,  // Level 65
         350'798'466,  // Level 66
         420'957'736,  // Level 67
         505'148'860,  // Level 68
         606'178'208,  // Level 69
         727'413'425,  // Level 70
         872'895'685,  // Level 71
       1'047'474'397,  // Level 72
       1'256'968'851,  // Level 73
       1'508'362'195,  // Level 74
    };

    // Levels after 74 are weird: the experience points don't fit into int32_t, but the game
    // uses modular arithmetic, so this works somehow.
    static constexpr std::int32_t level_88   =  1'810'034'207;
    static constexpr std::int32_t level_100  =  2'073'739'175;
    static constexpr std::int32_t level_108  =  2'099'639'276;
    static constexpr std::int32_t level_868  =  2'144'641'867;
    static constexpr std::int32_t level_3732 =  2'146'553'679;
    static constexpr std::int32_t level_5920 =  2'146'673'313;
    static constexpr std::int32_t level_6424 =  2'147'293'156;
  };
}
