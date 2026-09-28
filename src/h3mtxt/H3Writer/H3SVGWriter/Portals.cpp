#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/SavedGame/Portals.h>

#include <stdexcept>

namespace h3svg
{
  void H3SVGWriter::writeData(const ObjectExits& object_exits) const
  {
    writeVector<std::uint16_t>(std::span{ object_exits.exits });
  }

  void H3SVGWriter::writeData(const Portals& portals) const
  {
    writeData(portals.monoliths_two_way);
    writeData(portals.monoliths_one_way);
    writeData(portals.whirlpools);
    writeData(portals.subterranean_gates);
  }

  void H3SVGWriter::writeData(const SubterraneanGates& value) const
  {
    writeData(value.gates);
    writeVector<std::uint16_t>(std::span{ value.pairings });
  }
}
