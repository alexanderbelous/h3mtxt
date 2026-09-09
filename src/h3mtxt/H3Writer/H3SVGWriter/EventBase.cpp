#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/SavedGame/EventBase.h>

namespace h3svg
{
  void H3SVGWriter::writeData(const EventBase& event) const
  {
    writeData(event.guardians);
    writeData(event.experience);
    writeData(event.spell_points);
    writeData(event.morale);
    writeData(event.luck);
    writeData(event.resources);
    writeData(event.primary_skills);
    writeData(safeCastVectorSize<std::uint8_t>(event.secondary_skills.size()));
    writeSpan(std::span{ event.secondary_skills });
    writeData(safeCastVectorSize<std::uint8_t>(event.artifacts.size()));
    writeSpan(std::span{ event.artifacts });
    writeData(safeCastVectorSize<std::uint8_t>(event.spells.size()));
    writeSpan(std::span{ event.spells });
    writeData(safeCastVectorSize<std::uint8_t>(event.creatures.size()));
    writeSpan(std::span{ event.creatures });
  }
}
