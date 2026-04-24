#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/Constants/Constants.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>

namespace h3json
{
  h3m::CustomHero JsonReader<h3m::CustomHero>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::CustomHero>;
    h3m::CustomHero hero;
    readField(hero.type, value, Fields::kType);
    readField(hero.portrait, value, Fields::kPortrait);
    readField(hero.name, value, Fields::kName);
    readField(hero.can_hire, value, Fields::kCanHire);
    return hero;
  }

  h3m::Teams JsonReader<h3m::Teams>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::Teams>;
    h3m::Teams teams;
    readField(teams.num_teams, value, Fields::kNumTeams);
    if (teams.num_teams != 0)
    {
      readField(teams.team_for_player, value, Fields::kTeamForPlayer);
    }
    return teams;
  }

  h3m::Rumor JsonReader<h3m::Rumor>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::Rumor>;
    h3m::Rumor rumor;
    readField(rumor.name, value, Fields::kName);
    readField(rumor.description, value, Fields::kDescription);
    return rumor;
  }

  h3m::HeroesSettings JsonReader<h3m::HeroesSettings>::operator()(const Json::Value& value) const
  {
    constexpr std::span<const std::string_view, h3m::kNumHeroes> kFieldNames =
      getEnumFieldNames<h3m::HeroType, h3m::kNumHeroes>();

    h3m::HeroesSettings heroes_settings;
    for (std::size_t hero_idx = 0; hero_idx < h3m::kNumHeroes; ++hero_idx)
    {
      if (const Json::Value* field = findJsonField(value, kFieldNames[hero_idx]))
      {
        const h3m::HeroType hero = static_cast<h3m::HeroType>(hero_idx);
        heroes_settings[hero] = fromJson<h3m::HeroSettings>(*field);
      }
    }
    return heroes_settings;
  }

  h3m::MapAdditionalInfo JsonReader<h3m::MapAdditionalInfo>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::MapAdditionalInfo>;

    h3m::MapAdditionalInfo info;
    readField(info.victory_condition, value, Fields::kVictoryCondition);
    readField(info.loss_condition, value, Fields::kLossCondition);
    readField(info.teams, value, Fields::kTeams);
    readField(info.heroes_availability, value, Fields::kHeroesAvailability);
    readField(info.placeholder_heroes, value, Fields::kPlaceholderHeroes);
    readField(info.custom_heroes, value, Fields::kCustomHeroes);
    readField(info.reserved, value, Fields::kReserved);
    readField(info.disabled_artifacts, value, Fields::kDisabledArtifacts);
    readField(info.disabled_spells, value, Fields::kDisabledSpells);
    readField(info.disabled_skills, value, Fields::kDisabledSkills);
    readField(info.rumors, value, Fields::kRumors);
    readField(info.heroes_settings, value, Fields::kHeroesSettings);
    return info;
  }
}
