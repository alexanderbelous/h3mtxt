#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/SavedGame/ObjectPropertiesTables.h>

namespace h3svg
{
  void H3SVGWriter::writeData(const ObjectPropertiesTables& tables) const
  {
    writeData(safeCastVectorSize<std::uint16_t>(tables.events_and_pandoras_boxes.size()));
    writeSpan(std::span{ tables.events_and_pandoras_boxes });
    // TODO: serialize the rest.
  }
}
