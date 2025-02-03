#pragma once

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
      PlayerSpecs player {};
      player.can_be_human = readField<Bool>(value, "can_be_human");
      player.can_be_computer = readField<Bool>(value, "can_be_computer");
      player.behavior = readField<PlayerBehavior>(value, "behavior");
      player.customized_alignments = readField<Bool>(value, "customized_alignments");
      player.allowed_alignments = readField<TownsBitmask>(value, "allowed_alignments");
      player.random_town = readField<Bool>(value, "random_town");
      player.main_town = readOptionalField<MainTown>(value, "main_town");
      player.starting_hero = readField<StartingHero>(value, "starting_hero");
      if (shouldHaveAdditionalPlayerInfo(player))
      {
        player.additional_info = readField<AdditionalPlayerInfo>(value, "additional_info");
      }
      return player;
    }
  };
}
