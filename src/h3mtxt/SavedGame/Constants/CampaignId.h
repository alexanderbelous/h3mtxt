#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <cstdint>

namespace h3svg
{
  // Type of the campaign.
  //
  // This is similar to h3m::CampaignId from Campaign/Constants/CampaignId.h,
  // but there are 2 important differences:
  // * This enum identifies the campaign itself rather than its template.
  // * The values are 0-based rather than 1-based.
  enum class CampaignId : std::uint8_t
  {
    LongLiveTheQueen = 0,
    Liberation = 1,
    SongForTheFather = 2,
    DungeonsAndDevils = 3,
    LongLivetheKing = 4,
    SpoilsOfWar = 5,
    SeedsOfDiscontent = 6,
    Bracada = 7,
    Islands = 8,
    Krewlod = 9,
    Nighon = 10,
    Tatalia = 11,
    Armageddon = 12,
    HackAndSlash = 13,
    BirthOfABarbarian = 14,
    NewBeginning = 15,
    ElixirOfLife = 16,
    RiseOfTheNecromancer = 17,
    UnholyAlliance = 18,
    SpecterOfPower = 19,
    Custom = 20
  };
}
