#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/SavedGame/Portals.h>

namespace h3svg
{
  ObjectExits H3SVGReader::readObjectExits() const
  {
    ObjectExits object_exits;
    const std::uint16_t num_exits = readInt<std::uint16_t>();
    object_exits.exits.reserve(num_exits);
    for (std::uint16_t i = 0; i < num_exits; ++i)
    {
      object_exits.exits.push_back(readCoordinatesPacked());
    }
    return object_exits;
  }

  Portals H3SVGReader::readPortals() const
  {
    Portals portals;
    for (ObjectExits& monolith : portals.monoliths_two_way)
    {
      monolith = readObjectExits();
    }
    for (ObjectExits& monolith : portals.monoliths_one_way)
    {
      monolith = readObjectExits();
    }
    portals.whirlpools = readObjectExits();
    portals.subterranean_gates = readSubterraneanGates();
    return portals;
  }

  SubterraneanGates H3SVGReader::readSubterraneanGates() const
  {
    SubterraneanGates subterranean_gates;
    subterranean_gates.gates = readObjectExits();
    const std::uint16_t num_pairings = readInt<std::uint16_t>();
    subterranean_gates.pairings.reserve(num_pairings);
    for (std::uint16_t i = 0; i < num_pairings; ++i)
    {
      subterranean_gates.pairings.push_back(readInt<std::int32_t>());
    }
    return subterranean_gates;
  }
}
