#pragma once

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBaseFwd.h>
#include <h3mtxt/Map/MapFwd.h>

// API for deserializing H3M data from JSON.
namespace h3m::H3JsonReader_NS
{
  template<>
  Coordinates JsonReader<Coordinates>::operator()(const Json::Value& value) const;

  template<>
  CreatureStack JsonReader<CreatureStack>::operator()(const Json::Value& value) const;

  template<>
  CustomHero JsonReader<CustomHero>::operator()(const Json::Value& value) const;

  template<>
  Guardians JsonReader<Guardians>::operator()(const Json::Value & value) const;

  template<>
  HeroArtifacts JsonReader<HeroArtifacts>::operator()(const Json::Value& value) const;

  template<>
  HeroSettings JsonReader<HeroSettings>::operator()(const Json::Value & value) const;

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
  ObjectTemplate JsonReader<ObjectTemplate>::operator()(const Json::Value& value) const;

  template<>
  PlayerSpecs JsonReader<PlayerSpecs>::operator()(const Json::Value & value) const;

  template<>
  PrimarySkills JsonReader<PrimarySkills>::operator()(const Json::Value& value) const;

  template<>
  Quest JsonReader<Quest>::operator()(const Json::Value& value) const;

  template<>
  Reward JsonReader<Reward>::operator()(const Json::Value& value) const;

  template<>
  Rumor JsonReader<Rumor>::operator()(const Json::Value& value) const;

  template<>
  SecondarySkill JsonReader<SecondarySkill>::operator()(const Json::Value& value) const;

  template<>
  SpriteTilesBitmask JsonReader<SpriteTilesBitmask>::operator()(const Json::Value& value) const;

  template<>
  StartingHero JsonReader<StartingHero>::operator()(const Json::Value& value) const;

  template<>
  TeamsInfo JsonReader<TeamsInfo>::operator()(const Json::Value& value) const;

  // Full specialization for TerrainsBitmask. The template version from Utils.h
  // is not used here because TerrainsBitmask is currently serialized as an array of bytes.
  template<>
  TerrainsBitmask JsonReader<TerrainsBitmask>::operator()(const Json::Value& value) const;

  template<>
  Tile JsonReader<Tile>::operator()(const Json::Value& value) const;

  template<>
  TimedEvent JsonReader<TimedEvent>::operator()(const Json::Value& value) const;

  template<>
  TownBuildings JsonReader<TownBuildings>::operator()(const Json::Value& value) const;

  template<>
  TownEvent JsonReader<TownEvent>::operator()(const Json::Value& value) const;

  template<>
  VictoryCondition JsonReader<VictoryCondition>::operator()(const Json::Value& value) const;

  ObjectPropertiesVariant readObjectPropertiesVariant(const Json::Value& value, ObjectPropertiesType object_properties_type);
}
