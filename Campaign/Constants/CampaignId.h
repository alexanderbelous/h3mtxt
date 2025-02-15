#pragma once

#include <cstdint>

namespace h3m
{
  // Template to use for the campaign (see CampText.txt).
  // The Campaign Editor calls it "Campaign Map".
  enum class CampaignId : std::uint8_t
  {
    Armageddon = 0x0d,
    // TODO: add the rest.
  };

  // Returns the maximum number of map regions for the given CampaignId.
  // \param campaign_map - input CampaignId.
  // \return the maximum number of map regions for @campaign_map,
  //         or 0 if @campaign_map is not a valid CampaignId constant.
  constexpr std::uint8_t countMapRegions(CampaignId campaign_id) noexcept
  {
    switch (campaign_id)
    {
    case CampaignId::Armageddon:
      return 8;
    // TODO: add the rest.
    default:
      return 0;
    }
  }
}
