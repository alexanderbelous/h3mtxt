#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/Map/TimedEvent.h>

namespace h3m::H3Reader_NS
{
  TimedEvent readTimedEvent(std::istream& stream)
  {
    TimedEvent event;
    event.name = readString(stream);
    event.message = readString(stream);
    event.resources = readResources(stream);
    event.affected_players = readEnumBitmask<PlayerColor, 1>(stream);
    event.applies_to_human = readBool(stream);
    event.applies_to_computer = readBool(stream);
    event.day_of_first_occurence = readInt<std::uint16_t>(stream);
    event.repeat_after_days = readInt<std::uint16_t>(stream);
    event.unknown = readReservedData<16>(stream);
    return event;
  }
}
