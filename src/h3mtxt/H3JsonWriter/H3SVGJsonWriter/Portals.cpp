#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/Portals.h>
#include <h3mtxt/Medea/Medea.h>

namespace Medea_NS
{
  template<>
  void JsonObjectWriter<h3svg::ObjectExits>::operator()(FieldsWriter& out, const h3svg::ObjectExits& object_exits) const
  {
    using Fields = h3json::FieldNames<h3svg::ObjectExits>;
    out.writeField(Fields::kExits, object_exits.exits);
  }

  template<>
  void JsonObjectWriter<h3svg::Portals>::operator()(FieldsWriter& out,
                                                    const h3svg::Portals& portals) const
  {
    using Fields = h3json::FieldNames<h3svg::Portals>;
    out.writeField(Fields::kMonolithsTwoWay, portals.monoliths_two_way);
    out.writeField(Fields::kMonolithsOneWay, portals.monoliths_one_way);
    out.writeField(Fields::kWhirlpools, portals.whirlpools);
    out.writeField(Fields::kSubterraneanGates, portals.subterranean_gates);
  }

  template<>
  void JsonObjectWriter<h3svg::SubterraneanGates>::operator()(FieldsWriter& out,
                                                              const h3svg::SubterraneanGates& subterranean_gates) const
  {
    using Fields = h3json::FieldNames<h3svg::SubterraneanGates>;
    out.writeField(Fields::kGates, subterranean_gates.gates);
    out.writeField(Fields::kPairings, subterranean_gates.pairings);
  }
}
