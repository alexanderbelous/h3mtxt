#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/Map/Utils/EnumSequence.h>
#include <h3mtxt/Map/Reward.h>

#include <array>

namespace h3m::H3Reader_NS
{
  namespace
  {
    template<RewardType T>
    RewardDetails<T> readRewardDetails(std::istream& stream)
    {
      static_assert(false, "Missing specialization for readRewardDetails<T>.");
    }

    template<>
    RewardDetails<RewardType::None> readRewardDetails<RewardType::None>(std::istream&)
    {
      return {};
    }

    template<>
    RewardDetails<RewardType::Experience> readRewardDetails<RewardType::Experience>(std::istream& stream)
    {
      RewardDetails<RewardType::Experience> details;
      details.experience = readInt<std::int32_t>(stream);
      return details;
    }

    template<>
    RewardDetails<RewardType::SpellPoints> readRewardDetails<RewardType::SpellPoints>(std::istream& stream)
    {
      RewardDetails<RewardType::SpellPoints> details;
      details.spell_points = readInt<std::int32_t>(stream);
      return details;
    }

    template<>
    RewardDetails<RewardType::Morale> readRewardDetails<RewardType::Morale>(std::istream& stream)
    {
      RewardDetails<RewardType::Morale> details;
      details.morale = readInt<std::int8_t>(stream);
      return details;
    }

    template<>
    RewardDetails<RewardType::Luck> readRewardDetails<RewardType::Luck>(std::istream& stream)
    {
      RewardDetails<RewardType::Luck> details;
      details.luck = readInt<std::int8_t>(stream);
      return details;
    }

    template<>
    RewardDetails<RewardType::Resource> readRewardDetails<RewardType::Resource>(std::istream& stream)
    {
      RewardDetails<RewardType::Resource> details;
      details.type = readEnum<ResourceType>(stream);
      details.amount = readInt<std::int32_t>(stream);
      return details;
    }

    template<>
    RewardDetails<RewardType::PrimarySkill> readRewardDetails<RewardType::PrimarySkill>(std::istream& stream)
    {
      RewardDetails<RewardType::PrimarySkill> details;
      details.type = readEnum<PrimarySkillType>(stream);
      details.value = readInt<std::int8_t>(stream);
      return details;
    }

    template<>
    RewardDetails<RewardType::SecondarySkill> readRewardDetails<RewardType::SecondarySkill>(std::istream& stream)
    {
      return RewardDetails<RewardType::SecondarySkill> { readSecondarySkill(stream) };
    }

    template<>
    RewardDetails<RewardType::Artifact> readRewardDetails<RewardType::Artifact>(std::istream& stream)
    {
      RewardDetails<RewardType::Artifact> details;
      details.artifact = readEnum<ArtifactType>(stream);
      return details;
    }

    template<>
    RewardDetails<RewardType::Spell> readRewardDetails<RewardType::Spell>(std::istream& stream)
    {
      RewardDetails<RewardType::Spell> details;
      details.spell = readEnum<SpellType>(stream);
      return details;
    }

    template<>
    RewardDetails<RewardType::Creature> readRewardDetails<RewardType::Creature>(std::istream& stream)
    {
      return RewardDetails<RewardType::Creature> { readCreatureStack(stream) };
    }

    // Wrapper around readRewardDetails(), which returns the result as Reward::Details variant.
    template<RewardType T>
    Reward::Details readRewardDetailsAsVariant(std::istream& stream)
    {
      return readRewardDetails<T>(stream);
    }

    // Reads RewardDetails for the specified RewardType.
    // \param stream - input stream.
    // \param reward_type - type of the reward.
    // \return the deserialized data as Reward::Details.
    Reward::Details readRewardDetailsVariant(std::istream& stream, RewardType reward_type)
    {
      // Type of a pointer to a function that takes std::istream& and returns Reward::Details.
      using ReadRewardDetailsPtr = Reward::Details(*)(std::istream& stream);
      // Generate (at compile time) an array of function pointers for each instantiation of
      // readRewardDetails() ordered by RewardType.
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
      return kRewardDetailsReaders.at(static_cast<std::size_t>(reward_type))(stream);
    }
  }

  Reward readReward(std::istream& stream)
  {
    Reward reward;
    const RewardType reward_type = readEnum<RewardType>(stream);
    reward.details = readRewardDetailsVariant(stream, reward_type);
    return reward;
  }
}
