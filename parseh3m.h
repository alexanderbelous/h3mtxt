#pragma once

#include <h3mparser/Map/Map.h>

#include <iosfwd>

namespace h3m
{

// Reads a *.h3m map from the given stream.
// \param stream - input stream. The stream is expected to store uncompressed *.h3m data.
// \return the parsed map.
Map parseh3m(std::istream& stream);

}