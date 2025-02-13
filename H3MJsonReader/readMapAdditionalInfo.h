#pragma once

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/H3MJsonReader/readHeroSettings.h>
#include <h3mtxt/H3MJsonReader/readLossCondition.h>
#include <h3mtxt/H3MJsonReader/readPlayersBitmask.h>
#include <h3mtxt/H3MJsonReader/readSecondarySkillsBitmask.h>
#include <h3mtxt/H3MJsonReader/readVictoryCondition.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>

namespace h3m
{
  template<>
  struct JsonReader<TeamsInfo>
  {
    TeamsInfo operator()(const Json::Value& value) const
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
  };

  template<>
  struct JsonReader<Rumor>
  {
    Rumor operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<Rumor>;
      Rumor rumor;
      readField(rumor.name, value, Fields::kName);
      readField(rumor.description, value, Fields::kDescription);
      return rumor;
    }
  };

  template<>
  struct JsonReader<MapAdditionalInfo::CustomHero>
  {
    MapAdditionalInfo::CustomHero operator()(const Json::Value& value) const
    {
      MapAdditionalInfo::CustomHero hero;
      hero.type = readField<HeroType>(value, "type");
      hero.portrait = readField<HeroPortrait>(value, "portrait");
      hero.name = readField<std::string>(value, "name");
      hero.can_hire = readField<PlayersBitmask>(value, "can_hire");
      return hero;
    }
  };

  template<>
  struct JsonReader<HeroesSettings>
  {
    HeroesSettings operator()(const Json::Value& value) const
    {
      if (!value.isArray())
      {
        throw std::runtime_error("JsonReader<HeroesSettings>(): expected array, got " + value.toStyledString());
      }
      HeroesSettings heroes_settings;
      for (const Json::Value& keyval : value)
      {
        // TODO: rename "key" and "value" to "hero" and "settings".
        const HeroType hero = readField<HeroType>(keyval, "key");
        HeroSettings settings = readField<HeroSettings>(keyval, "value");
        heroes_settings[hero] = std::move(settings);
      }
      return heroes_settings;
    }
  };

  template<>
  struct JsonReader<MapAdditionalInfo>
  {
    MapAdditionalInfo operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<MapAdditionalInfo>;

      MapAdditionalInfo info;
      readField(info.victory_condition, value, Fields::kVictoryCondition);
      readField(info.loss_condition, value, Fields::kLossCondition);
      readField(info.teams, value, Fields::kTeams);
      readField(info.heroes_availability.data, value, Fields::kHeroesAvailability);
      readField(info.placeholder_heroes, value, Fields::kPlaceholderHeroes);
      readField(info.custom_heroes, value, Fields::kCustomHeroes);
      readField(info.reserved, value, Fields::kReserved);
      readField(info.artifacts_nonavailability, value, Fields::kArtifactsNonavailability);
      readField(info.disabled_spells.bitset, value, Fields::kDisabledSpells);
      readField(info.disabled_skills, value, Fields::kDisabledSkills);
      readField(info.rumors, value, Fields::kRumors);
      readField(info.heroes_settings, value, Fields::kHeroesSettings);
      return info;
    }
  };
}
