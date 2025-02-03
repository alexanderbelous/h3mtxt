#pragma once

#include <iosfwd>

namespace h3m
{
  struct Map;

  // Writes a JSON representation of the given H3M map into the given stream.
  // \param stream - output stream.
  // \param map - input H3M map.
  void writeH3mJson(std::ostream& stream, const Map& map);
}