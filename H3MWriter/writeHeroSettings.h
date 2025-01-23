#pragma once

#include <h3mtxt/H3MWriter/H3MWriter.h>
#include <h3mtxt/H3MWriter/writeHeroArtifacts.h>
#include <h3mtxt/H3MWriter/writePrimarySkills.h>
#include <h3mtxt/H3MWriter/writeSecondarySkill.h>
#include <h3mtxt/Map/HeroSettings.h>

namespace h3m
{
  template<>
  struct H3MWriter<HeroSettings>
  {
    void operator()(std::ostream& stream, const HeroSettings& settings) const
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
  };
}
