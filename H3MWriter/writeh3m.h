#pragma once

#include <iosfwd>

namespace h3m
{
  struct Map;

  // Writes uncompressed H3M data into the given stream.
  // \param stream - output stream.
  // \param map - map to write.
  void writeh3m(std::ostream& stream, const Map& map);
}
