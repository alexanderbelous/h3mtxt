#include <h3mtxt/H3MReader/readTimedEventBase.h>

#include <h3mtxt/H3MReader/readResources.h>
#include <h3mtxt/H3MReader/Utils.h>
#include <h3mtxt/Map/TimedEventBase.h>

namespace h3m
{
  void readTimedEventBase(std::istream& stream, TimedEventBase& event)
  {
    event.name = readString(stream);
    event.message = readString(stream);
    event.resources = readResources<std::int32_t>(stream);
    event.affected_players.bitset = readUint8(stream);
    event.applies_to_human = readBool(stream);
    event.applies_to_computer = readBool(stream);
    event.day_of_first_occurence = readUint<std::uint16_t>(stream);
    event.repeat_after_days = readUint<std::uint8_t>(stream);
    event.unknown = readReservedData<17>(stream);
  }
}
