#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/Campaign/Constants/StartingOptionsType.h>
#include <h3mtxt/Campaign/StartingBonus.h>
#include <h3mtxt/Map/Constants/PlayerColor.h>

#include <cstdint>
#include <utility>
#include <variant>
#include <vector>

namespace h3m
{
  template<>
  struct StartingOptionsDetails<StartingOptionsType::None>
  {
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
      StartingOptionsDetails<StartingOptionsType::None>,
      StartingOptionsDetails<StartingOptionsType::StartingBonus>,
      StartingOptionsDetails<StartingOptionsType::HeroCrossover>,
      StartingOptionsDetails<StartingOptionsType::StartingHero>
    >;

    // Constructs a StartingOptions object holding a
    // StartingOptionsDetails<StartingOptionsType::None> alternative.
    constexpr StartingOptions() noexcept = default;

    template<StartingOptionsType T>
    constexpr StartingOptions(const StartingOptionsDetails<T>& details):
      details(details)
    {}

    template<StartingOptionsType T>
    constexpr StartingOptions(StartingOptionsDetails<T>&& details) :
      details(std::move(details))
    {}

    constexpr StartingOptionsType type() const noexcept
    {
      return static_cast<StartingOptionsType>(details.index());
    }

    Details details;
  };
}
