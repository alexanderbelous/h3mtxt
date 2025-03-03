#pragma once

#include <h3mtxt/Map/Map.h>

#include <iosfwd>

namespace h3m::H3Reader_NS
{
  // Reads a *.h3m map from the given stream.
  // \param stream - input stream. The stream is expected to store either gzip-compressed
  //        or uncompressed *.h3m data.
  //        Note that HoMM3 expects a compressed map to be written as a single gzip stream,
  //        but parseh3m() doesn't have this restriction.
  // \return the parsed map.
  Map parseh3m(std::istream& stream);
}
