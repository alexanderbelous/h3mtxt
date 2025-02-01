#pragma once

#include <h3mtxt/Map/Map.h>

#include <iosfwd>

namespace h3m
{
  // Reads a H3M map from the given JSON file.
  // \param stream - input stream containing the JSON data.
  // \return the parsed map.
  Map readH3mJson(std::istream& stream);
}
