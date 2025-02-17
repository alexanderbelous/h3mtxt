#pragma once

#include <cstdint>

namespace h3m
{
  // Template to use for the campaign.
  // The Campaign Editor calls it "Campaign Map".
  enum class CampaignId : std::uint8_t
  {
    LongLiveTheQueen = 1,
    Liberation = 2,
    SongForTheFather = 3,
    DungeonsAndDevils = 4,
    LongLivetheKing = 5,
    SpoilsOfWar = 6,
    SeedsOfDiscontent = 7,
    Bracada = 8,
    Islands = 9,
    Krewlod = 10,
    Nighon = 11,
    Tatalia = 12,
    Armageddon = 13,
    HackAndSlash = 14,
    BirthOfABarbarian = 15,
    NewBeginning = 16,
    ElixirOfLife = 17,
    RiseOfTheNecromancer = 18,
    UnholyAlliance = 19,
    SpecterOfPower = 20,
  };

  // Returns the maximum number of map regions for the given CampaignId.
  // \param campaign_map - input CampaignId.
  // \return the maximum number of map regions for @campaign_map,
  //         or 0 if @campaign_map is not a valid CampaignId constant.
  constexpr std::uint8_t countMapRegions(CampaignId campaign_id) noexcept
  {
    switch (campaign_id)
    {
    case CampaignId::LongLiveTheQueen:
      return 3;
    case CampaignId::Liberation:
      return 4;
    case CampaignId::SongForTheFather:
      return 3;
    case CampaignId::DungeonsAndDevils:
      return 7;
    case CampaignId::LongLivetheKing:
      return 4;
    case CampaignId::SpoilsOfWar:
      return 3;
    case CampaignId::SeedsOfDiscontent:
      return 3;
    case CampaignId::Bracada:
    case CampaignId::Krewlod:
    case CampaignId::Nighon:
      return 4;
    case CampaignId::Tatalia:
      return 3;
    case CampaignId::Armageddon:
      return 8;
    case CampaignId::HackAndSlash:
      return 4;
    case CampaignId::BirthOfABarbarian:
      return 5;
    case CampaignId::NewBeginning:
    case CampaignId::ElixirOfLife:
    case CampaignId::RiseOfTheNecromancer:
      return 4;
    case CampaignId::UnholyAlliance:
      return 12;
    case CampaignId::SpecterOfPower:
      return 4;
    default:
      return 0;
    }
  }
}
