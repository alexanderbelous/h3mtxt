#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/Campaign/Constants/StartingBonusType.h>
#include <h3mtxt/Campaign/Constants/StartingBonusResourceType.h>
#include <h3mtxt/Map/Constants/ArtifactType.h>
#include <h3mtxt/Map/Constants/PrimarySkillType.h>
#include <h3mtxt/Map/Constants/SpellType.h>
#include <h3mtxt/Map/Constants/TownBuildingType.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>
#include <h3mtxt/Map/Utils/TypedQuantity.h>
#include <h3mtxt/Map/CreatureStack.h>
#include <h3mtxt/Map/SecondarySkill.h>

#include <cstdint>
#include <utility>
#include <variant>

namespace h3m
{
  template<>
  struct StartingBonusDetails<StartingBonusType::Spell>
  {
    constexpr bool operator==(const StartingBonusDetails&) const noexcept = default;

    // HeroType or 2 special values:
    // * 0xFFFD (-3) for the Most Powerful Hero.
    // * 0xFFFE (-2) for the Generated Hero
    std::uint16_t hero {};
    SpellType spell {};
  };

  template<>
  struct StartingBonusDetails<StartingBonusType::Creature>
  {
    constexpr bool operator==(const StartingBonusDetails&) const noexcept = default;

    // HeroType or 2 special values:
    // * 0xFFFD (-3) for the Most Powerful Hero.
    // * 0xFFFE (-2) for the Generated Hero
    std::uint16_t hero {};
    CreatureStack creature_stack;
  };

  template<>
  struct StartingBonusDetails<StartingBonusType::Building>
  {
    constexpr bool operator==(const StartingBonusDetails&) const noexcept = default;

    TownBuildingType building {};
  };

  template<>
  struct StartingBonusDetails<StartingBonusType::Artifact>
  {
    constexpr bool operator==(const StartingBonusDetails&) const noexcept = default;

    // HeroType or 2 special values:
    // * 0xFFFD (-3) for the Most Powerful Hero.
    // * 0xFFFE (-2) for the Generated Hero
    std::uint16_t hero {};
    ArtifactType artifact {};
  };

  template<>
  struct StartingBonusDetails<StartingBonusType::SpellScroll>
  {
    constexpr bool operator==(const StartingBonusDetails&) const noexcept = default;

    // HeroType or 2 special values:
    // * 0xFFFD (-3) for the Most Powerful Hero.
    // * 0xFFFE (-2) for the Generated Hero
    std::uint16_t hero {};
    SpellType spell {};
  };

  template<>
  struct StartingBonusDetails<StartingBonusType::PrimarySkills>
  {
    constexpr bool operator==(const StartingBonusDetails&) const noexcept = default;

    // HeroType or 2 special values:
    // * 0xFFFD (-3) for the Most Powerful Hero.
    // * 0xFFFE (-2) for the Generated Hero
    std::uint16_t hero {};
    PrimarySkills skills;
  };

  template<>
  struct StartingBonusDetails<StartingBonusType::SecondarySkill>
  {
    constexpr bool operator==(const StartingBonusDetails&) const noexcept = default;

    // HeroType or 2 special values:
    // * 0xFFFD (-3) for the Most Powerful Hero.
    // * 0xFFFE (-2) for the Generated Hero
    std::uint16_t hero {};
    SecondarySkill skill;
  };

  template<>
  struct StartingBonusDetails<StartingBonusType::Resource> : TypedQuantity<StartingBonusResourceType, std::int32_t>
  {
    constexpr bool operator==(const StartingBonusDetails&) const noexcept = default;

    // The Campaign Editor only allows setting a quantity from [1; 32767],
    // but any signed 32-bit value can be used here.
  };

  struct StartingBonus
  {
    using Details = std::variant<
      StartingBonusDetails<StartingBonusType::Spell>,
      StartingBonusDetails<StartingBonusType::Creature>,
      StartingBonusDetails<StartingBonusType::Building>,
      StartingBonusDetails<StartingBonusType::Artifact>,
      StartingBonusDetails<StartingBonusType::SpellScroll>,
      StartingBonusDetails<StartingBonusType::PrimarySkills>,
      StartingBonusDetails<StartingBonusType::SecondarySkill>,
      StartingBonusDetails<StartingBonusType::Resource>
    >;

    constexpr bool operator==(const StartingBonus&) const noexcept = default;

    // \return the type of the bonus.
    constexpr StartingBonusType type() const noexcept;

    // Returns the 0-based index of the alternative corresponding to the given StartingBonusType.
    // \param bonus_type - input StartingBonusType.
    // \return 0-based index of the alternative from StartingBonus::Details that has the type
    //         StartingBonusDetails<bonus_type>, or std::variant_npos if there is no such alternative.
    static constexpr std::size_t getAlternativeIdx(StartingBonusType bonus_type) noexcept;

    Details details;
  };

  constexpr StartingBonusType StartingBonus::type() const noexcept
  {
    return static_cast<StartingBonusType>(details.index());
  }

  constexpr std::size_t StartingBonus::getAlternativeIdx(StartingBonusType bonus_type) noexcept
  {
    const std::size_t idx = static_cast<std::size_t>(bonus_type);
    return idx < std::variant_size_v<Details> ? idx : std::variant_npos;
  }
}
