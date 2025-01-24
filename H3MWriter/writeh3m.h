#pragma once

#include <iosfwd>

namespace h3m
{
  struct Map;

  // Writes H3M data into the given stream.
  // \param stream - output stream.
  // \param map - map to write.
  // \param compress - if true, the function will write (gzip) compressed H3M data,
  //        otherwise uncompressed H3M data.
  void writeh3m(std::ostream& stream, const Map& map, bool compress = true);
}
