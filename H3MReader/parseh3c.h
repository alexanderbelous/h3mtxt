#pragma once

#include <h3mtxt/Campaign/Campaign.h>

#include <iosfwd>

namespace h3m
{
  // Reads a *.h3c campaign from the given stream.
  // \param stream - input stream. The stream is expected to store
  //        either gzip-compressed or uncompressed *.h3c data.
  // \return the parsed campaign.
  Campaign parseh3c(std::istream& stream);
}
