#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>

namespace h3m::H3JsonReader_NS
{
  CustomHero JsonReader<CustomHero>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<CustomHero>;
    CustomHero hero;
    hero.type = readField<HeroType>(value, Fields::kType);
    hero.portrait = readField<HeroPortrait>(value, Fields::kPortrait);
    hero.name = readField<std::string>(value, Fields::kName);
    hero.can_hire = readField<PlayersBitmask>(value, Fields::kCanHire);
    return hero;
  }

  TeamsInfo JsonReader<TeamsInfo>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<TeamsInfo>;
    TeamsInfo info;
    readField(info.num_teams, value, Fields::kNumTeams);
    if (info.num_teams != 0)
    {
      readField(info.team_for_player, value, Fields::kTeamForPlayer);
    }
    return info;
  }

  Rumor JsonReader<Rumor>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<Rumor>;
    Rumor rumor;
    readField(rumor.name, value, Fields::kName);
    readField(rumor.description, value, Fields::kDescription);
    return rumor;
  }

  HeroesSettings JsonReader<HeroesSettings>::operator()(const Json::Value& value) const
  {
    if (!value.isArray())
    {
      throw std::runtime_error("JsonReader<HeroesSettings>(): expected array, got " + value.toStyledString());
    }
    HeroesSettings heroes_settings;
    for (const Json::Value& keyval : value)
    {
      const HeroType hero = readField<HeroType>(keyval, "hero");
      HeroSettings settings = readField<HeroSettings>(keyval, "settings");
      heroes_settings[hero] = std::move(settings);
    }
    return heroes_settings;
  }

  MapAdditionalInfo JsonReader<MapAdditionalInfo>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<MapAdditionalInfo>;

    MapAdditionalInfo info;
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
