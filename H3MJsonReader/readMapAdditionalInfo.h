#pragma once

#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/H3MJsonReader/readLossCondition.h>
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
      // TODO: read as as object with 8 boolean fields.
      //hero.can_hire.bitset = readField<std::uint8_t>(value, "can_hire");
      return hero;
    }
  };

  template<>
  struct JsonReader<MapAdditionalInfo>
  {
    MapAdditionalInfo operator()(const Json::Value& value) const
    {
      MapAdditionalInfo info;
      info.victory_condition = readField<VictoryCondition>(value, "victory_condition");
      info.loss_condition = readField<LossCondition>(value, "loss_condition");
      info.teams = readField<TeamsInfo>(value, "teams");
      info.heroes_availability.data = readField<BitSet<20>>(value, "heroes_availability");
      info.placeholder_heroes = readField<std::vector<HeroType>>(value, "placeholder_heroes");
      info.custom_heroes = readField<std::vector<MapAdditionalInfo::CustomHero>>(value, "custom_heroes");
      info.reserved = readField<ReservedData<31>>(value, "reserved");
      info.artifacts_nonavailability = readField<BitSet<18>>(value, "artifacts_nonavailability");
      info.disabled_spells.bitset = readField<BitSet<9>>(value, "disabled_spells");
      info.rumors = readField<std::vector<Rumor>>(value, "rumors");
      // TODO: add the rest
      return info;
    }
  };
}
