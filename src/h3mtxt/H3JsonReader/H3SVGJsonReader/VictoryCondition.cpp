#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/VariantJsonReader.h>
#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/VictoryCondition.h>

#include <stdexcept>
#include <type_traits>

namespace h3json
{
  template<h3svg::VictoryConditionType T>
  h3svg::VictoryConditionDetails<T>
  JsonReader<h3svg::VictoryConditionDetails<T>>::operator()(const Json::Value& value) const
  {
    if constexpr (std::is_base_of_v<h3m::VictoryConditionDetails<T>, h3svg::VictoryConditionDetails<T>> &&
                  sizeof(h3svg::VictoryConditionDetails<T>) == sizeof(h3m::VictoryConditionDetails<T>))
    {
      return h3svg::VictoryConditionDetails<T> { fromJson<h3m::VictoryConditionDetails<T>>(value) };
    }
    else
    {
      h3svg::VictoryConditionDetails<T> details{ fromJson<h3svg::SpecialVictoryConditionBase>(value) };
      if constexpr (T == h3svg::VictoryConditionType::AcquireArtifact)
      {
        readField(details.artifact_type, value, "artifact_type");
      }
      else if constexpr (T == h3svg::VictoryConditionType::AccumulateCreatures)
      {
        readField(details.creatures, value, "creatures");
      }
      else if constexpr (T == h3svg::VictoryConditionType::DefeatHero)
      {
        readField(details.hero, value, "hero");
      }
      else
      {
        static_assert(false, "Invalid VictoryConditionType.");
      }
      return details;
    }
  }

  template<>
  h3svg::VictoryCondition JsonReader<h3svg::VictoryCondition>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::VictoryCondition>;
    const h3svg::VictoryConditionType victory_condition_type = readField<h3svg::VictoryConditionType>(value, Fields::kType);
    const std::size_t variant_alternative_idx = h3svg::VictoryCondition::getAlternativeIdx(victory_condition_type);
    if (variant_alternative_idx == std::variant_npos)
    {
      throw std::runtime_error("JsonReader<h3svg::VictoryCondition>: invalid victory_condition_type");
    }
    return h3svg::VictoryCondition{
      .details = VariantJsonReader<h3svg::VictoryCondition::Details>{}(getJsonField(value, Fields::kDetails),
                                                                       variant_alternative_idx)
    };
  }
}
