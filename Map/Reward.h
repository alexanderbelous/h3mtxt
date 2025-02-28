#pragma once

#include <h3mtxt/Map/MapFwd.h>
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
