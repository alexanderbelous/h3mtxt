#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Map/Constants/RewardType.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

#include <cstdint>
#include <variant>

namespace h3svg
{
  template<>
  struct RewardDetailsSvg<RewardType::None>
  {
    ReservedData<8> reserved;
  };

  template<>
  struct RewardDetailsSvg<RewardType::Experience>
  {
    std::int32_t experience {};
    ReservedData<4> reserved;
  };

  template<>
  struct RewardDetailsSvg<RewardType::SpellPoints>
  {
    std::int32_t spell_points {};
    ReservedData<4> reserved;
  };

  template<>
  struct RewardDetailsSvg<RewardType::Morale>
  {
    std::int32_t morale {};
    ReservedData<4> reserved;
  };

  template<>
  struct RewardDetailsSvg<RewardType::Luck>
  {
    std::int32_t luck {};
    ReservedData<4> reserved;
  };

  template<>
  struct RewardDetailsSvg<RewardType::Resource>
  {
    ResourceType32 type {};
    std::int32_t amount {};
  };

  template<>
  struct RewardDetailsSvg<RewardType::PrimarySkill>
  {
    PrimarySkillType32 type {};
    std::int32_t value {};
  };

  template<>
  struct RewardDetailsSvg<RewardType::SecondarySkill>
  {
    SecondarySkillType32 type {};
    std::int32_t level {};
  };

  template<>
  struct RewardDetailsSvg<RewardType::Artifact>
  {
    ArtifactType32 artifact {};
    ReservedData<4> reserved;
  };

  template<>
  struct RewardDetailsSvg<RewardType::Spell>
  {
    SpellType32 spell {};
    ReservedData<4> reserved;
  };

  template<>
  struct RewardDetailsSvg<RewardType::Creature>
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
  struct RewardSvg
  {
    using Details = std::variant<
      RewardDetailsSvg<RewardType::None>,
      RewardDetailsSvg<RewardType::Experience>,
      RewardDetailsSvg<RewardType::SpellPoints>,
      RewardDetailsSvg<RewardType::Morale>,
      RewardDetailsSvg<RewardType::Luck>,
      RewardDetailsSvg<RewardType::Resource>,
      RewardDetailsSvg<RewardType::PrimarySkill>,
      RewardDetailsSvg<RewardType::SecondarySkill>,
      RewardDetailsSvg<RewardType::Artifact>,
      RewardDetailsSvg<RewardType::Spell>,
      RewardDetailsSvg<RewardType::Creature>
    >;

    // \return the type of the reward.
    constexpr RewardType type() const noexcept;

    Details details {};
  };

  constexpr RewardType RewardSvg::type() const noexcept
  {
    return static_cast<RewardType>(details.index());
  }
}
