#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/SavedGame/Object.h>

namespace h3svg
{
  Object H3SVGReader::readObject() const
  {
    Object object;
    object.coordinates = readCoordinates();
    object.template_idx = readInt<std::uint16_t>();
    return object;
  }
}
