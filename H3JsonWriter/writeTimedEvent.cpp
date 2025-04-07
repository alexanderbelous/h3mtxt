#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/TimedEvent.h>
#include <h3mtxt/Medea/Medea.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::TimedEvent>::operator()(FieldsWriter& out, const h3m::TimedEvent& event) const
  {
    using Fields = h3m::FieldNames<h3m::TimedEvent>;
    out.writeField(Fields::kName, event.name);
    out.writeField(Fields::kMessage, event.message);
    out.writeField(Fields::kResources, event.resources);
    out.writeField(Fields::kAffectedPlayers, event.affected_players);
    out.writeField(Fields::kAppliesToHuman, event.applies_to_human);
    out.writeField(Fields::kAppliesToComputer, event.applies_to_computer);
    out.writeField(Fields::kDayOfFirstOccurence, event.day_of_first_occurence);
    out.writeField(Fields::kRepeatAfterDays, event.repeat_after_days);
    out.writeField(Fields::kUnknown, event.unknown);
  }
}
