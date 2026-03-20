#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/TimedEvent.h>

namespace h3json
{
  h3m::TimedEvent JsonReader<h3m::TimedEvent>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::TimedEvent>;
    h3m::TimedEvent event;
    readField(event.name, value, Fields::kName);
    readField(event.message, value, Fields::kMessage);
    readField(event.resources, value, Fields::kResources);
    readField(event.affected_players, value, Fields::kAffectedPlayers);
    readField(event.applies_to_human, value, Fields::kAppliesToHuman);
    readField(event.applies_to_computer, value, Fields::kAppliesToComputer);
    readField(event.day_of_first_occurence, value, Fields::kDayOfFirstOccurence);
    readField(event.repeat_after_days, value, Fields::kRepeatAfterDays);
    readField(event.unknown, value, Fields::kUnknown);
    return event;
  }
}
