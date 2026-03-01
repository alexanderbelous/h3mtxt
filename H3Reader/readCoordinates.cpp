#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/Map/Coordinates.h>

namespace h3m::H3Reader_NS
{
  Coordinates readCoordinates(std::istream& stream)
  {
    Coordinates result;
    result.x = readInt<std::uint8_t>(stream);
    result.y = readInt<std::uint8_t>(stream);
    result.z = readInt<std::uint8_t>(stream);
    return result;
  }
}
