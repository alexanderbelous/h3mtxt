#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>

#include <iosfwd>

namespace h3m
{
  // Writes a JSON representation of the given H3C campaign into the given stream.
  // \param stream - output stream.
  // \param campaign - input H3C campaign.
  void writeH3cJson(std::ostream& stream, const Campaign& campaign);
}