#include <h3mtxt/H3JsonReader/H3JsonReader.h>
#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/TimedEvent.h>

namespace h3m::H3JsonReader_NS
{
  TimedEvent JsonReader<TimedEvent>::operator()(const Json::Value& value) const
  {
    using Fields = h3m::FieldNames<h3m::TimedEvent>;
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
