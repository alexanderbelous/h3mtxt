#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>

#include <iosfwd>

namespace h3m::H3Writer_NS
{
  // Writes the given h3m::Campaign as a .h3c file into the specified stream.
  //
  // The Campaign Editor does not support uncompressed files, so there is no @compress
  // param like in writeh3m().
  // \param stream - output stream.
  // \param campaign - campaign to write.
  void writeh3c(std::ostream& stream, const Campaign& campaign);
}
