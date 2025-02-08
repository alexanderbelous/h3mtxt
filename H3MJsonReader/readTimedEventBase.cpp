#include <h3mtxt/H3MJsonReader/readTimedEventBase.h>

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/H3MJsonReader/readPlayersBitmask.h>
#include <h3mtxt/H3MJsonReader/readResources.h>
#include <h3mtxt/Map/TimedEventBase.h>

namespace h3m::H3MJsonReader_NS
{
  void readTimedEventBase(TimedEventBase& event, const Json::Value& value)
  {
    using Fields = h3m::FieldNames<h3m::TimedEventBase>;
    readField(event.name, value, Fields::kName);
    readField(event.message, value, Fields::kMessage);
    readField(event.resources, value, Fields::kResources);
    readField(event.affected_players, value, Fields::kAffectedPlayers);
    readField(event.applies_to_human, value, Fields::kAppliesToHuman);
    readField(event.applies_to_computer, value, Fields::kAppliesToComputer);
    readField(event.day_of_first_occurence, value, Fields::kDayOfFirstOccurence);
    readField(event.repeat_after_days, value, Fields::kRepeatAfterDays);
    readField(event.unknown, value, Fields::kUnknown);
  }
}
