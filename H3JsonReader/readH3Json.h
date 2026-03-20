#pragma once

#include <h3mtxt/Campaign/Campaign.h>
#include <h3mtxt/Map/Map.h>

#include <iosfwd>
#include <variant>

namespace h3json
{
  // Reads a *.h3m map or a .h3c campaign from the given JSON file.
  // \param stream - input stream containing JSON data. The stream is expected to store
  //        either a JSON-serialized h3m::Map or a JSON-serialized h3m::Campaign.
  // \return the parsed map/campaign.
  std::variant<h3m::Map, h3m::Campaign> readH3Json(std::istream& stream);
}
