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
  h3m::HeroCrossoverOption JsonReader2<h3m::HeroCrossoverOption>::operator()() const
  {
    h3m::HeroCrossoverOption option;
    using Fields = FieldNames<decltype(option)>;
    readField(Fields::kPlayer, option.player);
    readField(Fields::kSourceScenario, option.source_scenario);
    return option;
  }

  template<>
  h3m::StartingHeroOption JsonReader2<h3m::StartingHeroOption>::operator()() const
  {
    h3m::StartingHeroOption option;
    using Fields = FieldNames<decltype(option)>;
    readField(Fields::kPlayer, option.player);
    readField(Fields::kType, option.type);
    return option;
  }

  template<StartingOptionsType T>
  StartingOptionsDetails<T> JsonReader2<StartingOptionsDetails<T>>::operator()() const
  {
    using Fields = FieldNames<StartingOptionsDetails<T>>;
    StartingOptionsDetails<T> details;
    if constexpr (T == StartingOptionsType::None)
    {
      // No fields.
    }
    else if constexpr (T == StartingOptionsType::StartingBonus)
    {
      readField(Fields::kPlayer, details.player);
      readField(Fields::kOptions, details.options);
    }
    else if constexpr (T == StartingOptionsType::HeroCrossover)
    {
      readField(Fields::kOptions, details.options);
    }
    else if constexpr (T == StartingOptionsType::StartingHero)
    {
      readField(Fields::kOptions, details.options);
    }
    else
    {
      static_assert(false, "Invalid StartingOptionsType.");
    }
    return details;
  }

  template<>
  StartingOptions JsonReader2<StartingOptions>::operator()() const
  {
    using Fields = FieldNames<StartingOptions>;
    const StartingOptionsType starting_options_type = readField<StartingOptionsType>(Fields::kType);
    return StartingOptions{
      .details = VariantJsonReader<StartingOptions::Details>{}(getField(Fields::kDetails),
                                                               StartingOptions::getAlternativeIdx(starting_options_type))
    };
  }
}
