#include <h3mtxt/H3MWriter/H3Writer.h>
#include <h3mtxt/H3MWriter/Utils.h>
#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>

namespace h3m
{
  // TODO: it's kinda bad that the specialization itself is declared here.
  // Consider unnesting CustomHero, so that it can be forward-declared.
  template<>
  struct H3MWriter<MapAdditionalInfo::CustomHero>
  {
    void operator()(std::ostream& stream, const MapAdditionalInfo::CustomHero& value) const
    {
      writeData(stream, value.type);
      writeData(stream, value.portrait);
      writeData(stream, value.name);
      writeData(stream, value.can_hire);
    }
  };

  void H3MWriter<TeamsInfo>::operator()(std::ostream& stream, const TeamsInfo& teams) const
  {
    writeData(stream, teams.num_teams);
    if (teams.num_teams != 0)
    {
      writeData(stream, teams.team_for_player);
    }
  }

  void H3MWriter<Rumor>::operator()(std::ostream& stream, const Rumor& value) const
  {
    writeData(stream, value.name);
    writeData(stream, value.description);
  }

  void H3MWriter<MapAdditionalInfo>::operator()(std::ostream& stream, const MapAdditionalInfo& value) const
  {
    writeData(stream, value.victory_condition);
    writeData(stream, value.loss_condition);
    writeData(stream, value.teams);
    writeData(stream, value.heroes_availability);
    writeVector<std::uint32_t>(stream, value.placeholder_heroes);
    writeVector<std::uint8_t>(stream, value.custom_heroes);
    writeData(stream, value.reserved);
    writeData(stream, value.disabled_artifacts);
    writeData(stream, value.disabled_spells);
    writeData(stream, value.disabled_skills);
    writeVector<std::uint32_t>(stream, value.rumors);
    // Write heroes' settings.
    for (std::uint8_t hero_idx = 0; hero_idx < kNumHeroes; ++hero_idx)
    {
      const HeroType hero_type = static_cast<HeroType>(hero_idx);
      const bool has_settings = value.heroes_settings.hasSettings(hero_type);
      writeData(stream, has_settings);
      if (has_settings)
      {
        writeData(stream, value.heroes_settings[hero_type]);
      }
    }
  }
}
