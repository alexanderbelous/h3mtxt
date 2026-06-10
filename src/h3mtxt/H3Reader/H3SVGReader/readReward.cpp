#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/Map/Utils/SwitchStatement.h>
#include <h3mtxt/SavedGame/Reward.h>

#include <stdexcept>

namespace h3svg
{
  namespace
  {
    using ::h3m::kNumRewardTypes;

    template<RewardType T>
    Reward::Details readRewardDetailsAsVariant(const H3SVGReader& reader)
    {
      return Reward::Details{ reader.readRewardDetails<T>() };
    }

    template<RewardType T>
    using RewardDetailsReaderTemplateAlias = SwitchStatement_NS::StaticConstant<&readRewardDetailsAsVariant<T>>;

    Reward::Details readRewardDetailsVariant(const H3SVGReader& reader, RewardType reward_type)
    {
      static constexpr auto switch_statement =
        SwitchStatement_NS::generateSwitchStatement<RewardType,
                                                    kNumRewardTypes,
                                                    RewardDetailsReaderTemplateAlias>();
      return switch_statement(reward_type, reader);
    }
  }

  template<>
  RewardDetails<RewardType::None> H3SVGReader::readRewardDetails() const
  {
    return { .reserved = readReservedData<8>() };
  }

  template<>
  RewardDetails<RewardType::Experience> H3SVGReader::readRewardDetails() const
  {
    return {
      .experience = readInt<int32_t>(),
      .reserved = readReservedData<4>()
    };
  }

  template<>
  RewardDetails<RewardType::SpellPoints> H3SVGReader::readRewardDetails() const
  {
    return {
      .spell_points = readInt<int32_t>(),
      .reserved = readReservedData<4>()
    };
  }

  template<>
  RewardDetails<RewardType::Morale> H3SVGReader::readRewardDetails() const
  {
    return {
      .morale = readInt<int32_t>(),
      .reserved = readReservedData<4>()
    };
  }

  template<>
  RewardDetails<RewardType::Luck> H3SVGReader::readRewardDetails() const
  {
    return {
      .luck = readInt<int32_t>(),
      .reserved = readReservedData<4>()
    };
  }

  template<>
  RewardDetails<RewardType::Resource> H3SVGReader::readRewardDetails() const
  {
    return {
      .type = readEnum<ResourceType32>(),
      .amount = readInt<std::int32_t>()
    };
  }

  template<>
  RewardDetails<RewardType::PrimarySkill> H3SVGReader::readRewardDetails() const
  {
    return {
      .type = readEnum<PrimarySkillType32>(),
      .value = readInt<std::int32_t>()
    };
  }

  template<>
  RewardDetails<RewardType::SecondarySkill> H3SVGReader::readRewardDetails() const
  {
    return {
      .type = readEnum<SecondarySkillType32>(),
      .level = readInt<std::int32_t>()
    };
  }

  template<>
  RewardDetails<RewardType::Artifact> H3SVGReader::readRewardDetails() const
  {
    return {
      .artifact = readEnum<ArtifactType32>(),
      .reserved = readReservedData<4>()
    };
  }

  template<>
  RewardDetails<RewardType::Spell> H3SVGReader::readRewardDetails() const
  {
    return {
      .spell = readEnum<SpellType32>(),
      .reserved = readReservedData<4>()
    };
  }

  template<>
  RewardDetails<RewardType::Creature> H3SVGReader::readRewardDetails() const
  {
    return {
      .type = readEnum<CreatureType32>(),
      .count = readInt<std::int32_t>()
    };
  }

  Reward H3SVGReader::readReward() const
  {
    const std::uint32_t reward_type_idx = readInt<std::uint32_t>();
    if (reward_type_idx >= kNumRewardTypes)
    {
      throw std::runtime_error("H3SVGReader::readReward(): invalid RewardType.");
    }
    return Reward{ .details = readRewardDetailsVariant(*this, static_cast<RewardType>(reward_type_idx)) };
  }
}
