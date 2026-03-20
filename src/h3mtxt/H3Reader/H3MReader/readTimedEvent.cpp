#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/TimedEvent.h>

namespace h3m
{
  TimedEvent H3MReader::readTimedEvent() const
  {
    TimedEvent event;
    event.name = readString32();
    event.message = readString32();
    event.resources = readResources();
    event.affected_players = readEnumBitmask<PlayerColor, 1>();
    event.applies_to_human = readBool();
    event.applies_to_computer = readBool();
    event.day_of_first_occurence = readInt<std::uint16_t>();
    event.repeat_after_days = readInt<std::uint16_t>();
    event.unknown = readReservedData<16>();
    return event;
  }
}
