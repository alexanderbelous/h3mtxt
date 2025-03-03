#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/H3JsonReader/VariantJsonReader.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Campaign/StartingOptions.h>

#include <stdexcept>

namespace h3m::H3JsonReader_NS
{
  template<>
  struct JsonReader<StartingOptionsDetails<StartingOptionsType::None>>
  {
    StartingOptionsDetails<StartingOptionsType::None> operator()(const Json::Value&) const
    {
      return {};
    }
  };

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
    StartingOptions starting_options;
    if (starting_options_type != StartingOptionsType::None)
    {
      VariantJsonReader<StartingOptions::Details> variant_reader;
      starting_options.details = variant_reader(getJsonField(value, Fields::kDetails),
                                                StartingOptions::getAlternativeIdx(starting_options_type));
    }
    return starting_options;
  }
}
