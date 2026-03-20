#pragma once

#include <cstdint>

namespace h3m
{
  // 8-bit integers that can be used as the theme music for a campaign
  // or in the prologue/epilogue of a campaign scenario.
  //
  // The game loads this from the CmpMusic.txt file inside the H3bitmap.lod resource.
  // AFAIU, the names in CmpMusic.txt are also used as filenames to locate the corresponding
  // .mp3 files in the MP3 directory.
  enum class CampaignMusic : std::uint8_t
  {
    CampainMusic01  = 0,
    CampainMusic02  = 1,
    CampainMusic03  = 2,
    CampainMusic04  = 3,
    CampainMusic05  = 4,
    CampainMusic06  = 5,
    CampainMusic07  = 6,
    CampainMusic08  = 7,
    CampainMusic09  = 8,
    AiTheme0        = 9,
    AiTheme1        = 10,
    AiTheme2        = 11,
    Combat01        = 12,
    Combat02        = 13,
    Combat03        = 14,
    Combat04        = 15,
    CstleTown       = 16,
    TowerTown       = 17,
    Rampart         = 18,
    InfernoTown     = 19,
    NecroTown       = 20,
    Dungeon         = 21,
    Stronghold      = 22,
    FortressTown    = 23,
    ElemTown        = 24,
    Dirt            = 25,
    Sand            = 26,
    Grass           = 27,
    Snow            = 28,
    Swamp           = 29,
    Rough           = 30,
    Underground     = 31,
    Lava            = 32,
    Water           = 33,
    GoodTheme       = 34,
    NeutralTheme    = 35,
    EvilTheme       = 36,
    SecretTheme     = 37,
    LoopLepr        = 38,
    MainMenu        = 39,
    WinScenario     = 40,
    CampainMusic10  = 41,
    BladeABCampaign = 42,
    BladeDBCampaign = 43,
    BladeDSCampaign = 44,
    BladeFLCampaign = 45,
    BladeFWCampaign = 46,
    BladePFCampaign = 47,
    CampainMusic11  = 48
  };
}
