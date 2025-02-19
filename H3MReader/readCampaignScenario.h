#pragma once

#include <h3mtxt/Campaign/Constants/CampaignId.h>
#include <h3mtxt/Campaign/CampaignScenario.h>

#include <iosfwd>

namespace h3m
{
  CampaignScenario readCampaignScenario(std::istream& stream, CampaignId campaign_id);
}
