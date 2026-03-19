#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/HeroSettings.h>

namespace h3m
{
  void H3MWriter::writeData(const HeroSettings& settings) const
  {
    writeData(settings.experience);
    // Write secondary skills.
    writeData(static_cast<Bool>(settings.secondary_skills.has_value()));
    if (settings.secondary_skills)
    {
      writeData(safeCastVectorSize<std::uint32_t>((*settings.secondary_skills).size()));
      writeSpan(std::span{*settings.secondary_skills});
    }
    writeData(settings.artifacts);
    writeData(settings.biography);
    writeData(settings.gender);
    writeData(settings.spells);
    writeData(settings.primary_skills);
  }
}
