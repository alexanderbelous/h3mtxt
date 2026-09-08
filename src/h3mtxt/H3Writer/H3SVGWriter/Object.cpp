#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/SavedGame/Object.h>

namespace h3svg
{
  void H3SVGWriter::writeData(const Object& object) const
  {
    writeData(object.coordinates);
    writeData(object.template_idx);
  }
}
