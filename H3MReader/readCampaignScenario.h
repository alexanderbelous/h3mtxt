#pragma once

#include <h3mtxt/Campaign/CampaignScenario.h>

#include <iosfwd>

namespace h3m
{
  CampaignScenario readCampaignScenario(std::istream& stream);
}
