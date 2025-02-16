#pragma once

#include <h3mtxt/Map/Constants/ArtifactType.h>
#include <h3mtxt/Map/Constants/CreatureType.h>
#include <h3mtxt/Map/Constants/SpellType.h>
#include <h3mtxt/Map/Constants/PrimarySkillType.h>
#include <h3mtxt/Map/Constants/ResourceType.h>
#include <h3mtxt/Map/Constants/RewardType.h>
#include <h3mtxt/Map/SecondarySkill.h>

#include <variant>

namespace h3m
{
  template<RewardType T>
  struct RewardDetails;

  template<>
  struct RewardDetails<RewardType::None>
  {};

  template<>
  struct RewardDetails<RewardType::Experience>
  {
    std::uint32_t experience {};
  };

  template<>
  struct RewardDetails<RewardType::SpellPoints>
  {
    // The Map Editor only allows setting a value from [1; 999].
    //
    // 0 is OK (no spell points granted).
    // Values within [1000; 2147483647] are generally ok (I think I've observed a crash at 32768,
    // but I haven't been able to reproduce it), but you will only be granted 999 points anyway.
    // Negative values are weird:
    // * If N is negative and the hero has -N or more spell points, the hero will lose -N spell points.
    // * However, if N is negative and the hero has less than -N spell points,
    //   the hero will *gain* 10 spell points.
    std::int32_t spell_points {};
  };

  template<>
  struct RewardDetails<RewardType::Morale>
  {
    // The Map Editor only allows setting a value from [1; 3].
    // However, it's perfectly fine to use a value > 3; this can have a
    // meaningful effect if, for example, the hero has creatures from 7 different towns
    // (-5 morale).
    std::uint8_t morale {};
  };

  template<>
  struct RewardDetails<RewardType::Luck>
  {
    std::uint8_t luck {};
  };

  template<>
  struct RewardDetails<RewardType::Resource>
  {
    ResourceType type {};
    std::uint32_t amount {};
  };

  template<>
  struct RewardDetails<RewardType::PrimarySkill>
  {
    PrimarySkillType type {};
    std::uint8_t value {};
  };

  template<>
  struct RewardDetails<RewardType::SecondarySkill>
  {
    SecondarySkill skill;
  };

  template<>
  struct RewardDetails<RewardType::Artifact>
  {
    ArtifactType artifact {};
  };

  template<>
  struct RewardDetails<RewardType::Spell>
  {
    SpellType spell {};
  };

  template<>
  struct RewardDetails<RewardType::Creature>
  {
    // TODO: this is the same as in CreatureStack. Consider merging.
    CreatureType type {};
    std::uint16_t count {};
  };

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

    Details details;
  };

  constexpr RewardType Reward::type() const noexcept
  {
    return static_cast<RewardType>(details.index());
  }
}
