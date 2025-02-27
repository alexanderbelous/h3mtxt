#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/Map/MapFwd.h>

#include <json/forwards.h>

// API for deserializing H3 data from JSON.
namespace h3m::H3JsonReader_NS
{
  // Template class for deserializing Json::Value as the specified type.
  template<class T, class Enable = void>
  struct JsonReader
  {
    // \param value - input JSON value.
    // \return @value deserialized as an object of type T.
    T operator()(const Json::Value& value) const;
  };

  template<>
  bool JsonReader<bool>::operator()(const Json::Value& value) const;

  template<>
  ArtifactsBitmask JsonReader<ArtifactsBitmask>::operator()(const Json::Value& value) const;

  template<>
  CreatureStack JsonReader<CreatureStack>::operator()(const Json::Value& value) const;

  template<>
  GlobalEvent JsonReader<GlobalEvent>::operator()(const Json::Value& value) const;

  template<>
  Guardians JsonReader<Guardians>::operator()(const Json::Value & value) const;

  template<>
  HeroArtifacts JsonReader<HeroArtifacts>::operator()(const Json::Value& value) const;

  template<>
  HeroSettings JsonReader<HeroSettings>::operator()(const Json::Value & value) const;

  template<>
  HeroesBitmask JsonReader<HeroesBitmask>::operator()(const Json::Value& value) const;

  template<>
  HeroesSettings JsonReader<HeroesSettings>::operator()(const Json::Value& value) const;

  template<>
  LossCondition JsonReader<LossCondition>::operator()(const Json::Value& value) const;

  template<>
  MainTown JsonReader<MainTown>::operator()(const Json::Value& value) const;

  template<>
  Map JsonReader<Map>::operator()(const Json::Value& value) const;

  template<>
  MapAdditionalInfo JsonReader<MapAdditionalInfo>::operator()(const Json::Value& value) const;

  template<>
  MapBasicInfo JsonReader<MapBasicInfo>::operator()(const Json::Value& value) const;

  template<>
  MessageAndTreasure JsonReader<MessageAndTreasure>::operator()(const Json::Value& value) const;

  template<>
  ObjectAttributes JsonReader<ObjectAttributes>::operator()(const Json::Value& value) const;

  template<>
  PlayerSpecs JsonReader<PlayerSpecs>::operator()(const Json::Value & value) const;

  template<>
  PlayersBitmask JsonReader<PlayersBitmask>::operator()(const Json::Value& value) const;

  template<>
  PrimarySkills JsonReader<PrimarySkills>::operator()(const Json::Value& value) const;

  template<>
  Quest JsonReader<Quest>::operator()(const Json::Value& value) const;

  template<>
  Resources JsonReader<Resources>::operator()(const Json::Value& value) const;

  template<>
  ResourcesBitmask JsonReader<ResourcesBitmask>::operator()(const Json::Value& value) const;

  template<>
  Reward JsonReader<Reward>::operator()(const Json::Value& value) const;

  template<>
  Rumor JsonReader<Rumor>::operator()(const Json::Value& value) const;

  template<>
  SecondarySkill JsonReader<SecondarySkill>::operator()(const Json::Value& value) const;

  template<>
  SecondarySkillsBitmask JsonReader<SecondarySkillsBitmask>::operator()(const Json::Value& value) const;

  template<>
  SpellsBitmask JsonReader<SpellsBitmask>::operator()(const Json::Value& value) const;

  template<>
  StartingHero JsonReader<StartingHero>::operator()(const Json::Value& value) const;

  template<>
  TeamsInfo JsonReader<TeamsInfo>::operator()(const Json::Value& value) const;

  template<>
  Tile JsonReader<Tile>::operator()(const Json::Value& value) const;

  template<>
  TownBuildings JsonReader<TownBuildings>::operator()(const Json::Value& value) const;

  template<>
  TownBuildingsBitmask JsonReader<TownBuildingsBitmask>::operator()(const Json::Value& value) const;

  template<>
  TownEvent JsonReader<TownEvent>::operator()(const Json::Value& value) const;

  template<>
  TownsBitmask JsonReader<TownsBitmask>::operator()(const Json::Value& value) const;

  template<>
  VictoryCondition JsonReader<VictoryCondition>::operator()(const Json::Value& value) const;

  ObjectDetailsDataVariant readObjectDetailsDataVariant(const Json::Value& value, MetaObjectType meta_object_type);

  void readTimedEventBase(TimedEventBase& event, const Json::Value& value);
}
