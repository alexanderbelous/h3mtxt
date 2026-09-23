#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Map/Constants/ArtifactType.h>
#include <h3mtxt/Map/Constants/CreatureType.h>
#include <h3mtxt/Map/Constants/PrimarySkillType.h>
#include <h3mtxt/Map/Constants/ResourceType.h>
#include <h3mtxt/Map/Constants/RewardType.h>
#include <h3mtxt/Map/Constants/SecondarySkillType.h>
#include <h3mtxt/Map/Constants/SpellType.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/Map/Utils/TypedQuantity.h>

#include <cstdint>
#include <variant>

namespace h3svg
{
  template<>
  struct RewardDetails<RewardType::None>
  {
    constexpr bool operator==(const RewardDetails&) const noexcept = default;

    ReservedData<8> reserved;
  };

  template<>
  struct RewardDetails<RewardType::Experience>
  {
    constexpr bool operator==(const RewardDetails&) const noexcept = default;

    std::int32_t experience {};
    ReservedData<4> reserved;
  };

  template<>
  struct RewardDetails<RewardType::SpellPoints>
  {
    constexpr bool operator==(const RewardDetails&) const noexcept = default;

    std::int32_t spell_points {};
    ReservedData<4> reserved;
  };

  template<>
  struct RewardDetails<RewardType::Morale>
  {
    constexpr bool operator==(const RewardDetails&) const noexcept = default;

    std::int32_t morale {};
    ReservedData<4> reserved;
  };

  template<>
  struct RewardDetails<RewardType::Luck>
  {
    constexpr bool operator==(const RewardDetails&) const noexcept = default;

    std::int32_t luck {};
    ReservedData<4> reserved;
  };

  template<>
  struct RewardDetails<RewardType::Resource>
  {
    constexpr bool operator==(const RewardDetails&) const noexcept = default;

    TypedQuantity<ResourceType32, std::int32_t> resource;
  };

  template<>
  struct RewardDetails<RewardType::PrimarySkill>
  {
    constexpr bool operator==(const RewardDetails&) const noexcept = default;

    PrimarySkillType32 type {};
    std::int32_t value {};
  };

  template<>
  struct RewardDetails<RewardType::SecondarySkill>
  {
    constexpr bool operator==(const RewardDetails&) const noexcept = default;

    SecondarySkillType32 type {};
    std::int32_t level {};
  };

  template<>
  struct RewardDetails<RewardType::Artifact>
  {
    constexpr bool operator==(const RewardDetails&) const noexcept = default;

    ArtifactType32 artifact {};
    ReservedData<4> reserved;
  };

  template<>
  struct RewardDetails<RewardType::Spell>
  {
    constexpr bool operator==(const RewardDetails&) const noexcept = default;

    SpellType32 spell {};
    ReservedData<4> reserved;
  };

  template<>
  struct RewardDetails<RewardType::Creatures>
  {
    constexpr bool operator==(const RewardDetails&) const noexcept = default;

    TypedQuantity<CreatureType32, std::int32_t> creatures;
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
      RewardDetails<RewardType::Creatures>
    >;

    constexpr bool operator==(const Reward&) const noexcept = default;

    // Returns the 0-based index of the alternative corresponding to the given RewardType.
    // \param reward_type - type of the reward.
    // \return 0-based index of the alternative from Reward::Details that has the type
    //         RewardDetails<reward_type>, or std::variant_npos if there is no such alternative.
    static constexpr std::size_t getAlternativeIdx(RewardType reward_type) noexcept;

    // \return the type of the reward.
    constexpr RewardType type() const noexcept;

    Details details {};
  };

  constexpr std::size_t Reward::getAlternativeIdx(RewardType reward_type) noexcept
  {
    const std::size_t idx = static_cast<std::size_t>(reward_type);
    return idx < std::variant_size_v<Details> ? idx : std::variant_npos;
  }

  constexpr RewardType Reward::type() const noexcept
  {
    return static_cast<RewardType>(details.index());
  }
}
