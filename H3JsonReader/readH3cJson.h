#pragma once

#include <h3mtxt/Campaign/Campaign.h>

#include <iosfwd>

namespace h3m::H3JsonReader_NS
{
  // Reads a H3C campaign from the given JSON file.
  // \param stream - input stream containing the JSON data.
  // \return the parsed campaign.
  Campaign readH3cJson(std::istream& stream);
}
