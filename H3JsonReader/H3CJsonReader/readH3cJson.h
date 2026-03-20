#pragma once

#include <h3mtxt/Campaign/Campaign.h>

#include <iosfwd>

namespace h3json
{
  // Reads a H3C campaign from the given JSON file.
  // \param stream - input stream containing the JSON data.
  // \return the parsed campaign.
  h3m::Campaign readH3cJson(std::istream& stream);
}
