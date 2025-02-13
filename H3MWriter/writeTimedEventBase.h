#pragma once

#include <h3mtxt/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/TimedEventBase.h>

namespace h3m
{
  // TODO: consider moving the implementation to .cpp.
  inline void writeTimedEventBase(std::ostream& stream, const TimedEventBase& event)
  {
    writeData(stream, event.name);
    writeData(stream, event.message);
    writeData(stream, event.resources);
    writeData(stream, event.affected_players);
    writeData(stream, event.applies_to_human);
    writeData(stream, event.applies_to_computer);
    writeData(stream, event.day_of_first_occurence);
    writeData(stream, event.repeat_after_days);
    writeData(stream, event.unknown);
  }
}