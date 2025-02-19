#pragma once

#include <iosfwd>

namespace h3m
{
  struct Campaign;

  // Writes a JSON representation of the given H3C campaign into the given stream.
  // \param stream - output stream.
  // \param campaign - input H3C campaign.
  void writeH3cJson(std::ostream& stream, const Campaign& campaign);
}