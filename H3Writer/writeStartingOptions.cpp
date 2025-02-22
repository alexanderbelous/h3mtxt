#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/H3Writer/Utils.h>
#include <h3mtxt/Campaign/StartingOptions.h>

#include <limits>
#include <stdexcept>

namespace h3m::H3Writer_NS
{
  namespace
  {
    template<StartingOptionsType T>
    void writeStartingOptionsDetails(std::ostream& stream, const StartingOptionsDetails<T>& details);

    template<>
    void writeStartingOptionsDetails<StartingOptionsType::None>(
      std::ostream& stream, const StartingOptionsDetails<StartingOptionsType::None>& details)
    {
    }

    template<>
    void writeStartingOptionsDetails<StartingOptionsType::StartingBonus>(
      std::ostream& stream, const StartingOptionsDetails<StartingOptionsType::StartingBonus>& details)
    {
      if (details.options.size() > std::numeric_limits<std::uint8_t>::max())
      {
        throw std::runtime_error("writeStartingOptionsDetails<StartingOptionsType::StartingBonus>(): too many options");
      }
      writeData(stream, details.player);
      writeData(stream, static_cast<std::uint8_t>(details.options.size()));
      for (const StartingBonus& bonus : details.options)
      {
        writeData(stream, bonus);
      }
    }

    template<>
    void writeStartingOptionsDetails<StartingOptionsType::HeroCrossover>(
      std::ostream& stream, const StartingOptionsDetails<StartingOptionsType::HeroCrossover>& details)
    {
      if (details.options.size() > std::numeric_limits<std::uint8_t>::max())
      {
        throw std::runtime_error("writeStartingOptionsDetails<StartingOptionsType::HeroCrossover>(): too many options");
      }
      writeData(stream, static_cast<std::uint8_t>(details.options.size()));
      for (const StartingOptionsDetails<StartingOptionsType::HeroCrossover>::Hero& hero : details.options)
      {
        writeData(stream, hero.player);
        writeData(stream, hero.source_scenario);
      }
    }

    template<>
    void writeStartingOptionsDetails<StartingOptionsType::StartingHero>(
      std::ostream& stream, const StartingOptionsDetails<StartingOptionsType::StartingHero>& details)
    {
      if (details.options.size() > std::numeric_limits<std::uint8_t>::max())
      {
        throw std::runtime_error("writeStartingOptionsDetails<StartingOptionsType::StartingHero>(): too many options");
      }
      writeData(stream, static_cast<std::uint8_t>(details.options.size()));
      for (const StartingOptionsDetails<StartingOptionsType::StartingHero>::Hero& hero : details.options)
      {
        writeData(stream, hero.player);
        writeData(stream, hero.type);
      }
    }
  }

  void H3Writer<StartingOptions>::operator()(std::ostream& stream, const StartingOptions& options) const
  {
    writeData(stream, options.type());
    std::visit([&stream] <StartingOptionsType T> (const StartingOptionsDetails<T> &details)
               { writeStartingOptionsDetails<T>(stream, details); },
               options.details);
  }
}
