#pragma once

#include <h3mtxt/Map/Map.h>

#include <iosfwd>

namespace h3m::H3Reader_NS
{
  // Reads a *.h3m map from the given stream.
  // \param stream - input stream. The stream is expected to store
  //        either gzip-compressed or uncompressed *.h3m data.
  // \return the parsed map.
  Map parseh3m(std::istream& stream);
}
