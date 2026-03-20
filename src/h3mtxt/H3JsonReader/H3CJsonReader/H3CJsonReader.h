#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/Campaign/Constants/StartingBonusType.h>
#include <h3mtxt/Campaign/Constants/StartingOptionsType.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBaseFwd.h>

// API for deserializing H3C data from JSON.
namespace h3json
{
  template<>
  h3m::Campaign JsonReader<h3m::Campaign>::operator()(const Json::Value& value) const;

  template<>
  h3m::CampaignHeader JsonReader<h3m::CampaignHeader>::operator()(const Json::Value& value) const;

  template<>
  h3m::CampaignScenario JsonReader<h3m::CampaignScenario>::operator()(const Json::Value& value) const;

  template<>
  h3m::CrossoverOptions JsonReader<h3m::CrossoverOptions>::operator()(const Json::Value& value) const;

  template<>
  h3m::CutScene JsonReader<h3m::CutScene>::operator()(const Json::Value& value) const;

  template<>
  h3m::StartingBonus JsonReader<h3m::StartingBonus>::operator()(const Json::Value& value) const;

  template<>
  h3m::StartingBonusDetails<h3m::StartingBonusType::Spell>
  JsonReader<h3m::StartingBonusDetails<h3m::StartingBonusType::Spell>>::operator()(const Json::Value& value) const;

  template<>
  h3m::StartingBonusDetails<h3m::StartingBonusType::Creature>
  JsonReader<h3m::StartingBonusDetails<h3m::StartingBonusType::Creature>>::operator()(const Json::Value& value) const;

  template<>
  h3m::StartingBonusDetails<h3m::StartingBonusType::Building>
  JsonReader<h3m::StartingBonusDetails<h3m::StartingBonusType::Building>>::operator()(const Json::Value& value) const;

  template<>
  h3m::StartingBonusDetails<h3m::StartingBonusType::Artifact>
  JsonReader<h3m::StartingBonusDetails<h3m::StartingBonusType::Artifact>>::operator()(const Json::Value& value) const;

  template<>
  h3m::StartingBonusDetails<h3m::StartingBonusType::SpellScroll>
  JsonReader<h3m::StartingBonusDetails<h3m::StartingBonusType::SpellScroll>>::operator()(const Json::Value& value) const;

  template<>
  h3m::StartingBonusDetails<h3m::StartingBonusType::PrimarySkills>
  JsonReader<h3m::StartingBonusDetails<h3m::StartingBonusType::PrimarySkills>>::operator()(const Json::Value& value) const;

  template<>
  h3m::StartingBonusDetails<h3m::StartingBonusType::SecondarySkill>
  JsonReader<h3m::StartingBonusDetails<h3m::StartingBonusType::SecondarySkill>>::operator()(const Json::Value& value) const;

  template<>
  h3m::StartingBonusDetails<h3m::StartingBonusType::Resource>
  JsonReader<h3m::StartingBonusDetails<h3m::StartingBonusType::Resource>>::operator()(const Json::Value& value) const;

  template<>
  h3m::StartingOptions JsonReader<h3m::StartingOptions>::operator()(const Json::Value& value) const;

  template<>
  h3m::StartingOptionsDetails<h3m::StartingOptionsType::None>
  JsonReader<h3m::StartingOptionsDetails<h3m::StartingOptionsType::None>>::operator()(const Json::Value&) const;

  template<>
  h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingBonus>
  JsonReader<h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingBonus>>::operator()(const Json::Value&) const;

  template<>
  h3m::StartingOptionsDetails<h3m::StartingOptionsType::HeroCrossover>
  JsonReader<h3m::StartingOptionsDetails<h3m::StartingOptionsType::HeroCrossover>>::operator()(const Json::Value&) const;

  template<>
  h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingHero>
  JsonReader<h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingHero>>::operator()(const Json::Value&) const;
}
