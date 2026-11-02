#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/TimedEvent.h>

namespace h3json
{
  template<>
  h3m::TimedEvent JsonReader2<h3m::TimedEvent>::operator()() const
  {
    using Fields = FieldNames<h3m::TimedEvent>;
    h3m::TimedEvent event;
    readField(Fields::kName, event.name);
    readField(Fields::kMessage, event.message);
    readField(Fields::kResources, event.resources);
    readField(Fields::kAffectedPlayers, event.affected_players);
    readField(Fields::kAppliesToHuman, event.applies_to_human);
    readField(Fields::kAppliesToComputer, event.applies_to_computer);
    readField(Fields::kDayOfFirstOccurence, event.day_of_first_occurence);
    readField(Fields::kRepeatAfterDays, event.repeat_after_days);
    readField(Fields::kUnknown, event.unknown);
    return event;
  }
}
