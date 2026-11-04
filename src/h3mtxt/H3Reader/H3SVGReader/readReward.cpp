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
    using readRewardDetailsAsVariantAliasTemplate = SwitchStatement_NS::StaticConstant<&readRewardDetailsAsVariant<T>>;
  }

  template<RewardType T>
  RewardDetails<T> H3SVGReader::readRewardDetails() const
  {
    RewardDetails<T> details;
    if constexpr (T == RewardType::None)
    {
      details.reserved = readReservedData<8>();
    }
    else if constexpr (T == RewardType::Experience)
    {
      details.experience = readInt<int32_t>();
      details.reserved = readReservedData<4>();
    }
    else if constexpr (T == RewardType::SpellPoints)
    {
      details.spell_points = readInt<int32_t>();
      details.reserved = readReservedData<4>();
    }
    else if constexpr (T == RewardType::Morale)
    {
      details.morale = readInt<int32_t>();
      details.reserved = readReservedData<4>();
    }
    else if constexpr (T == RewardType::Luck)
    {
      details.luck = readInt<int32_t>();
      details.reserved = readReservedData<4>();
    }
    else if constexpr (T == RewardType::Resource)
    {
      details.resource = readTypedQuantity<ResourceType32, std::int32_t>();
    }
    else if constexpr (T == RewardType::PrimarySkill)
    {
      details.type = readEnum<PrimarySkillType32>();
      details.value = readInt<std::int32_t>();
    }
    else if constexpr (T == RewardType::SecondarySkill)
    {
      details.type = readEnum<SecondarySkillType32>();
      details.level = readInt<std::int32_t>();
    }
    else if constexpr (T == RewardType::Artifact)
    {
      details.artifact = readEnum<ArtifactType32>();
      details.reserved = readReservedData<4>();
    }
    else if constexpr (T == RewardType::Spell)
    {
      details.spell = readEnum<SpellType32>();
      details.reserved = readReservedData<4>();
    }
    else if constexpr (T == RewardType::Creatures)
    {
      details.creatures = readTypedQuantity<CreatureType32, std::int32_t>();
    }
    else
    {
      static_assert(false, "Invalid RewardType.");
    }
    return details;
  }

  Reward H3SVGReader::readReward() const
  {
    static constexpr auto read_reward_details_variant =
        SwitchStatement_NS::generateSwitchStatement<RewardType,
                                                    kNumRewardTypes,
                                                    readRewardDetailsAsVariantAliasTemplate>();

    const std::uint32_t reward_type_idx = readInt<std::uint32_t>();
    if (reward_type_idx >= kNumRewardTypes)
    {
      throw std::runtime_error("H3SVGReader::readReward(): invalid RewardType.");
    }
    const RewardType reward_type = static_cast<RewardType>(reward_type_idx);
    return Reward{ .details = read_reward_details_variant(reward_type, *this) };
  }
}
