#include <h3mtxt/H3Reader/H3CReader/H3CReader.h>
#include <h3mtxt/Campaign/StartingOptions.h>

#include <stdexcept>

namespace h3m
{
  HeroCrossoverOption H3CReader::readHeroCrossoverOption() const
  {
    HeroCrossoverOption option;
    option.player = readEnum<PlayerColor>();
    option.source_scenario = readInt<std::uint8_t>();
    return option;
  }

  StartingHeroOption H3CReader::readStartingHeroOption() const
  {
    StartingHeroOption option;
    option.player = readEnum<PlayerColor>();
    option.type = readInt<std::uint16_t>();
    return option;
  }

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
    const std::uint8_t num_options = readInt<std::uint8_t>();
    details.options.reserve(num_options);
    for (std::size_t i = 0; i < num_options; ++i)
    {
      details.options.push_back(readStartingBonus());
    }
    return details;
  }

  template<>
  StartingOptionsDetails<StartingOptionsType::HeroCrossover> H3CReader::readStartingOptionsDetails() const
  {
    StartingOptionsDetails<StartingOptionsType::HeroCrossover> details;
    const std::uint8_t num_options = readInt<std::uint8_t>();
    details.options.reserve(num_options);
    for (std::size_t i = 0; i < num_options; ++i)
    {
      details.options.push_back(readHeroCrossoverOption());
    }
    return details;
  }

  template<>
  StartingOptionsDetails<StartingOptionsType::StartingHero> H3CReader::readStartingOptionsDetails() const
  {
    StartingOptionsDetails<StartingOptionsType::StartingHero> details;
    const std::uint8_t num_options = readInt<std::uint8_t>();
    details.options.reserve(num_options);
    for (std::size_t i = 0; i < num_options; ++i)
    {
      details.options.push_back(readStartingHeroOption());
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
