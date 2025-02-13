#include <h3mtxt/H3MJsonReader/readReward.h>

#include <h3mtxt/Map/Utils/EnumSequence.h>

#include <array>

namespace h3m
{
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
