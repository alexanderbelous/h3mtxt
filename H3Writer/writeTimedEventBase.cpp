#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/H3Writer/Utils.h>
#include <h3mtxt/Map/TimedEventBase.h>

namespace h3m::H3Writer_NS
{
  void writeTimedEventBase(std::ostream& stream, const TimedEventBase& event)
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