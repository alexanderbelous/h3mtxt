#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/VariantJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/Reward.h>

namespace h3json
{
  using ::h3m::Reward;
  using ::h3m::RewardDetails;
  using ::h3m::RewardType;

  template<>
  RewardDetails<RewardType::None>
  JsonReader<RewardDetails<RewardType::None>>::operator()(const Json::Value&) const
  {
    return {};
  }

  template<>
  RewardDetails<RewardType::Experience>
  JsonReader<RewardDetails<RewardType::Experience>>::operator()(const Json::Value& value) const
  {
    RewardDetails<RewardType::Experience> details;
    readField(details.experience, value, "experience");
    return details;
  }

  template<>
  RewardDetails<RewardType::SpellPoints>
  JsonReader<RewardDetails<RewardType::SpellPoints>>::operator()(const Json::Value& value) const
  {
    RewardDetails<RewardType::SpellPoints> details;
    readField(details.spell_points, value, "spell_points");
    return details;
  }

  template<>
  RewardDetails<RewardType::Morale>
  JsonReader<RewardDetails<RewardType::Morale>>::operator()(const Json::Value& value) const
  {
    RewardDetails<RewardType::Morale> details;
    readField(details.morale, value, "morale");
    return details;
  }

  template<>
  RewardDetails<RewardType::Luck>
  JsonReader<RewardDetails<RewardType::Luck>>::operator()(const Json::Value& value) const
  {
    RewardDetails<RewardType::Luck> details;
    readField(details.luck, value, "luck");
    return details;
  }

  template<>
  RewardDetails<RewardType::Resource>
  JsonReader<RewardDetails<RewardType::Resource>>::operator()(const Json::Value& value) const
  {
    RewardDetails<RewardType::Resource> details;
    readField(details.type, value, "type");
    readField(details.amount, value, "amount");
    return details;
  }

  template<>
  RewardDetails<RewardType::PrimarySkill>
  JsonReader<RewardDetails<RewardType::PrimarySkill>>::operator()(const Json::Value& value) const
  {
    RewardDetails<RewardType::PrimarySkill> details;
    readField(details.type, value, "type");
    readField(details.value, value, "value");
    return details;
  }

  template<>
  RewardDetails<RewardType::SecondarySkill>
  JsonReader<RewardDetails<RewardType::SecondarySkill>>::operator()(const Json::Value& value) const
  {
    return RewardDetails<RewardType::SecondarySkill> { fromJson<h3m::SecondarySkill>(value) };
  }

  template<>
  RewardDetails<RewardType::Artifact>
  JsonReader<RewardDetails<RewardType::Artifact>>::operator()(const Json::Value& value) const
  {
    RewardDetails<RewardType::Artifact> details;
    readField(details.artifact, value, "artifact");
    return details;
  }

  template<>
  RewardDetails<RewardType::Spell>
  JsonReader<RewardDetails<RewardType::Spell>>::operator()(const Json::Value& value) const
  {
    RewardDetails<RewardType::Spell> details;
    readField(details.spell, value, "spell");
    return details;
  }

  template<>
  RewardDetails<RewardType::Creature>
  JsonReader<RewardDetails<RewardType::Creature>>::operator()(const Json::Value& value) const
  {
    return RewardDetails<RewardType::Creature> { fromJson<h3m::CreatureStack>(value) };
  }

  Reward JsonReader<Reward>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<Reward>;
    Reward reward;
    const RewardType reward_type = readField<RewardType>(value, Fields::kType);
    if (reward_type != RewardType::None)
    {
      VariantJsonReader<Reward::Details> variant_reader {};
      reward.details = variant_reader(getJsonField(value, Fields::kDetails),
                                      Reward::getAlternativeIdx(reward_type));
    }
    return reward;
  }
}
