#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/Utils/SwitchStatement.h>
#include <h3mtxt/Map/Reward.h>

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

    // Convert the function template readRewardDetailsAsVariant<T>() into an alias template,
    // so that it can be passed as a template template parameter to generateSwitchStatement().
    template<RewardType T>
    using RewardDetailsReaderTemplateAlias = SwitchStatement_NS::StaticConstant<&readRewardDetailsAsVariant<T>>;
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
    details.quantity = readInt<std::int32_t>();
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
    // Generate a switch statement for all valid RewardType constants.
    // read_reward_details(N, reader) will trigger readRewardDetailsAsVariant<N>(reader).
    static constexpr auto read_reward_details =
      SwitchStatement_NS::generateSwitchStatement<RewardType, kNumRewardTypes, RewardDetailsReaderTemplateAlias>();

    const RewardType reward_type = readEnum<RewardType>();
    return Reward{ .details = read_reward_details(reward_type, *this) };
  }
}
