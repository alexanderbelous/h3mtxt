#pragma once

#include <h3mtxt/Map/Map.h>

#include <iosfwd>

namespace h3m
{

// Reads a *.h3m map from the given stream.
// \param stream - input stream. The stream is expected to store uncompressed *.h3m data.
// \param read_objects_details - if true, Map.objects_details and the next fields will be parsed,
//        otherwise they won't be.
// TODO: remove read_objects_details parameter.
// \return the parsed map.
Map parseh3m(std::istream& stream, bool read_objects_details = false);

}
