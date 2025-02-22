#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/H3Writer/Utils.h>
#include <h3mtxt/Campaign/Campaign.h>

#include <stdexcept>

namespace h3m::H3Writer_NS
{
  namespace
  {
    void checkCampaign(const Campaign& campaign)
    {
      if (campaign.scenarios.size() != countMapRegions(campaign.id))
      {
        throw std::runtime_error("H3Writer<Campaign>: wrong number of scenarios.");
      }
      const std::size_t num_existing_scenarios = countScenarios(campaign);
      if (campaign.maps.size() != num_existing_scenarios)
      {
        throw std::runtime_error("H3Writer<Campaign>: wrong number of maps.");
      }
    }
  }
  void H3Writer<Campaign>::operator()(std::ostream& stream, const Campaign& campaign) const
  {
    checkCampaign(campaign);
    writeData(stream, campaign.format);
    writeData(stream, campaign.id);
    writeData(stream, campaign.name);
    writeData(stream, campaign.description);
    writeData(stream, campaign.allow_selecting_difficulty);
    writeData(stream, campaign.theme_music);
    for (const CampaignScenario& scenario : campaign.scenarios)
    {
      writeCampaignScenario(stream, scenario, campaign.id);
    }
    for (const Map& map : campaign.maps)
    {
      writeData(stream, map);
    }
  }
}
