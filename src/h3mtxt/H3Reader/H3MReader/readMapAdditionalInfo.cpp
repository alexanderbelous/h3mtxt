#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>

namespace h3m
{
  Teams H3MReader::readTeams() const
  {
    Teams teams;
    teams.num_teams = readInt<std::uint8_t>();
    if (teams.num_teams != 0)
    {
      for (std::uint8_t& team : teams.team_for_player.data)
      {
        team = readInt<std::uint8_t>();
      }
    }
    return teams;
  }

  CustomHero H3MReader::readCustomHero() const
  {
    CustomHero custom_hero;
    custom_hero.type = readEnum<HeroType>();
    custom_hero.portrait = readEnum<HeroPortrait>();
    custom_hero.name = readString32();
    custom_hero.can_hire = readEnumBitmask<PlayerColor, 1>();
    return custom_hero;
  }

  Rumor H3MReader::readRumor() const
  {
    Rumor rumor;
    rumor.name = readString32();
    rumor.description = readString32();
    return rumor;
  }

  HeroSettings H3MReader::readHeroSettings() const
  {
    HeroSettings settings;
    if (const Bool has_experience = readBool())
    {
      settings.experience = readInt<std::int32_t>();
    }
    if (const Bool has_secondary_skills = readBool())
    {
      std::vector<SecondarySkill>& secondary_skills = settings.secondary_skills.emplace();
      const std::uint32_t num_secondary_skills = readInt<std::uint32_t>();
      secondary_skills.reserve(num_secondary_skills);
      for (std::uintmax_t i = 0; i < num_secondary_skills; ++i)
      {
        secondary_skills.push_back(readSecondarySkill());
      }
    }
    if (const Bool has_artifacts = readBool())
    {
      settings.artifacts = readHeroArtifacts();
    }
    if (const Bool has_biography = readBool())
    {
      settings.biography = readString32();
    }
    settings.gender = readEnum<Gender>();
    if (const Bool has_spells = readBool())
    {
      settings.spells = readEnumBitmask<SpellType, 9>();
    }
    if (const Bool has_primary_skills = readBool())
    {
      settings.primary_skills = readPrimarySkills();
    }
    return settings;
  }

  MapAdditionalInfo H3MReader::readMapAdditionalInfo() const
  {
    MapAdditionalInfo additional_info;
    additional_info.victory_condition = readVictoryCondition();
    additional_info.loss_condition = readLossCondition();
    additional_info.teams = readTeams();
    additional_info.heroes_availability = readEnumBitmask<HeroType, 20>();
    // Read placeholder heroes.
    const std::uint32_t num_placeholder_heroes = readInt<std::uint32_t>();
    additional_info.placeholder_heroes.reserve(num_placeholder_heroes);
    for (std::uint32_t i = 0; i < num_placeholder_heroes; ++i)
    {
      additional_info.placeholder_heroes.push_back(readEnum<HeroType>());
    }
    // Read custom heroes.
    const std::uint8_t num_custom_heroes = readInt<std::uint8_t>();
    additional_info.custom_heroes.reserve(num_custom_heroes);
    for (std::uint32_t i = 0; i < num_custom_heroes; ++i)
    {
      additional_info.custom_heroes.push_back(readCustomHero());
    }
    // Read reserved data.
    additional_info.reserved = readReservedData<31>();
    additional_info.disabled_artifacts = readEnumBitmask<ArtifactType, 18>();
    additional_info.disabled_spells = readEnumBitmask<SpellType, 9>();
    additional_info.disabled_skills = readEnumBitmask<SecondarySkillType, 4>();
    // Read rumors.
    const std::uint32_t num_rumors = readInt<std::uint32_t>();
    additional_info.rumors.reserve(num_rumors);
    for (std::uint32_t i = 0; i < num_rumors; ++i)
    {
      additional_info.rumors.push_back(readRumor());
    }
    // Read heroes
    for (std::uint32_t i = 0; i < kNumHeroes; ++i)
    {
      if (const Bool has_settings = readBool())
      {
        additional_info.heroes_settings[static_cast<HeroType>(i)] = readHeroSettings();
      }
    }
    return additional_info;
  }
}
