#pragma once

#include <h3mtxt/Map/Constants/PlayerColor.h>
#include <h3mtxt/Map/Constants/SpellType.h>

#include <cstdint>
#include <variant>
#include <vector>

namespace h3m
{
  enum class StartingOptionsType : std::uint8_t
  {
    StartingBonus = 1,
    HeroCrossover = 2,
    StartingHero = 3
  };

  template<StartingOptionsType>
  struct StartingOptionsDetails;

  enum class StartingBonusType : std::uint8_t
  {
    Spell = 0,
    Creature = 1,
    Building = 2,
    Artifact = 3,
    SpellScroll = 4,
    PrimarySkills = 5,
    SecondarySkill = 6,
    Resource = 7,
  };

  template<StartingBonusType>
  struct StartingBonusDetails;

  template<>
  struct StartingBonusDetails<StartingBonusType::Spell>
  {
    // HeroType or 0xFDFF for the most powerful hero.
    std::uint16_t hero {};
    SpellType spell {};
  };

  struct StartingBonus
  {
    using Details = std::variant<
      StartingBonusDetails<StartingBonusType::Spell>
      // TODO: add the rest
    >;

    Details details;
  };

  template<>
  struct StartingOptionsDetails<StartingOptionsType::StartingBonus>
  {
    PlayerColor player {};
    // Size is serialized as std::uint8_t.
    std::vector<StartingBonus> options;
  };

  template<>
  struct StartingOptionsDetails<StartingOptionsType::HeroCrossover>
  {
    struct Hero
    {
      PlayerColor player {};
      std::uint8_t source_scenario {};
    };

    // Size is serialized as std::uint8_t.
    std::vector<Hero> options;
  };

  template<>
  struct StartingOptionsDetails<StartingOptionsType::StartingHero>
  {
    struct Hero
    {
      PlayerColor player{};
      // HeroType or 0xFFFF if random.
      std::uint16_t type{};
    };

    // Size is serialized as std::uint8_t.
    std::vector<Hero> options;
  };

  struct StartingOptions
  {
    using Details = std::variant<
      StartingOptionsDetails<StartingOptionsType::StartingBonus>,
      StartingOptionsDetails<StartingOptionsType::HeroCrossover>,
      StartingOptionsDetails<StartingOptionsType::StartingHero>
    >;

    constexpr StartingOptionsType type() const noexcept;

    Details details;
  };

  constexpr StartingOptionsType StartingOptions::type() const noexcept
  {
    return static_cast<StartingOptionsType>(details.index() + 1);
  }
}
