#pragma once

#include <h3mtxt/Map/TimedEventBase.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>
#include <h3mtxt/H3MTxtWriter/writePlayersBitmask.h>
#include <h3mtxt/H3MTxtWriter/writeResources.h>

namespace Util_NS
{
  void printTimedEventBase(FieldsWriter& out, const h3m::TimedEventBase& event)
  {
    out.writeField("name", event.name);
    out.writeField("message", event.message);
    out.writeField("resources", event.resources);
    out.writeField("affected_players", event.affected_players);
    out.writeField("applies_to_human", event.applies_to_human);
    out.writeField("applies_to_computer", event.applies_to_computer);
    out.writeField("day_of_first_occurence", event.day_of_first_occurence);
    out.writeField("repeat_after_days", event.repeat_after_days);
    out.writeField("unknown", event.unknown);
  }
}
