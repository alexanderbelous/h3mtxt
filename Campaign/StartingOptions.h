#pragma once

#include <h3mtxt/Campaign/StartingBonus.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>

#include <cstdint>
#include <utility>
#include <variant>
#include <vector>

namespace h3m
{
  enum class StartingOptionsType : std::uint8_t
  {
    // TODO: apparently 0 is also a valid value, indicating no options.
    // The Campaign Editor doesn't allow selecting it, though.
    // Check, and if this is correct, add an enum constant.
    StartingBonus = 1,
    HeroCrossover = 2,
    StartingHero = 3
  };

  template<StartingOptionsType>
  struct StartingOptionsDetails;

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

    constexpr StartingOptions() noexcept = default;

    template<StartingOptionsType T>
    constexpr StartingOptions(const StartingOptionsDetails<T>& details):
      details(details)
    {}

    template<StartingOptionsType T>
    constexpr StartingOptions(StartingOptionsDetails<T>&& details) :
      details(std::move(details))
    {}

    constexpr StartingOptionsType type() const noexcept;

    Details details;
  };

  constexpr StartingOptionsType StartingOptions::type() const noexcept
  {
    return static_cast<StartingOptionsType>(details.index() + 1);
  }
}
