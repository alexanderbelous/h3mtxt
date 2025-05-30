#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/Campaign/Constants/StartingBonusType.h>
#include <h3mtxt/Campaign/Constants/StartingBonusResourceType.h>
#include <h3mtxt/Map/Constants/ArtifactType.h>
#include <h3mtxt/Map/Constants/SpellType.h>
#include <h3mtxt/Map/Constants/TownBuildingType.h>
#include <h3mtxt/Map/CreatureStack.h>
#include <h3mtxt/Map/PrimarySkills.h>
#include <h3mtxt/Map/SecondarySkill.h>

#include <cstdint>
#include <utility>
#include <variant>

namespace h3m
{
  template<>
  struct StartingBonusDetails<StartingBonusType::Spell>
  {
    // HeroType or 0xFDFF for the most powerful hero.
    std::uint16_t hero {};
    SpellType spell {};
  };

  template<>
  struct StartingBonusDetails<StartingBonusType::Creature>
  {
    // HeroType or 0xFDFF for the most powerful hero.
    std::uint16_t hero {};
    CreatureStack creature_stack;
  };

  template<>
  struct StartingBonusDetails<StartingBonusType::Building>
  {
    TownBuildingType building {};
  };

  template<>
  struct StartingBonusDetails<StartingBonusType::Artifact>
  {
    // HeroType or 0xFDFF for the most powerful hero.
    std::uint16_t hero {};
    ArtifactType artifact {};
  };

  template<>
  struct StartingBonusDetails<StartingBonusType::SpellScroll>
  {
    // HeroType or 0xFDFF for the most powerful hero.
    std::uint16_t hero {};
    SpellType spell {};
  };

  template<>
  struct StartingBonusDetails<StartingBonusType::PrimarySkills>
  {
    // HeroType or 0xFDFF for the most powerful hero.
    std::uint16_t hero {};
    PrimarySkills skills;
  };

  template<>
  struct StartingBonusDetails<StartingBonusType::SecondarySkill>
  {
    // HeroType or 0xFDFF for the most powerful hero.
    std::uint16_t hero {};
    SecondarySkill skill;
  };

  template<>
  struct StartingBonusDetails<StartingBonusType::Resource>
  {
    StartingBonusResourceType type {};
    std::uint32_t amount {};
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

    constexpr StartingBonusType type() const noexcept
    {
      return static_cast<StartingBonusType>(details.index());
    }

    // Get the 0-based index of the alternative corresponding to the given StartingBonusType.
    // \param bonus_type - input StartingBonusType.
    // \return 0-based index of the alternative from StartingBonus::Details that has the type
    //         StartingBonusDetails<bonus_type>, or std::variant_npos if there is no such alternative.
    static constexpr std::size_t getAlternativeIdx(StartingBonusType bonus_type) noexcept
    {
      const std::size_t idx = static_cast<std::size_t>(bonus_type);
      return idx < std::variant_size_v<Details> ? idx : std::variant_npos;
    }

    Details details;
  };
}
