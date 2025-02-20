#include <h3mtxt/H3MReader/H3Reader.h>
#include <h3mtxt/H3MReader/Utils.h>

#include <h3mtxt/Campaign/Campaign.h>

namespace h3m::H3Reader_NS
{
  Campaign readCampaign(std::istream& stream)
  {
    Campaign campaign;
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
    const std::uint8_t max_num_scenarios = countMapRegions(campaign.id);
    campaign.scenarios.reserve(max_num_scenarios);
    for (std::uint8_t i = 0; i < max_num_scenarios; ++i)
    {
      campaign.scenarios.push_back(readCampaignScenario(stream, campaign.id));
    }
    const std::size_t num_scenarios = countScenarios(campaign);
    campaign.maps.reserve(num_scenarios);
    for (std::size_t i = 0; i < num_scenarios; ++i)
    {
      campaign.maps.push_back(readMap(stream));
    }
    return campaign;
  }
}
