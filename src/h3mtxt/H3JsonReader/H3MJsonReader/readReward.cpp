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
    using Fields = FieldNames<RewardDetails<RewardType::Experience>>;
    RewardDetails<RewardType::Experience> details;
    readField(details.experience, value, Fields::kExperience);
    return details;
  }

  template<>
  RewardDetails<RewardType::SpellPoints>
  JsonReader<RewardDetails<RewardType::SpellPoints>>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<RewardDetails<RewardType::SpellPoints>>;
    RewardDetails<RewardType::SpellPoints> details;
    readField(details.spell_points, value, Fields::kSpellPoints);
    return details;
  }

  template<>
  RewardDetails<RewardType::Morale>
  JsonReader<RewardDetails<RewardType::Morale>>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<RewardDetails<RewardType::Morale>>;
    RewardDetails<RewardType::Morale> details;
    readField(details.morale, value, Fields::kMorale);
    return details;
  }

  template<>
  RewardDetails<RewardType::Luck>
  JsonReader<RewardDetails<RewardType::Luck>>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<RewardDetails<RewardType::Luck>>;
    RewardDetails<RewardType::Luck> details;
    readField(details.luck, value, Fields::kLuck);
    return details;
  }

  template<>
  RewardDetails<RewardType::Resource>
  JsonReader<RewardDetails<RewardType::Resource>>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<RewardDetails<RewardType::Resource>>;
    RewardDetails<RewardType::Resource> details;
    readField(details.resource, value, Fields::kResource);
    return details;
  }

  template<>
  RewardDetails<RewardType::PrimarySkill>
  JsonReader<RewardDetails<RewardType::PrimarySkill>>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<RewardDetails<RewardType::PrimarySkill>>;
    RewardDetails<RewardType::PrimarySkill> details;
    readField(details.type, value, Fields::kType);
    readField(details.value, value, Fields::kValue);
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
    using Fields = FieldNames<RewardDetails<RewardType::Artifact>>;
    RewardDetails<RewardType::Artifact> details;
    readField(details.artifact, value, Fields::kArtifact);
    return details;
  }

  template<>
  RewardDetails<RewardType::Spell>
  JsonReader<RewardDetails<RewardType::Spell>>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<RewardDetails<RewardType::Spell>>;
    RewardDetails<RewardType::Spell> details;
    readField(details.spell, value, Fields::kSpell);
    return details;
  }

  template<>
  RewardDetails<RewardType::Creatures>
  JsonReader<RewardDetails<RewardType::Creatures>>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<RewardDetails<RewardType::Creatures>>;
    RewardDetails<RewardType::Creatures> details;
    readField(details.creatures, value, Fields::kCreatures);
    return details;
  }

  template<>
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
