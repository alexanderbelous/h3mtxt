#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/SavedGame/EventBase.h>

namespace h3svg
{
  void H3SVGWriter::writeData(const Troops& troops) const
  {
    writeData(troops.creature_types);
    writeData(troops.creature_counts);
  }

  void H3SVGWriter::writeData(const Guardians& guardians) const
  {
    writeString16(guardians.message);
    writeData(guardians.creatures);
  }

  void H3SVGWriter::writeData(const EventBase& event) const
  {
    writeData(event.guardians);
    writeData(event.experience);
    writeData(event.spell_points);
    writeData(event.morale);
    writeData(event.luck);
    writeData(event.resources);
    writeData(event.primary_skills);
    writeVector<std::uint8_t>(std::span{ event.secondary_skills });
    writeVector<std::uint8_t>(std::span{ event.artifacts });
    writeVector<std::uint8_t>(std::span{ event.spells });
    writeVector<std::uint8_t>(std::span{ event.creatures });
  }
}
