#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/Utils/EnumSequence.h>
#include <h3mtxt/Map/Reward.h>

#include <array>

namespace h3m
{
  namespace
  {
    // Wrapper around H3MReader::readRewardDetails(), which returns the result as Reward::Details variant.
    template<RewardType T>
    Reward::Details readRewardDetailsAsVariant(const H3MReader& reader)
    {
      return reader.readRewardDetails<T>();
    }

    // Reads RewardDetails for the specified RewardType.
    // \param reader - input stream.
    // \param reward_type - type of the reward.
    // \return the deserialized data as Reward::Details.
    Reward::Details readRewardDetailsVariant(const H3MReader& reader, RewardType reward_type)
    {
      // Type of a pointer to a function that takes const H3MReader& and returns Reward::Details.
      using ReadRewardDetailsPtr = Reward::Details(*)(const H3MReader& reader);
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
      return kRewardDetailsReaders.at(static_cast<std::size_t>(reward_type))(reader);
    }
  }

  template<>
  RewardDetails<RewardType::None> H3MReader::readRewardDetails<RewardType::None>() const
  {
    return {};
  }

  template<>
  RewardDetails<RewardType::Experience> H3MReader::readRewardDetails<RewardType::Experience>() const
  {
    RewardDetails<RewardType::Experience> details;
    details.experience = readInt<std::int32_t>();
    return details;
  }

  template<>
  RewardDetails<RewardType::SpellPoints> H3MReader::readRewardDetails<RewardType::SpellPoints>() const
  {
    RewardDetails<RewardType::SpellPoints> details;
    details.spell_points = readInt<std::int32_t>();
    return details;
  }

  template<>
  RewardDetails<RewardType::Morale> H3MReader::readRewardDetails<RewardType::Morale>() const
  {
    RewardDetails<RewardType::Morale> details;
    details.morale = readInt<std::int8_t>();
    return details;
  }

  template<>
  RewardDetails<RewardType::Luck> H3MReader::readRewardDetails<RewardType::Luck>() const
  {
    RewardDetails<RewardType::Luck> details;
    details.luck = readInt<std::int8_t>();
    return details;
  }

  template<>
  RewardDetails<RewardType::Resource> H3MReader::readRewardDetails<RewardType::Resource>() const
  {
    RewardDetails<RewardType::Resource> details;
    details.type = readEnum<ResourceType>();
    details.amount = readInt<std::int32_t>();
    return details;
  }

  template<>
  RewardDetails<RewardType::PrimarySkill> H3MReader::readRewardDetails<RewardType::PrimarySkill>() const
  {
    RewardDetails<RewardType::PrimarySkill> details;
    details.type = readEnum<PrimarySkillType>();
    details.value = readInt<std::int8_t>();
    return details;
  }

  template<>
  RewardDetails<RewardType::SecondarySkill> H3MReader::readRewardDetails<RewardType::SecondarySkill>() const
  {
    return RewardDetails<RewardType::SecondarySkill> { readSecondarySkill() };
  }

  template<>
  RewardDetails<RewardType::Artifact> H3MReader::readRewardDetails<RewardType::Artifact>() const
  {
    RewardDetails<RewardType::Artifact> details;
    details.artifact = readEnum<ArtifactType>();
    return details;
  }

  template<>
  RewardDetails<RewardType::Spell> H3MReader::readRewardDetails<RewardType::Spell>() const
  {
    RewardDetails<RewardType::Spell> details;
    details.spell = readEnum<SpellType>();
    return details;
  }

  template<>
  RewardDetails<RewardType::Creature> H3MReader::readRewardDetails<RewardType::Creature>() const
  {
    return RewardDetails<RewardType::Creature> { readCreatureStack() };
  }

  Reward H3MReader::readReward() const
  {
    Reward reward;
    const RewardType reward_type = readEnum<RewardType>();
    reward.details = readRewardDetailsVariant(*this, reward_type);
    return reward;
  }
}
