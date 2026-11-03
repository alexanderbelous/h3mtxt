#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/Portals.h>

namespace h3json
{
  template<>
  h3svg::ObjectExits JsonReader2<h3svg::ObjectExits>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::ObjectExits>;
    h3svg::ObjectExits object_exits;
    readField(Fields::kExits, object_exits.exits);
    return object_exits;
  }

  template<>
  h3svg::Portals JsonReader2<h3svg::Portals>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::Portals>;
    h3svg::Portals portals;
    readField(Fields::kMonolithsTwoWay, portals.monoliths_two_way);
    readField(Fields::kMonolithsOneWay, portals.monoliths_one_way);
    readField(Fields::kWhirlpools, portals.whirlpools);
    readField(Fields::kSubterraneanGates, portals.subterranean_gates);
    return portals;
  }

  template<>
  h3svg::SubterraneanGates JsonReader2<h3svg::SubterraneanGates>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::SubterraneanGates>;
    h3svg::SubterraneanGates subterranean_gates;
    readField(Fields::kGates, subterranean_gates.gates);
    readField(Fields::kPairings, subterranean_gates.pairings);
    return subterranean_gates;
  }
}
