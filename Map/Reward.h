#pragma once

#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/ArtifactType.h>
#include <h3mtxt/Map/Constants/SpellType.h>
#include <h3mtxt/Map/Constants/PrimarySkillType.h>
#include <h3mtxt/Map/Constants/ResourceType.h>
#include <h3mtxt/Map/Constants/RewardType.h>
#include <h3mtxt/Map/CreatureStack.h>
#include <h3mtxt/Map/SecondarySkill.h>

#include <variant>

namespace h3m
{
  template<>
  struct RewardDetails<RewardType::None>
  {};

  template<>
  struct RewardDetails<RewardType::Experience>
  {
    // The Map Editor only allows using values from [1; 99,999,999], but any signed 32-bit integer can be used here:
    // * 0 has no effect (the hero's experience remains the same).
    // * Negative experience points are handled correctly: the hero's experience decreases, and the level gets
    //   recalculated (i.e. the level can also decrease after the reward).
    std::int32_t experience {};
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
    //
    // * 0 is OKish: it doesn't change the hero's morale, but the game displays it as "Good Morale" anyway.
    //   The Map Editor displays it as "+0 Morale".
    // * Values within [4; 127] are fine; this can have a meaningful effect if, for example,
    //   the hero has creatures from 7 different towns (-5 morale).
    // * Negative values are OKish: the hero's morale will be decreased by the specified value, but
    //   the game displays it as "Good Morale" anyway. The Map Editor displays it as "+-N Morale".
    std::int8_t morale {};
  };

  template<>
  struct RewardDetails<RewardType::Luck>
  {
    // Same as with RewardType::Morale.
    std::int8_t luck {};
  };

  template<>
  struct RewardDetails<RewardType::Resource>
  {
    ResourceType type {};
    // The Map Editor only allow setting a value within [1; 32767].
    // However, the behavior is fine for all int32_t values:
    // * 0 has no effect (no resources given).
    // * Negative values reduce your current amount of this resource, but it won't go below 0.
    std::int32_t amount {};
  };

  template<>
  struct RewardDetails<RewardType::PrimarySkill>
  {
    PrimarySkillType type {};
    // The Map Editor only allows using a value within [1; 99].
    //
    // 0 is OK (no effect).
    // Negative values are a bit weird:
    // * Both the Map Editor and the game will show them like "+-N attack".
    // * If, after accepting the reward, the hero's new primary skill level becomes
    //   negative, it will be displayed as 0, and will be treated as 0 during combat.
    //   It will stay this way until you increase the level to an actually positive
    //   number.
    std::int8_t value {};
  };

  template<>
  struct RewardDetails<RewardType::SecondarySkill> : SecondarySkill
  {
  };

  template<>
  struct RewardDetails<RewardType::Artifact>
  {
    // FYI: None (0xFFFF) shouldn't be used here - it causes the game to crash when completing the quest.
    ArtifactType artifact {};
  };

  template<>
  struct RewardDetails<RewardType::Spell>
  {
    SpellType spell {};
  };

  template<>
  struct RewardDetails<RewardType::Creature> : CreatureStack
  {
    // FYI: CreatureStack::count can be negative, in which case the number of creatures in your stack will
    // decrease.
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

    // Get the 0-based index of the alternative corresponding to the given RewardType.
    // \param reward_type - type of the reward.
    // \return 0-based index of the alternative from Reward::Details that has the type
    //         RewardDetails<reward_type>, or std::variant_npos if there is no such alternative.
    static constexpr std::size_t getAlternativeIdx(RewardType reward_type) noexcept;

    Details details;
  };

  constexpr RewardType Reward::type() const noexcept
  {
    return static_cast<RewardType>(details.index());
  }

  constexpr std::size_t Reward::getAlternativeIdx(RewardType reward_type) noexcept
  {
    const std::size_t idx = static_cast<std::size_t>(reward_type);
    return idx < std::variant_size_v<Details> ? idx : std::variant_npos;
  }
}
