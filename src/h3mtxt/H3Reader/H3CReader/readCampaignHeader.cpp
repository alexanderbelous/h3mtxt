#include <h3mtxt/H3Reader/H3CReader/H3CReader.h>

#include <h3mtxt/Campaign/CampaignHeader.h>

namespace h3m
{
  CampaignHeader H3CReader::readCampaignHeader() const
  {
    CampaignHeader campaign;
    campaign.format = readEnum<CampaignFormat>();
    if (campaign.format != CampaignFormat::ShadowOfDeath)
    {
      throw std::runtime_error("Unsupported CampaignFormat. Only ShadowOfDeath is supported.");
    }
    campaign.id = readEnum<CampaignId>();
    campaign.name = readString32();
    campaign.description = readString32();
    campaign.allow_selecting_difficulty = readBool();
    campaign.theme_music = readEnum<CampaignMusic>();
    const std::uint8_t num_regions = countRegions(campaign.id);
    campaign.scenarios.reserve(num_regions);
    for (std::uint8_t i = 0; i < num_regions; ++i)
    {
      campaign.scenarios.push_back(readCampaignScenario(campaign.id));
    }
    return campaign;
  }
}
