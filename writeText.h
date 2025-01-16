#pragma once

#include <iosfwd>

namespace h3m
{
  struct Map;

  // Writes a textual representation of the given H3M map into the given stream.
  // \param stream - output stream.
  // \param map - input H3M map.
  void writeText(std::ostream& stream, const Map& map);
}