#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/Campaign/Constants/StartingBonusType.h>
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
    // TODO: replace with an enum. This is a superset of ResourceType:
    // 0xFD means wood+ore; 0xFE means mercury+sulfur+crystal+gems.
    // TODO: check if there are other valid values.
    std::uint8_t type {};
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

    constexpr StartingBonus() noexcept = default;

    template<StartingBonusType T>
    constexpr StartingBonus(const StartingBonusDetails<T>& details):
      details(details)
    {}

    template<StartingBonusType T>
    constexpr StartingBonus(StartingBonusDetails<T>&& details):
      details(std::move(details))
    {}

    constexpr StartingBonusType type() const noexcept
    {
      return static_cast<StartingBonusType>(details.index());
    }

    Details details;
  };
}
