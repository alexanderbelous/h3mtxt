#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>

namespace h3m
{
  void H3MWriter::writeData(const CustomHero& value) const
  {
    writeData(value.type);
    writeData(value.portrait);
    writeData(value.name);
    writeData(value.can_hire);
  }

  void H3MWriter::writeData(const TeamsInfo& teams) const
  {
    writeData(teams.num_teams);
    if (teams.num_teams != 0)
    {
      writeData(teams.team_for_player);
    }
  }

  void H3MWriter::writeData(const Rumor& value) const
  {
    writeData(value.name);
    writeData(value.description);
  }

  void H3MWriter::writeData(const MapAdditionalInfo& value) const
  {
    writeData(value.victory_condition);
    writeData(value.loss_condition);
    writeData(value.teams);
    writeData(value.heroes_availability);
    writeData(safeCastVectorSize<std::uint32_t>(value.placeholder_heroes.size()));
    writeSpan(std::span{ value.placeholder_heroes });
    writeData(safeCastVectorSize<std::uint8_t>(value.custom_heroes.size()));
    writeSpan(std::span{ value.custom_heroes });
    writeData(value.reserved);
    writeData(value.disabled_artifacts);
    writeData(value.disabled_spells);
    writeData(value.disabled_skills);
    writeData(safeCastVectorSize<std::uint32_t>(value.rumors.size()));
    writeSpan(std::span{ value.rumors });
    // Write heroes' settings.
    for (std::uint8_t hero_idx = 0; hero_idx < kNumHeroes; ++hero_idx)
    {
      const HeroType hero_type = static_cast<HeroType>(hero_idx);
      const bool has_settings = value.heroes_settings.hasSettings(hero_type);
      writeData(static_cast<Bool>(has_settings));
      if (has_settings)
      {
        writeData(value.heroes_settings[hero_type]);
      }
    }
  }
}
