#include <h3mtxt/H3Writer/H3CWriter/H3CWriter.h>
#include <h3mtxt/Campaign/StartingOptions.h>

namespace h3m
{
  void H3CWriter::writeData(const HeroCrossoverOption& option) const
  {
    writeData(option.player);
    writeData(option.source_scenario);
  }

  void H3CWriter::writeData(const StartingHeroOption& option) const
  {
    writeData(option.player);
    writeData(option.type);
  }

  template<>
  void H3CWriter::writeData(const StartingOptionsDetails<StartingOptionsType::None>&) const
  {
  }

  template<>
  void H3CWriter::writeData(const StartingOptionsDetails<StartingOptionsType::StartingBonus>& details) const
  {
    writeData(details.player);
    writeData(safeCastVectorSize<std::uint8_t>(details.options.size()));
    for (const StartingBonus& bonus : details.options)
    {
      writeData(bonus);
    }
  }

  template<>
  void H3CWriter::writeData(const StartingOptionsDetails<StartingOptionsType::HeroCrossover>& details) const
  {
    writeData(safeCastVectorSize<std::uint8_t>(details.options.size()));
    for (const HeroCrossoverOption& option : details.options)
    {
      writeData(option);
    }
  }

  template<>
  void H3CWriter::writeData(const StartingOptionsDetails<StartingOptionsType::StartingHero>& details) const
  {
    writeData(safeCastVectorSize<std::uint8_t>(details.options.size()));
    for (const StartingHeroOption& option : details.options)
    {
      writeData(option);
    }
  }

  void H3CWriter::writeData(const StartingOptions& options) const
  {
    writeData(options.type());
    std::visit([this] <StartingOptionsType T> (const StartingOptionsDetails<T>& details)
               { writeData(details); },
               options.details);
  }
}
