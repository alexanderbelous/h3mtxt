#pragma once

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBaseFwd.h>
#include <h3mtxt/Map/Constants/LossConditionType.h>
#include <h3mtxt/Map/Constants/QuestType.h>
#include <h3mtxt/SavedGame/SavedGameFwd.h>

// API for deserializing H3SVG data from JSON.
namespace h3json
{
  template<>
  h3svg::Artifact
  JsonReader<h3svg::Artifact>::operator()(const Json::Value& value) const;

  template<>
  h3svg::ArtifactMerchants
  JsonReader<h3svg::ArtifactMerchants>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Boat
  JsonReader<h3svg::Boat>::operator()(const Json::Value& value) const;

  template<>
  h3svg::CampaignInfo
  JsonReader<h3svg::CampaignInfo>::operator()(const Json::Value& value) const;

  template<>
  h3svg::CoordinatesPacked
  JsonReader<h3svg::CoordinatesPacked>::operator()(const Json::Value& value) const;

  template<>
  h3svg::CreatureBank
  JsonReader<h3svg::CreatureBank>::operator()(const Json::Value& value) const;

  template<>
  h3svg::CrossoverInfo
  JsonReader<h3svg::CrossoverInfo>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Date
  JsonReader<h3svg::Date>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Dwelling
  JsonReader<h3svg::Dwelling>::operator()(const Json::Value& value) const;

  template<>
  h3svg::EventBase
  JsonReader<h3svg::EventBase>::operator()(const Json::Value& value) const;

  // Defined in Utils.h.
  template<std::size_t N>
  struct JsonReader<h3svg::FixedLengthString<N>>
  {
    h3svg::FixedLengthString<N> operator()(const Json::Value& value) const;
  };

  template<>
  h3svg::Garrison
  JsonReader<h3svg::Garrison>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Guardians
  JsonReader<h3svg::Guardians>::operator()(const Json::Value& value) const;

  template<>
  h3svg::HeroArtifact
  JsonReader<h3svg::HeroArtifact>::operator()(const Json::Value& value) const;

  template<>
  h3svg::HeroArtifacts
  JsonReader<h3svg::HeroArtifacts>::operator()(const Json::Value& value) const;

  template<>
  h3svg::LossCondition
  JsonReader<h3svg::LossCondition>::operator()(const Json::Value& value) const;

  template<h3svg::LossConditionType T>
  struct JsonReader<h3svg::LossConditionDetails<T>>
  {
    h3svg::LossConditionDetails<T> operator()(const Json::Value& value) const;
  };

  template<>
  h3svg::LossConditionDetails<h3svg::LossConditionType::LoseHero>
  JsonReader<h3svg::LossConditionDetails<h3svg::LossConditionType::LoseHero>>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Mine
  JsonReader<h3svg::Mine>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Monster
  JsonReader<h3svg::Monster>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Obelisk
  JsonReader<h3svg::Obelisk>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Object
  JsonReader<h3svg::Object>::operator()(const Json::Value& value) const;

  template<>
  h3svg::ObjectPropertiesTables
  JsonReader<h3svg::ObjectPropertiesTables>::operator()(const Json::Value& value) const;

  template<>
  h3svg::ObjectTemplate
  JsonReader<h3svg::ObjectTemplate>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Player
  JsonReader<h3svg::Player>::operator()(const Json::Value& value) const;

  template<>
  h3svg::PlayerSpecs
  JsonReader<h3svg::PlayerSpecs>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Quest
  JsonReader<h3svg::Quest>::operator()(const Json::Value& value) const;

  template<h3svg::QuestType T>
  struct JsonReader<h3svg::QuestDetails<T>>
  {
    h3svg::QuestDetails<T> operator()(const Json::Value& value) const;
  };

  template<>
  h3svg::QuestDetails<h3svg::QuestType::Level>
  JsonReader<h3svg::QuestDetails<h3svg::QuestType::Level>>::operator()(const Json::Value& value) const;

  template<>
  h3svg::QuestDetails<h3svg::QuestType::DefeatHero>
  JsonReader<h3svg::QuestDetails<h3svg::QuestType::DefeatHero>>::operator()(const Json::Value& value) const;

  template<>
  h3svg::QuestDetails<h3svg::QuestType::DefeatMonster>
  JsonReader<h3svg::QuestDetails<h3svg::QuestType::DefeatMonster>>::operator()(const Json::Value& value) const;

  template<>
  h3svg::QuestDetails<h3svg::QuestType::Creatures>
  JsonReader<h3svg::QuestDetails<h3svg::QuestType::Creatures>>::operator()(const Json::Value& value) const;

  template<>
  h3svg::QuestDetails<h3svg::QuestType::BeHero>
  JsonReader<h3svg::QuestDetails<h3svg::QuestType::BeHero>>::operator()(const Json::Value& value) const;

  template<>
  h3svg::QuestGuard
  JsonReader<h3svg::QuestGuard>::operator()(const Json::Value& value) const;

  template<>
  h3svg::RegionInfo
  JsonReader<h3svg::RegionInfo>::operator()(const Json::Value& value) const;

  template<>
  h3svg::ReplayEvent
  JsonReader<h3svg::ReplayEvent>::operator()(const Json::Value& value) const;

  template<h3svg::ReplayEventType T>
  struct JsonReader<h3svg::ReplayEventDetails<T>>
  {
    // Defined in ReplayEvent.cpp.
    // Template instantiations are provided for all valid ReplayEventTypes.
    h3svg::ReplayEventDetails<T> operator()(const Json::Value& value) const;
  };

  template<>
  h3svg::Reward
  JsonReader<h3svg::Reward>::operator()(const Json::Value& value) const;

  template<h3svg::RewardType T>
  struct JsonReader<h3svg::RewardDetails<T>>
  {
    // Defined in Reward.cpp.
    // Template instantiations are provided for all valid RewardTypes.
    h3svg::RewardDetails<T> operator()(const Json::Value& value) const;
  };

  template<>
  h3svg::Rumor
  JsonReader<h3svg::Rumor>::operator()(const Json::Value& value) const;

  template<>
  h3svg::SavedGame
  JsonReader<h3svg::SavedGame>::operator()(const Json::Value& value) const;

  template<>
  h3svg::ScenarioStartingInfo
  JsonReader<h3svg::ScenarioStartingInfo>::operator()(const Json::Value& value) const;

  template<>
  h3svg::SeersHut
  JsonReader<h3svg::SeersHut>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Sign
  JsonReader<h3svg::Sign>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Tile
  JsonReader<h3svg::Tile>::operator()(const Json::Value& value) const;

  template<>
  h3svg::TileVisibility
  JsonReader<h3svg::TileVisibility>::operator()(const Json::Value& value) const;

  template<>
  h3svg::TimedEvent
  JsonReader<h3svg::TimedEvent>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Town
  JsonReader<h3svg::Town>::operator()(const Json::Value& value) const;

  template<>
  h3svg::TownEvent
  JsonReader<h3svg::TownEvent>::operator()(const Json::Value& value) const;

  template<>
  h3svg::TownUniqueBuildingsProperties
  JsonReader<h3svg::TownUniqueBuildingsProperties>::operator()(const Json::Value& value) const;

  template<>
  h3svg::Troops
  JsonReader<h3svg::Troops>::operator()(const Json::Value& value) const;

  template<>
  h3svg::University
  JsonReader<h3svg::University>::operator()(const Json::Value& value) const;

  template<>
  h3svg::VictoryCondition
  JsonReader<h3svg::VictoryCondition>::operator()(const Json::Value& value) const;
}
