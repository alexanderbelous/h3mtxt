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

    constexpr StartingOptionsType type() const noexcept
    {
      return static_cast<StartingOptionsType>(details.index());
    }

    // Get the 0-based index of the alternative corresponding to the given StartingOptionsType.
    // \param options_type - input StartingOptionsType.
    // \return 0-based index of the alternative from StartingOptions::Details that has the type
    //         StartignOptionsDetails<options_type>, or std::variant_npos if there is no such alternative.
    static constexpr std::size_t getAlternativeIdx(StartingOptionsType options_type) noexcept
    {
      const std::size_t idx = static_cast<std::size_t>(options_type);
      return idx < std::variant_size_v<Details> ? idx : std::variant_npos;
    }

    Details details;
  };
}
