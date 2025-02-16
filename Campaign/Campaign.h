#pragma once

#include <h3mtxt/Campaign/Constants/CampaignFormat.h>
#include <h3mtxt/Campaign/Constants/CampaignId.h>
#include <h3mtxt/Campaign/Constants/CampaignMusic.h>
#include <h3mtxt/Campaign/CampaignScenario.h>
#include <h3mtxt/Map/Map.h>

#include <string>
#include <vector>

namespace h3m
{
  // Represents a *.h3c campaign.
  struct Campaign
  {
    CampaignFormat format = CampaignFormat::ShadowOfDeath;
    CampaignId id {};
    std::string name;
    std::string description;
    Bool allow_selecting_difficulty {};
    CampaignMusic theme_music {};
    // The number of elements should be equal to countMapRegions(this->id),
    // even if the campaign has unused regions.
    std::vector<CampaignScenario> scenarios;
    // Map for each existing scenario.
    // Maps are ordered by regions (same as scenarios); if scenario[i].map_filename.empty(), then the
    // map will be missing for this region.
    std::vector<Map> maps;
  };

  // Computes the number of existing scenarios in the given Campaign.
  // \param campaign - input campaign. This function will only access campaign.scenarios.
  // \return the number of existing scenarios in @campaign.
  inline std::size_t countScenarios(const Campaign& campaign)
  {
    std::size_t result = 0;
    for (const CampaignScenario& scenario : campaign.scenarios)
    {
      if (!scenario.map_filename.empty())
      {
        ++result;
      }
    }
    return result;
  }
}
