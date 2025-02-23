#pragma once

#include <h3mtxt/Campaign/Campaign.h>
#include <h3mtxt/Map/Map.h>

#include <iosfwd>
#include <variant>

namespace h3m::H3Reader_NS
{
  // Reads a *.h3m map or a .h3c campaign from the given stream.
  // \param stream - input stream. The stream is expected to store
  //        either .h3c data or (possibly gzip-compressed) .h3m data.
  // \return the parsed map/campaign.
  std::variant<Map, Campaign> parseh3(std::istream& stream);
}
