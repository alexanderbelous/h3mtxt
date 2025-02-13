#pragma once

#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/H3MJsonReader/readSecondarySkill.h>
#include <h3mtxt/Map/Reward.h>

namespace h3m
{
  template<>
  struct JsonReader<RewardDetails<RewardType::None>>
  {
    RewardDetails<RewardType::None> operator()(const Json::Value&) const
    {
      return {};
    }
  };

  template<>
  struct JsonReader<RewardDetails<RewardType::Experience>>
  {
    RewardDetails<RewardType::Experience> operator()(const Json::Value& value) const
    {
      RewardDetails<RewardType::Experience> details;
      readField(details.experience, value, "experience");
      return details;
    }
  };

  template<>
  struct JsonReader<RewardDetails<RewardType::SpellPoints>>
  {
    RewardDetails<RewardType::SpellPoints> operator()(const Json::Value& value) const
    {
      RewardDetails<RewardType::SpellPoints> details;
      readField(details.spell_points, value, "spell_points");
      return details;
    }
  };

  template<>
  struct JsonReader<RewardDetails<RewardType::Morale>>
  {
    RewardDetails<RewardType::Morale> operator()(const Json::Value& value) const
    {
      RewardDetails<RewardType::Morale> details;
      readField(details.morale, value, "morale");
      return details;
    }
  };

  template<>
  struct JsonReader<RewardDetails<RewardType::Luck>>
  {
    RewardDetails<RewardType::Luck> operator()(const Json::Value& value) const
    {
      RewardDetails<RewardType::Luck> details;
      readField(details.luck, value, "luck");
      return details;
    }
  };

  template<>
  struct JsonReader<RewardDetails<RewardType::Resource>>
  {
    RewardDetails<RewardType::Resource> operator()(const Json::Value& value) const
    {
      RewardDetails<RewardType::Resource> details;
      readField(details.type, value, "type");
      readField(details.amount, value, "amount");
      return details;
    }
  };

  template<>
  struct JsonReader<RewardDetails<RewardType::PrimarySkill>>
  {
    RewardDetails<RewardType::PrimarySkill> operator()(const Json::Value& value) const
    {
      RewardDetails<RewardType::PrimarySkill> details;
      readField(details.type, value, "type");
      readField(details.value, value, "value");
      return details;
    }
  };

  template<>
  struct JsonReader<RewardDetails<RewardType::SecondarySkill>>
  {
    RewardDetails<RewardType::SecondarySkill> operator()(const Json::Value& value) const
    {
      RewardDetails<RewardType::SecondarySkill> details;
      readField(details.skill, value, "skill");
      return details;
    }
  };

  template<>
  struct JsonReader<RewardDetails<RewardType::Artifact>>
  {
    RewardDetails<RewardType::Artifact> operator()(const Json::Value& value) const
    {
      RewardDetails<RewardType::Artifact> details;
      readField(details.artifact, value, "artifact");
      return details;
    }
  };

  template<>
  struct JsonReader<RewardDetails<RewardType::Spell>>
  {
    RewardDetails<RewardType::Spell> operator()(const Json::Value& value) const
    {
      RewardDetails<RewardType::Spell> details;
      readField(details.spell, value, "spell");
      return details;
    }
  };

  template<>
  struct JsonReader<RewardDetails<RewardType::Creature>>
  {
    RewardDetails<RewardType::Creature> operator()(const Json::Value& value) const
    {
      RewardDetails<RewardType::Creature> details;
      readField(details.type, value, "type");
      readField(details.count, value, "count");
      return details;
    }
  };

  template<>
  struct JsonReader<Reward>
  {
    Reward operator()(const Json::Value& value) const;
  };
}
