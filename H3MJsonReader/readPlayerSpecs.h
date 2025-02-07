#pragma once

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/Map/PlayerSpecs.h>

namespace h3m
{
  // TODO: move to a separate header.
  template<>
  struct JsonReader<TownsBitmask>
  {
    TownsBitmask operator()(const Json::Value& value) const
    {
      TownsBitmask towns_bitmask {};
      towns_bitmask.bitset = fromJson<BitSet<2>>(value);
      return towns_bitmask;
    }
  };

  template<>
  struct JsonReader<MainTown>
  {
    MainTown operator()(const Json::Value& value) const
    {
      MainTown main_town {};
      main_town.generate_hero = readField<Bool>(value, "generate_hero");
      main_town.town_type = readField<TownType>(value, "town_type");
      main_town.x = readField<std::uint8_t>(value, "x");
      main_town.y = readField<std::uint8_t>(value, "y");
      main_town.z = readField<std::uint8_t>(value, "z");
      return main_town;
    }
  };

  template<>
  struct JsonReader<StartingHero>
  {
    StartingHero operator()(const Json::Value& value) const
    {
      StartingHero hero {};
      hero.is_random = readField<Bool>(value, "is_random");
      hero.type = readField<HeroType>(value, "type");
      hero.portrait = readField<HeroPortrait>(value, "portrait");
      hero.name = readField<std::string>(value, "name");
      return hero;
    }
  };

  template<>
  struct JsonReader<AdditionalPlayerInfo::HeroInfo>
  {
    AdditionalPlayerInfo::HeroInfo operator()(const Json::Value& value) const
    {
      AdditionalPlayerInfo::HeroInfo info{};
      info.type = readField<HeroType>(value, "type");
      info.name = readField<std::string>(value, "name");
      return info;
    }
  };

  template<>
  struct JsonReader<AdditionalPlayerInfo>
  {
    AdditionalPlayerInfo operator()(const Json::Value& value) const
    {
      AdditionalPlayerInfo info {};
      info.num_placeholder_heroes = readField<std::uint8_t>(value, "num_placeholder_heroes");
      info.heroes = readField<std::vector<AdditionalPlayerInfo::HeroInfo>>(value, "heroes");
      return info;
    }
  };

  template<>
  struct JsonReader<PlayerSpecs>
  {
    PlayerSpecs operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<PlayerSpecs>;
      PlayerSpecs player {};
      readField(player.can_be_human, value, Fields::kCanBeHuman);
      readField(player.can_be_computer, value, Fields::kCanBeComputer);
      readField(player.behavior, value, Fields::kBehavior);
      readField(player.customized_alignments, value, Fields::kCustomizedAlignments);
      readField(player.allowed_alignments, value, Fields::kAllowedAlignments);
      readField(player.random_town, value, Fields::kRandomTown);
      readOptionalField(player.main_town, value, Fields::kMainTown);
      readField(player.starting_hero, value, Fields::kStartingHero);
      if (shouldHaveAdditionalPlayerInfo(player))
      {
        readField(player.additional_info, value, Fields::kAdditionalInfo);
      }
      return player;
    }
  };
}
