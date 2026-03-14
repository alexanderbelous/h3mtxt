#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/Coordinates.h>

namespace h3m
{
  Coordinates H3MReader::readCoordinates() const
  {
    Coordinates result;
    result.x = readInt<std::uint8_t>();
    result.y = readInt<std::uint8_t>();
    result.z = readInt<std::uint8_t>();
    return result;
  }
}
