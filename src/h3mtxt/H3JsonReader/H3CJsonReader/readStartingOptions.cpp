#include <h3mtxt/H3JsonReader/H3CJsonReader/H3CJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/VariantJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3C.h>
#include <h3mtxt/Campaign/StartingOptions.h>

namespace h3json
{
  using ::h3m::StartingOptions;
  using ::h3m::StartingOptionsDetails;
  using ::h3m::StartingOptionsType;

  template<>
  h3m::HeroCrossoverOption JsonReader<h3m::HeroCrossoverOption>::operator()(const Json::Value& value) const
  {
    h3m::HeroCrossoverOption option;
    using Fields = FieldNames<decltype(option)>;
    readField(option.player, value, Fields::kPlayer);
    readField(option.source_scenario, value, Fields::kSourceScenario);
    return option;
  }

  template<>
  h3m::StartingHeroOption JsonReader<h3m::StartingHeroOption>::operator()(const Json::Value& value) const
  {
    h3m::StartingHeroOption option;
    using Fields = FieldNames<decltype(option)>;
    readField(option.player, value, Fields::kPlayer);
    readField(option.type, value, Fields::kType);
    return option;
  }

  template<>
  StartingOptionsDetails<StartingOptionsType::None>
  JsonReader<StartingOptionsDetails<StartingOptionsType::None>>::operator()(const Json::Value&) const
  {
    return {};
  }

  template<>
  StartingOptionsDetails<StartingOptionsType::StartingBonus>
  JsonReader<StartingOptionsDetails<StartingOptionsType::StartingBonus>>::operator()(const Json::Value& value) const
  {
    StartingOptionsDetails<StartingOptionsType::StartingBonus> details;
    using Fields = FieldNames<decltype(details)>;
    readField(details.player, value, Fields::kPlayer);
    readField(details.options, value, Fields::kOptions);
    return details;
  }

  template<>
  StartingOptionsDetails<StartingOptionsType::HeroCrossover>
  JsonReader<StartingOptionsDetails<StartingOptionsType::HeroCrossover>>::operator()(const Json::Value& value) const
  {
    StartingOptionsDetails<StartingOptionsType::HeroCrossover> details;
    using Fields = FieldNames<decltype(details)>;
    readField(details.options, value, Fields::kOptions);
    return details;
  }

  template<>
  StartingOptionsDetails<StartingOptionsType::StartingHero>
  JsonReader<StartingOptionsDetails<StartingOptionsType::StartingHero>>::operator()(const Json::Value& value) const
  {
    StartingOptionsDetails<StartingOptionsType::StartingHero> details;
    using Fields = FieldNames<decltype(details)>;
    readField(details.options, value, Fields::kOptions);
    return details;
  }

  template<>
  StartingOptions JsonReader<StartingOptions>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<StartingOptions>;
    const StartingOptionsType starting_options_type = readField<StartingOptionsType>(value, Fields::kType);
    return StartingOptions{
      .details = VariantJsonReader<StartingOptions::Details>{}(getJsonField(value, Fields::kDetails),
                                                               StartingOptions::getAlternativeIdx(starting_options_type))
    };
  }
}
