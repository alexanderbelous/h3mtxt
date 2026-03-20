#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/TimedEvent.h>

namespace h3m
{
  void H3MWriter::writeData(const TimedEvent& event) const
  {
    writeData(event.name);
    writeData(event.message);
    writeData(event.resources);
    writeData(event.affected_players);
    writeData(event.applies_to_human);
    writeData(event.applies_to_computer);
    writeData(event.day_of_first_occurence);
    writeData(event.repeat_after_days);
    writeData(event.unknown);
  }
}
