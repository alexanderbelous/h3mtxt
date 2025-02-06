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
      TeamsInfo info;
      info.num_teams = readField<std::uint8_t>(value, "num_teams");
      if (info.num_teams != 0)
      {
        info.team_for_player = readField<std::array<std::uint8_t, 8>>(value, "team_for_player");
      }
      return info;
    }
  };

  template<>
  struct JsonReader<Rumor>
  {
    Rumor operator()(const Json::Value& value) const
    {
      Rumor rumor;
      rumor.name = readField<std::string>(value, "name");
      rumor.description = readField<std::string>(value, "description");
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
      info.victory_condition = readField<VictoryCondition>(value, Fields::kVictoryCondition);
      info.loss_condition = readField<LossCondition>(value, Fields::kLossCondition);
      info.teams = readField<TeamsInfo>(value, Fields::kTeams);
      info.heroes_availability.data = readField<BitSet<20>>(value, Fields::kHeroesAvailability);
      info.placeholder_heroes = readField<std::vector<HeroType>>(value, Fields::kPlaceholderHeroes);
      info.custom_heroes = readField<std::vector<MapAdditionalInfo::CustomHero>>(value, Fields::kCustomHeroes);
      info.reserved = readField<ReservedData<31>>(value, Fields::kReserved);
      info.artifacts_nonavailability = readField<BitSet<18>>(value, Fields::kArtifactsNonavailability);
      info.disabled_spells.bitset = readField<BitSet<9>>(value, Fields::kDisabledSpells);
      info.disabled_skills = readField<SecondarySkillsBitmask>(value, Fields::kDisabledSkills);
      info.rumors = readField<std::vector<Rumor>>(value, Fields::kRumors);
      info.heroes_settings = readField<HeroesSettings>(value, Fields::kHeroesSettings);
      return info;
    }
  };
}
