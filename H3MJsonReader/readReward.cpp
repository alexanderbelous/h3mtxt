#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/H3MJsonReader/Utils.h>
#include <h3mtxt/Map/Utils/EnumSequence.h>
#include <h3mtxt/Map/Reward.h>

#include <array>

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

  namespace
  {
    // Wrapper around JsonReader<RewardDetails<T>>, which returns the result as Reward::Details variant.
    template<RewardType T>
    Reward::Details readRewardDetailsAsVariant(const Json::Value& value)
    {
      return JsonReader<RewardDetails<T>>{}(value);
    }

    // Reads RewardDetails for the specified RewardType.
    // \param value - input JSON.
    // \param reward_type - type of the reward.
    // \return the deserialized data as Reward::Details.
    Reward::Details readRewardDetailsVariant(const Json::Value& value, RewardType reward_type)
    {
      // Type of a pointer to a function that takes const Json::Value& and returns Reward::Details.
      using ReadRewardDetailsPtr = Reward::Details(*)(const Json::Value&);
      // Generate (at compile time) an array of function pointers for each instantiation of
      // readRewardDetailsAsVariant() ordered by RewardType.
      constexpr std::array<ReadRewardDetailsPtr, kNumRewardTypes> kRewardDetailsReaders =
        [] <RewardType... reward_types>
        (EnumSequence<RewardType, reward_types...> seq)
        consteval
        {
          return std::array<ReadRewardDetailsPtr, sizeof...(reward_types)>
          {
            &readRewardDetailsAsVariant<reward_types>...
          };
        }(MakeEnumSequence<RewardType, kNumRewardTypes>{});
      // Invoke a function from the generated array.
      return kRewardDetailsReaders.at(static_cast<std::size_t>(reward_type))(value);
    }
  }

  Reward JsonReader<Reward>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<Reward>;
    Reward reward;
    const RewardType reward_type = readField<RewardType>(value, Fields::kType);
    if (reward_type != RewardType::None)
    {
      const Json::Value* details_json = value.find(
        Fields::kDetails.data(), Fields::kDetails.data() + Fields::kDetails.size());
      if (!details_json)
      {
        throw MissingJsonFieldError(Fields::kDetails);
      }
      reward.details = readRewardDetailsVariant(*details_json, reward_type);
    }
    return reward;
  }
}
