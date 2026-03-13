#include <h3mtxt/H3Reader/H3CReader/H3CReader.h>
#include <h3mtxt/Campaign/StartingOptions.h>

#include <stdexcept>

namespace h3m
{
  template<>
  StartingOptionsDetails<StartingOptionsType::None> H3CReader::readStartingOptionsDetails() const
  {
    return {};
  }

  template<>
  StartingOptionsDetails<StartingOptionsType::StartingBonus> H3CReader::readStartingOptionsDetails() const
  {
    StartingOptionsDetails<StartingOptionsType::StartingBonus> details;
    details.player = readEnum<PlayerColor>();
    const std::uint8_t num_bonuses = readInt<std::uint8_t>();
    details.options.reserve(num_bonuses);
    for (std::uint8_t i = 0; i < num_bonuses; ++i)
    {
      details.options.push_back(readStartingBonus());
    }
    return details;
  }

  template<>
  StartingOptionsDetails<StartingOptionsType::HeroCrossover> H3CReader::readStartingOptionsDetails() const
  {
    StartingOptionsDetails<StartingOptionsType::HeroCrossover> details;
    const std::uint8_t num_heroes = readInt<std::uint8_t>();
    details.options.reserve(num_heroes);
    for (std::uint8_t i = 0; i < num_heroes; ++i)
    {
      StartingOptionsDetails<StartingOptionsType::HeroCrossover>::Hero hero;
      hero.player = readEnum<PlayerColor>();
      hero.source_scenario = readInt<std::uint8_t>();
      details.options.push_back(std::move(hero));
    }
    return details;
  }

  template<>
  StartingOptionsDetails<StartingOptionsType::StartingHero> H3CReader::readStartingOptionsDetails() const
  {
    StartingOptionsDetails<StartingOptionsType::StartingHero> details;
    const std::uint8_t num_heroes = readInt<std::uint8_t>();
    details.options.reserve(num_heroes);
    for (std::uint8_t i = 0; i < num_heroes; ++i)
    {
      StartingOptionsDetails<StartingOptionsType::StartingHero>::Hero hero;
      hero.player = readEnum<PlayerColor>();
      hero.type = readInt<std::uint16_t>();
      details.options.push_back(std::move(hero));
    }
    return details;
  }

  StartingOptions H3CReader::readStartingOptions() const
  {
    const StartingOptionsType starting_options_type = readEnum<StartingOptionsType>();
    switch (starting_options_type)
    {
    case StartingOptionsType::None:
      return StartingOptions{ readStartingOptionsDetails<StartingOptionsType::None>() };
    case StartingOptionsType::StartingBonus:
      return StartingOptions{ readStartingOptionsDetails<StartingOptionsType::StartingBonus>() };
    case StartingOptionsType::HeroCrossover:
      return StartingOptions{ readStartingOptionsDetails<StartingOptionsType::HeroCrossover>() };
    case StartingOptionsType::StartingHero:
      return StartingOptions{ readStartingOptionsDetails<StartingOptionsType::StartingHero>() };
    default:
      throw std::runtime_error("Invalid starting_options_type.");
    }
  }
}
