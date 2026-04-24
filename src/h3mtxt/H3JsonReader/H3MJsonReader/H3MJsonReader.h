#pragma once

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBaseFwd.h>
#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/QuestType.h>
#include <h3mtxt/Map/Constants/RewardType.h>

// API for deserializing H3M data from JSON.
namespace h3json
{
  template<>
  h3m::Coordinates JsonReader<h3m::Coordinates>::operator()(const Json::Value& value) const;

  template<>
  h3m::CreatureStack JsonReader<h3m::CreatureStack>::operator()(const Json::Value& value) const;

  template<>
  h3m::CustomHero JsonReader<h3m::CustomHero>::operator()(const Json::Value& value) const;

  template<>
  h3m::Guardians JsonReader<h3m::Guardians>::operator()(const Json::Value & value) const;

  template<>
  h3m::HeroArtifacts JsonReader<h3m::HeroArtifacts>::operator()(const Json::Value& value) const;

  template<>
  h3m::HeroSettings JsonReader<h3m::HeroSettings>::operator()(const Json::Value & value) const;

  template<>
  h3m::HeroesSettings JsonReader<h3m::HeroesSettings>::operator()(const Json::Value& value) const;

  template<>
  h3m::LossCondition JsonReader<h3m::LossCondition>::operator()(const Json::Value& value) const;

  template<>
  h3m::MainTown JsonReader<h3m::MainTown>::operator()(const Json::Value& value) const;

  template<>
  h3m::Map JsonReader<h3m::Map>::operator()(const Json::Value& value) const;

  template<>
  h3m::MapAdditionalInfo JsonReader<h3m::MapAdditionalInfo>::operator()(const Json::Value& value) const;

  template<>
  h3m::MapBasicInfo JsonReader<h3m::MapBasicInfo>::operator()(const Json::Value& value) const;

  template<>
  h3m::MessageAndTreasure JsonReader<h3m::MessageAndTreasure>::operator()(const Json::Value& value) const;

  template<>
  h3m::ObjectTemplate JsonReader<h3m::ObjectTemplate>::operator()(const Json::Value& value) const;

  template<>
  h3m::PlayerSpecs JsonReader<h3m::PlayerSpecs>::operator()(const Json::Value & value) const;

  template<>
  h3m::PrimarySkills JsonReader<h3m::PrimarySkills>::operator()(const Json::Value& value) const;

  template<>
  h3m::Quest JsonReader<h3m::Quest>::operator()(const Json::Value& value) const;

  template<>
  h3m::QuestDetails<h3m::QuestType::None>
  JsonReader<h3m::QuestDetails<h3m::QuestType::None>>::operator()(const Json::Value& value) const;

  template<>
  h3m::QuestDetails<h3m::QuestType::Level>
  JsonReader<h3m::QuestDetails<h3m::QuestType::Level>>::operator()(const Json::Value& value) const;

  template<>
  h3m::QuestDetails<h3m::QuestType::PrimarySkills>
  JsonReader<h3m::QuestDetails<h3m::QuestType::PrimarySkills>>::operator()(const Json::Value& value) const;

  template<>
  h3m::QuestDetails<h3m::QuestType::DefeatHero>
  JsonReader<h3m::QuestDetails<h3m::QuestType::DefeatHero>>::operator()(const Json::Value& value) const;

  template<>
  h3m::QuestDetails<h3m::QuestType::DefeatMonster>
  JsonReader<h3m::QuestDetails<h3m::QuestType::DefeatMonster>>::operator()(const Json::Value& value) const;

  template<>
  h3m::QuestDetails<h3m::QuestType::Artifacts>
  JsonReader<h3m::QuestDetails<h3m::QuestType::Artifacts>>::operator()(const Json::Value& value) const;

  template<>
  h3m::QuestDetails<h3m::QuestType::Creatures>
  JsonReader<h3m::QuestDetails<h3m::QuestType::Creatures>>::operator()(const Json::Value& value) const;

  template<>
  h3m::QuestDetails<h3m::QuestType::Resources>
  JsonReader<h3m::QuestDetails<h3m::QuestType::Resources>>::operator()(const Json::Value& value) const;

  template<>
  h3m::QuestDetails<h3m::QuestType::BeHero>
  JsonReader<h3m::QuestDetails<h3m::QuestType::BeHero>>::operator()(const Json::Value& value) const;

  template<>
  h3m::QuestDetails<h3m::QuestType::BePlayer>
  JsonReader<h3m::QuestDetails<h3m::QuestType::BePlayer>>::operator()(const Json::Value& value) const;

  template<>
  h3m::Reward JsonReader<h3m::Reward>::operator()(const Json::Value& value) const;

  template<>
  h3m::RewardDetails<h3m::RewardType::None>
  JsonReader<h3m::RewardDetails<h3m::RewardType::None>>::operator()(const Json::Value& value) const;

  template<>
  h3m::RewardDetails<h3m::RewardType::Experience>
  JsonReader<h3m::RewardDetails<h3m::RewardType::Experience>>::operator()(const Json::Value& value) const;

  template<>
  h3m::RewardDetails<h3m::RewardType::SpellPoints>
  JsonReader<h3m::RewardDetails<h3m::RewardType::SpellPoints>>::operator()(const Json::Value& value) const;

  template<>
  h3m::RewardDetails<h3m::RewardType::Morale>
  JsonReader<h3m::RewardDetails<h3m::RewardType::Morale>>::operator()(const Json::Value& value) const;

  template<>
  h3m::RewardDetails<h3m::RewardType::Luck>
  JsonReader<h3m::RewardDetails<h3m::RewardType::Luck>>::operator()(const Json::Value& value) const;

  template<>
  h3m::RewardDetails<h3m::RewardType::Resource>
  JsonReader<h3m::RewardDetails<h3m::RewardType::Resource>>::operator()(const Json::Value& value) const;

  template<>
  h3m::RewardDetails<h3m::RewardType::PrimarySkill>
  JsonReader<h3m::RewardDetails<h3m::RewardType::PrimarySkill>>::operator()(const Json::Value& value) const;

  template<>
  h3m::RewardDetails<h3m::RewardType::SecondarySkill>
  JsonReader<h3m::RewardDetails<h3m::RewardType::SecondarySkill>>::operator()(const Json::Value& value) const;

  template<>
  h3m::RewardDetails<h3m::RewardType::Artifact>
  JsonReader<h3m::RewardDetails<h3m::RewardType::Artifact>>::operator()(const Json::Value& value) const;

  template<>
  h3m::RewardDetails<h3m::RewardType::Spell>
  JsonReader<h3m::RewardDetails<h3m::RewardType::Spell>>::operator()(const Json::Value& value) const;

  template<>
  h3m::RewardDetails<h3m::RewardType::Creature>
  JsonReader<h3m::RewardDetails<h3m::RewardType::Creature>>::operator()(const Json::Value& value) const;

  template<>
  h3m::Rumor JsonReader<h3m::Rumor>::operator()(const Json::Value& value) const;

  template<>
  h3m::SecondarySkill JsonReader<h3m::SecondarySkill>::operator()(const Json::Value& value) const;

  template<>
  h3m::SpriteTilesBitmask JsonReader<h3m::SpriteTilesBitmask>::operator()(const Json::Value& value) const;

  template<>
  h3m::StartingHero JsonReader<h3m::StartingHero>::operator()(const Json::Value& value) const;

  template<>
  h3m::Teams JsonReader<h3m::Teams>::operator()(const Json::Value& value) const;

  // Full specialization for TerrainsBitmask. The template version from Utils.h
  // is not used here because TerrainsBitmask is currently serialized as an array of bytes.
  template<>
  h3m::TerrainsBitmask JsonReader<h3m::TerrainsBitmask>::operator()(const Json::Value& value) const;

  template<>
  h3m::Tile JsonReader<h3m::Tile>::operator()(const Json::Value& value) const;

  template<>
  h3m::TimedEvent JsonReader<h3m::TimedEvent>::operator()(const Json::Value& value) const;

  template<>
  h3m::TownBuildings JsonReader<h3m::TownBuildings>::operator()(const Json::Value& value) const;

  template<>
  h3m::TownEvent JsonReader<h3m::TownEvent>::operator()(const Json::Value& value) const;

  template<>
  h3m::VictoryCondition JsonReader<h3m::VictoryCondition>::operator()(const Json::Value& value) const;

  h3m::ObjectPropertiesVariant readObjectPropertiesVariant(const Json::Value& value,
                                                           h3m::ObjectPropertiesType object_properties_type);
}
