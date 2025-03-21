#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/JsonWriter/ScopedObjectWriter.h>
#include <h3mtxt/Map/TimedEventBase.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::TimedEventBase>::operator()(FieldsWriter& out, const h3m::TimedEventBase& event) const
  {
    using Fields = h3m::FieldNames<h3m::TimedEventBase>;
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
