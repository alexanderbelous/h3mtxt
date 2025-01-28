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
    std::uint32_t spell_points {};
  };

  template<>
  struct RewardDetails<RewardType::Morale>
  {
    // TODO: test what happens if it's > 3.
    std::uint8_t morale {};
  };

  template<>
  struct RewardDetails<RewardType::Luck>
  {
    // TODO: test what happens if it's > 3.
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
