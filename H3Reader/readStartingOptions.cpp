#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/Campaign/StartingOptions.h>

#include <stdexcept>

namespace h3m::H3Reader_NS
{
  namespace
  {
    StartingOptionsDetails<StartingOptionsType::StartingBonus> readStartingBonusOptions(std::istream& stream)
    {
      StartingOptionsDetails<StartingOptionsType::StartingBonus> details;
      details.player = readEnum<PlayerColor>(stream);
      const std::uint8_t num_bonuses = readInt<std::uint8_t>(stream);
      details.options.reserve(num_bonuses);
      for (std::uint8_t i = 0; i < num_bonuses; ++i)
      {
        details.options.push_back(readStartingBonus(stream));
      }
      return details;
    }

    StartingOptionsDetails<StartingOptionsType::HeroCrossover> readHeroCrossoverOptions(std::istream& stream)
    {
      StartingOptionsDetails<StartingOptionsType::HeroCrossover> details;
      const std::uint8_t num_heroes = readInt<std::uint8_t>(stream);
      details.options.reserve(num_heroes);
      for (std::uint8_t i = 0; i < num_heroes; ++i)
      {
        StartingOptionsDetails<StartingOptionsType::HeroCrossover>::Hero hero;
        hero.player = readEnum<PlayerColor>(stream);
        hero.source_scenario = readInt<std::uint8_t>(stream);
        details.options.push_back(std::move(hero));
      }
      return details;
    }

    StartingOptionsDetails<StartingOptionsType::StartingHero> readStartingHeroOptions(std::istream& stream)
    {
      StartingOptionsDetails<StartingOptionsType::StartingHero> details;
      const std::uint8_t num_heroes = readInt<std::uint8_t>(stream);
      details.options.reserve(num_heroes);
      for (std::uint8_t i = 0; i < num_heroes; ++i)
      {
        StartingOptionsDetails<StartingOptionsType::StartingHero>::Hero hero;
        hero.player = readEnum<PlayerColor>(stream);
        hero.type = readInt<std::uint16_t>(stream);
        details.options.push_back(std::move(hero));
      }
      return details;
    }
  }

  StartingOptions readStartingOptions(std::istream& stream)
  {
    const StartingOptionsType starting_options_type = readEnum<StartingOptionsType>(stream);
    switch (starting_options_type)
    {
    case StartingOptionsType::None:
      return StartingOptions{};
    case StartingOptionsType::StartingBonus:
      return StartingOptions{ readStartingBonusOptions(stream) };
    case StartingOptionsType::HeroCrossover:
      return StartingOptions{ readHeroCrossoverOptions(stream) };
    case StartingOptionsType::StartingHero:
      return StartingOptions{ readStartingHeroOptions(stream) };
    default:
      throw std::runtime_error("Invalid starting_options_type.");
    }
  }
}
