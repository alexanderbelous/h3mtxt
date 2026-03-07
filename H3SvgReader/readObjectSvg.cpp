#include <h3mtxt/H3SvgReader/H3SvgReader.h>
#include <h3mtxt/SavedGame/ObjectSvg.h>

namespace h3svg
{
  ObjectSvg H3SvgReader::readObject() const
  {
    ObjectSvg object;
    object.coordinates = readCoordinates();
    object.template_idx = readInt<std::uint16_t>();
    return object;
  }
}
