#pragma once

#include <h3mtxt/Map/ObjectDetails.h>

#include <iosfwd>
#include <span>

namespace h3m
{
  struct ObjectAttributes;

  // Reads a single ObjectDetails entry from the stream.
  // \param stream - input stream.
  // \param objects_attributes - ObjectAttributes for each kind of object on the map.
  // \return the parsed ObjectDetails.
  ObjectDetails readObjectDetails(std::istream& stream,
                                  std::span<const ObjectAttributes> objects_attributes);
}
