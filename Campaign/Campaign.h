#pragma once

#include <h3mtxt/Campaign/Constants/CampaignFormat.h>
#include <h3mtxt/Campaign/Constants/CampaignId.h>
#include <h3mtxt/Campaign/Constants/CampaignMusic.h>
#include <h3mtxt/Campaign/CampaignScenario.h>
#include <h3mtxt/Map/Base.h>

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
    // TODO: Maps are serialized after all scenarios, but there is some padding/unknown data in between.
    // std::vector<Map> maps;
  };
}
