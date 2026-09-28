#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/Portals.h>

namespace h3json
{
  template<>
  h3svg::ObjectExits JsonReader<h3svg::ObjectExits>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::ObjectExits>;
    h3svg::ObjectExits object_exits;
    readField(object_exits.exits, value, Fields::kExits);
    return object_exits;
  }

  template<>
  h3svg::Portals
  JsonReader<h3svg::Portals>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::Portals>;
    h3svg::Portals portals;
    readField(portals.monoliths_two_way, value, Fields::kMonolithsTwoWay);
    readField(portals.monoliths_one_way, value, Fields::kMonolithsOneWay);
    readField(portals.whirlpools, value, Fields::kWhirlpools);
    readField(portals.subterranean_gates, value, Fields::kSubterraneanGates);
    return portals;
  }

  template<>
  h3svg::SubterraneanGates
  JsonReader<h3svg::SubterraneanGates>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::SubterraneanGates>;
    h3svg::SubterraneanGates subterranean_gates;
    readField(subterranean_gates.gates, value, Fields::kGates);
    readField(subterranean_gates.pairings, value, Fields::kPairings);
    return subterranean_gates;
  }
}
