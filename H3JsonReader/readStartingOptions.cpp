#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Campaign/StartingOptions.h>

#include <stdexcept>

namespace h3m::H3JsonReader_NS
{
  template<>
  struct JsonReader<StartingOptionsDetails<StartingOptionsType::StartingBonus>>
  {
    StartingOptionsDetails<StartingOptionsType::StartingBonus> operator()(const Json::Value& value) const
    {
      StartingOptionsDetails<StartingOptionsType::StartingBonus> details;
      readField(details.player, value, "player");
      readField(details.options, value, "options");
      return details;
    }
  };

  template<>
  struct JsonReader<StartingOptionsDetails<StartingOptionsType::HeroCrossover>>
  {
    StartingOptionsDetails<StartingOptionsType::HeroCrossover> operator()(const Json::Value& value) const
    {
      StartingOptionsDetails<StartingOptionsType::HeroCrossover> details;
      readField(details.options, value, "options");
      return details;
    }
  };

  template<>
  struct JsonReader<StartingOptionsDetails<StartingOptionsType::HeroCrossover>::Hero>
  {
    StartingOptionsDetails<StartingOptionsType::HeroCrossover>::Hero operator()(const Json::Value& value) const
    {
      StartingOptionsDetails<StartingOptionsType::HeroCrossover>::Hero hero;
      readField(hero.player, value, "player");
      readField(hero.source_scenario, value, "source_scenario");
      return hero;
    }
  };

  template<>
  struct JsonReader<StartingOptionsDetails<StartingOptionsType::StartingHero>>
  {
    StartingOptionsDetails<StartingOptionsType::StartingHero> operator()(const Json::Value& value) const
    {
      StartingOptionsDetails<StartingOptionsType::StartingHero> details;
      readField(details.options, value, "options");
      return details;
    }
  };

  template<>
  struct JsonReader<StartingOptionsDetails<StartingOptionsType::StartingHero>::Hero>
  {
    StartingOptionsDetails<StartingOptionsType::StartingHero>::Hero operator()(const Json::Value& value) const
    {
      StartingOptionsDetails<StartingOptionsType::StartingHero>::Hero hero;
      readField(hero.player, value, "player");
      readField(hero.type, value, "type");
      return hero;
    }
  };

  StartingOptions JsonReader<StartingOptions>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<StartingOptions>;
    const StartingOptionsType starting_options_type = readField<StartingOptionsType>(value, Fields::kType);
    switch (starting_options_type)
    {
    case StartingOptionsType::None:
      return StartingOptionsDetails<StartingOptionsType::None>();
    case StartingOptionsType::StartingBonus:
      return readField<StartingOptionsDetails<StartingOptionsType::StartingBonus>>(value, Fields::kDetails);
    case StartingOptionsType::HeroCrossover:
      return readField<StartingOptionsDetails<StartingOptionsType::HeroCrossover>>(value, Fields::kDetails);
    case StartingOptionsType::StartingHero:
      return readField<StartingOptionsDetails<StartingOptionsType::StartingHero>>(value, Fields::kDetails);
    default:
      throw std::runtime_error("JsonReader<StartingOptions>: invalid starting_options_type.");
    }
  }
}
