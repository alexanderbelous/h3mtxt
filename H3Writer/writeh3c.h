#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>

#include <iosfwd>

namespace h3m::H3Writer_NS
{
  // Writes the inpit h3m::Campaign into the specified stream.
  // \param stream - output stream.
  // \param campaign - campaign to write.
  // \param compress - if true, the function will write (gzip) compressed .h3c data,
  //        otherwise uncompressed data.
  void writeh3c(std::ostream& stream, const Campaign& campaign, bool compress = true);
}
