#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/H3Writer/Utils.h>
#include <h3mtxt/Map/HeroSettings.h>

namespace h3m
{
  void H3Writer<HeroSettings>::operator()(std::ostream& stream, const HeroSettings& settings) const
  {
    writeData(stream, settings.experience);
    // Write secondary skills.
    writeData(stream, settings.secondary_skills.has_value());
    if (settings.secondary_skills)
    {
      writeVector<std::uint32_t>(stream, *settings.secondary_skills);
    }
    writeData(stream, settings.artifacts);
    writeData(stream, settings.biography);
    writeData(stream, settings.gender);
    writeData(stream, settings.spells);
    writeData(stream, settings.primary_skills);
  }
}
