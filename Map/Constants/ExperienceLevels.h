#pragma once

#include <cstdint>

namespace h3m
{
  // TODO: add all valid levels.
  struct ExperienceLevels
  {
    static constexpr std::int32_t level_0    = -2'147'483'648;
    static constexpr std::int32_t level_1    =              0;
    static constexpr std::int32_t level_2    =          1'000;
    static constexpr std::int32_t level_3    =          2'000;
    static constexpr std::int32_t level_4    =          3'200;
    static constexpr std::int32_t level_5    =          4'600;
    static constexpr std::int32_t level_6    =          6'200;
    static constexpr std::int32_t level_7    =          8'000;
    static constexpr std::int32_t level_8    =         10'000;
    static constexpr std::int32_t level_9    =         12'200;
    static constexpr std::int32_t level_10   =         14'700;
    static constexpr std::int32_t level_20   =         81'961;
    static constexpr std::int32_t level_30   =        496'963;
    static constexpr std::int32_t level_40   =      3'066'455;
    static constexpr std::int32_t level_50   =     18'975'933;
    static constexpr std::int32_t level_60   =    117'483'099;
    static constexpr std::int32_t level_70   =    727'413'425;
    static constexpr std::int32_t level_71   =    872'895'685;
    static constexpr std::int32_t level_72   =  1'047'474'397;
    static constexpr std::int32_t level_73   =  1'256'968'851;
    static constexpr std::int32_t level_74   =  1'508'362'195;
    static constexpr std::int32_t level_88   =  1'810'034'207;
    static constexpr std::int32_t level_100  =  2'073'739'175;
    static constexpr std::int32_t level_108  =  2'099'639'276;
    static constexpr std::int32_t level_868  =  2'144'641'867;
    static constexpr std::int32_t level_3732 =  2'146'553'679;
    static constexpr std::int32_t level_5920 =  2'146'673'313;
    static constexpr std::int32_t level_6424 =  2'147'293'156;
  };
}