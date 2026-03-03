#include <h3mtxt/H3SvgReader/H3SvgReader.h>
#include <h3mtxt/Map/Utils/EnumSequence.h>
#include <h3mtxt/SavedGame/RewardSvg.h>

#include <array>
#include <stdexcept>

namespace h3m
{
  namespace
  {
    template<RewardType T>
    RewardSvg::Details readRewardDetailsAsVariant(const H3SvgReader& reader)
    {
      return RewardSvg::Details{ reader.readRewardDetails<T>() };
    }

    RewardSvg::Details readRewardDetailsVariant(const H3SvgReader& reader, RewardType reward_type)
    {
      // Type of a pointer to a function that takes const H3SvgReader& and returns RewardSvg::Details.
      using ReadRewardDetailsPtr = RewardSvg::Details(*)(const H3SvgReader& reader);
      // Generate (at compile time) an array of function pointers for each instantiation of
      // readRewardDetailsAsVariant() ordered by RewardType.
      static constexpr std::array<ReadRewardDetailsPtr, kNumRewardTypes> kRewardDetailsReaders =
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
  RewardDetailsSvg<RewardType::None> H3SvgReader::readRewardDetails() const
  {
    return { .reserved = readReservedData<8>() };
  }

  template<>
  RewardDetailsSvg<RewardType::Experience> H3SvgReader::readRewardDetails() const
  {
    return {
      .experience = readInt<int32_t>(),
      .reserved = readReservedData<4>()
    };
  }

  template<>
  RewardDetailsSvg<RewardType::SpellPoints> H3SvgReader::readRewardDetails() const
  {
    return {
      .spell_points = readInt<int32_t>(),
      .reserved = readReservedData<4>()
    };
  }

  template<>
  RewardDetailsSvg<RewardType::Morale> H3SvgReader::readRewardDetails() const
  {
    return {
      .morale = readInt<int32_t>(),
      .reserved = readReservedData<4>()
    };
  }

  template<>
  RewardDetailsSvg<RewardType::Luck> H3SvgReader::readRewardDetails() const
  {
    return {
      .luck = readInt<int32_t>(),
      .reserved = readReservedData<4>()
    };
  }

  template<>
  RewardDetailsSvg<RewardType::Resource> H3SvgReader::readRewardDetails() const
  {
    return {
      .type = readEnum<ResourceType32>(),
      .amount = readInt<std::int32_t>()
    };
  }

  template<>
  RewardDetailsSvg<RewardType::PrimarySkill> H3SvgReader::readRewardDetails() const
  {
    return {
      .type = readEnum<PrimarySkillType32>(),
      .value = readInt<std::int32_t>()
    };
  }

  template<>
  RewardDetailsSvg<RewardType::SecondarySkill> H3SvgReader::readRewardDetails() const
  {
    return {
      .type = readEnum<SecondarySkillType32>(),
      .level = readInt<std::int32_t>()
    };
  }

  template<>
  RewardDetailsSvg<RewardType::Artifact> H3SvgReader::readRewardDetails() const
  {
    return {
      .artifact = readEnum<ArtifactType32>(),
      .reserved = readReservedData<4>()
    };
  }

  template<>
  RewardDetailsSvg<RewardType::Spell> H3SvgReader::readRewardDetails() const
  {
    return {
      .spell = readEnum<SpellType32>(),
      .reserved = readReservedData<4>()
    };
  }

  template<>
  RewardDetailsSvg<RewardType::Creature> H3SvgReader::readRewardDetails() const
  {
    return {
      .type = readEnum<CreatureType32>(),
      .count = readInt<std::int32_t>()
    };
  }

  RewardSvg H3SvgReader::readReward() const
  {
    const std::uint32_t reward_type_idx = readInt<std::uint32_t>();
    if (reward_type_idx >= kNumRewardTypes)
    {
      throw std::runtime_error("H3SvgReader::readReward(): invalid RewardType.");
    }
    return RewardSvg{ .details = readRewardDetailsVariant(*this, static_cast<RewardType>(reward_type_idx)) };
  }
}
