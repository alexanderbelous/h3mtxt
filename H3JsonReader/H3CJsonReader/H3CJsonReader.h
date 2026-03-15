#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/Campaign/Constants/StartingBonusType.h>
#include <h3mtxt/Campaign/Constants/StartingOptionsType.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBaseFwd.h>

// API for deserializing H3C data from JSON.
namespace h3m::H3JsonReader_NS
{
  template<>
  Campaign JsonReader<Campaign>::operator()(const Json::Value& value) const;

  template<>
  CampaignHeader JsonReader<CampaignHeader>::operator()(const Json::Value& value) const;

  template<>
  CampaignScenario JsonReader<CampaignScenario>::operator()(const Json::Value& value) const;

  template<>
  CrossoverOptions JsonReader<CrossoverOptions>::operator()(const Json::Value& value) const;

  template<>
  CutScene JsonReader<CutScene>::operator()(const Json::Value& value) const;

  template<>
  StartingBonus JsonReader<StartingBonus>::operator()(const Json::Value& value) const;

  template<>
  StartingBonusDetails<StartingBonusType::Spell>
  JsonReader<StartingBonusDetails<StartingBonusType::Spell>>::operator()(const Json::Value& value) const;

  template<>
  StartingBonusDetails<StartingBonusType::Creature>
  JsonReader<StartingBonusDetails<StartingBonusType::Creature>>::operator()(const Json::Value& value) const;

  template<>
  StartingBonusDetails<StartingBonusType::Building>
  JsonReader<StartingBonusDetails<StartingBonusType::Building>>::operator()(const Json::Value& value) const;

  template<>
  StartingBonusDetails<StartingBonusType::Artifact>
  JsonReader<StartingBonusDetails<StartingBonusType::Artifact>>::operator()(const Json::Value& value) const;

  template<>
  StartingBonusDetails<StartingBonusType::SpellScroll>
  JsonReader<StartingBonusDetails<StartingBonusType::SpellScroll>>::operator()(const Json::Value& value) const;

  template<>
  StartingBonusDetails<StartingBonusType::PrimarySkills>
  JsonReader<StartingBonusDetails<StartingBonusType::PrimarySkills>>::operator()(const Json::Value& value) const;

  template<>
  StartingBonusDetails<StartingBonusType::SecondarySkill>
  JsonReader<StartingBonusDetails<StartingBonusType::SecondarySkill>>::operator()(const Json::Value& value) const;

  template<>
  StartingBonusDetails<StartingBonusType::Resource>
  JsonReader<StartingBonusDetails<StartingBonusType::Resource>>::operator()(const Json::Value& value) const;

  template<>
  StartingOptions JsonReader<StartingOptions>::operator()(const Json::Value& value) const;

  template<>
  StartingOptionsDetails<StartingOptionsType::None>
  JsonReader<StartingOptionsDetails<StartingOptionsType::None>>::operator()(const Json::Value&) const;

  template<>
  StartingOptionsDetails<StartingOptionsType::StartingBonus>
  JsonReader<StartingOptionsDetails<StartingOptionsType::StartingBonus>>::operator()(const Json::Value&) const;

  template<>
  StartingOptionsDetails<StartingOptionsType::HeroCrossover>
  JsonReader<StartingOptionsDetails<StartingOptionsType::HeroCrossover>>::operator()(const Json::Value&) const;

  template<>
  StartingOptionsDetails<StartingOptionsType::StartingHero>
  JsonReader<StartingOptionsDetails<StartingOptionsType::StartingHero>>::operator()(const Json::Value&) const;
}
