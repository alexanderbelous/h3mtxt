#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/Utils.h>

#include <h3mtxt/Campaign/CampaignHeader.h>

namespace h3m::H3Reader_NS
{
  CampaignHeader readCampaignHeader(std::istream& stream)
  {
    CampaignHeader campaign;
    campaign.format = readEnum<CampaignFormat>(stream);
    if (campaign.format != CampaignFormat::ShadowOfDeath)
    {
      throw std::runtime_error("Unsupported CampaignFormat. Only ShadowOfDeath is supported.");
    }
    campaign.id = readEnum<CampaignId>(stream);
    campaign.name = readString(stream);
    campaign.description = readString(stream);
    campaign.allow_selecting_difficulty = readBool(stream);
    campaign.theme_music = readEnum<CampaignMusic>(stream);
    const std::uint8_t num_regions = countRegions(campaign.id);
    campaign.scenarios.reserve(num_regions);
    for (std::uint8_t i = 0; i < num_regions; ++i)
    {
      campaign.scenarios.push_back(readCampaignScenario(stream, campaign.id));
    }
    return campaign;
  }
}
