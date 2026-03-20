#include <h3mtxt/H3JsonReader/H3CJsonReader/H3CJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3C.h>
#include <h3mtxt/Campaign/StartingOptions.h>

#include <stdexcept>

namespace h3json
{
  using ::h3m::StartingOptions;
  using ::h3m::StartingOptionsDetails;
  using ::h3m::StartingOptionsType;

  StartingOptionsDetails<StartingOptionsType::None>
  JsonReader<StartingOptionsDetails<StartingOptionsType::None>>::operator()(const Json::Value&) const
  {
    return {};
  }

  StartingOptionsDetails<StartingOptionsType::StartingBonus>
  JsonReader<StartingOptionsDetails<StartingOptionsType::StartingBonus>>::operator()(const Json::Value& value) const
  {
    StartingOptionsDetails<StartingOptionsType::StartingBonus> details;
    readField(details.player, value, "player");
    readField(details.options, value, "options");
    return details;
  }

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

  StartingOptionsDetails<StartingOptionsType::HeroCrossover>
  JsonReader<StartingOptionsDetails<StartingOptionsType::HeroCrossover>>::operator()(const Json::Value& value) const
  {
    StartingOptionsDetails<StartingOptionsType::HeroCrossover> details;
    readField(details.options, value, "options");
    return details;
  }

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

  StartingOptionsDetails<StartingOptionsType::StartingHero>
  JsonReader<StartingOptionsDetails<StartingOptionsType::StartingHero>>::operator()(const Json::Value& value) const
  {
    StartingOptionsDetails<StartingOptionsType::StartingHero> details;
    readField(details.options, value, "options");
    return details;
  }

  namespace
  {
    StartingOptions::Details readStartingOptionsDetails(const Json::Value& value,
                                                        StartingOptionsType starting_options_type)
    {
      switch (starting_options_type)
      {
        case StartingOptionsType::None:
          return {};
        case StartingOptionsType::StartingBonus:
          return fromJson<StartingOptionsDetails<StartingOptionsType::StartingBonus>>(value);
        case StartingOptionsType::HeroCrossover:
          return fromJson<StartingOptionsDetails<StartingOptionsType::HeroCrossover>>(value);
        case StartingOptionsType::StartingHero:
          return fromJson<StartingOptionsDetails<StartingOptionsType::StartingHero>>(value);
        default:
          throw std::runtime_error("JsonReader<StartingOptions>: invalid starting_options_type.");
      }
    }
  }

  StartingOptions JsonReader<StartingOptions>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<StartingOptions>;
    const StartingOptionsType starting_options_type = readField<StartingOptionsType>(value, Fields::kType);
    if (starting_options_type == StartingOptionsType::None)
    {
      return StartingOptions{};
    }
    return StartingOptions{ readStartingOptionsDetails(getJsonField(value, Fields::kDetails), starting_options_type) };
  }
}
