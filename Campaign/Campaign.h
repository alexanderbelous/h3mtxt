#pragma once

#include <h3mtxt/Campaign/CampaignHeader.h>
#include <h3mtxt/Map/Map.h>

#include <vector>

namespace h3m
{
  // Represents a *.h3c campaign.
  struct Campaign
  {
    CampaignHeader header;
    // Map for each existing scenario.
    // The number of maps must be equal to countScenarios(header).
    // Maps are ordered by regions (same as scenarios); if scenario[i].map_filename.empty(), then the
    // map will be missing for this region.
    std::vector<Map> maps;
  };
}
