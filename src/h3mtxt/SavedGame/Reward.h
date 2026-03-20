#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Map/Constants/RewardType.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

#include <cstdint>
#include <variant>

namespace h3svg
{
  template<>
  struct RewardDetails<RewardType::None>
  {
    ReservedData<8> reserved;
  };

  template<>
  struct RewardDetails<RewardType::Experience>
  {
    std::int32_t experience {};
    ReservedData<4> reserved;
  };

  template<>
  struct RewardDetails<RewardType::SpellPoints>
  {
    std::int32_t spell_points {};
    ReservedData<4> reserved;
  };

  template<>
  struct RewardDetails<RewardType::Morale>
  {
    std::int32_t morale {};
    ReservedData<4> reserved;
  };

  template<>
  struct RewardDetails<RewardType::Luck>
  {
    std::int32_t luck {};
    ReservedData<4> reserved;
  };

  template<>
  struct RewardDetails<RewardType::Resource>
  {
    ResourceType32 type {};
    std::int32_t amount {};
  };

  template<>
  struct RewardDetails<RewardType::PrimarySkill>
  {
    PrimarySkillType32 type {};
    std::int32_t value {};
  };

  template<>
  struct RewardDetails<RewardType::SecondarySkill>
  {
    SecondarySkillType32 type {};
    std::int32_t level {};
  };

  template<>
  struct RewardDetails<RewardType::Artifact>
  {
    ArtifactType32 artifact {};
    ReservedData<4> reserved;
  };

  template<>
  struct RewardDetails<RewardType::Spell>
  {
    SpellType32 spell {};
    ReservedData<4> reserved;
  };

  template<>
  struct RewardDetails<RewardType::Creature>
  {
    CreatureType32 type {};
    std::int32_t count {};
  };

  // The equivalent of h3m::Reward stored in H3SVG.
  //
  // This one is always serialized in H3SVG using 12 bytes. A type-unsafe version could be as simple as:
  //   int32_t reward_type;
  //   int32_t details1;
  //   int32_t details2;
  // Perhaps, this is exactly how Heroes3.exe treats it. We will use a type-safe representation though.
  struct Reward
  {
    using Details = std::variant<
      RewardDetails<RewardType::None>,
      RewardDetails<RewardType::Experience>,
      RewardDetails<RewardType::SpellPoints>,
      RewardDetails<RewardType::Morale>,
      RewardDetails<RewardType::Luck>,
      RewardDetails<RewardType::Resource>,
      RewardDetails<RewardType::PrimarySkill>,
      RewardDetails<RewardType::SecondarySkill>,
      RewardDetails<RewardType::Artifact>,
      RewardDetails<RewardType::Spell>,
      RewardDetails<RewardType::Creature>
    >;

    // \return the type of the reward.
    constexpr RewardType type() const noexcept;

    Details details {};
  };

  constexpr RewardType Reward::type() const noexcept
  {
    return static_cast<RewardType>(details.index());
  }
}
