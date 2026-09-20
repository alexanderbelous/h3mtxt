#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/VictoryCondition.h>

#include <stdexcept>

namespace h3json
{
  template<>
  h3svg::VictoryCondition JsonReader<h3svg::VictoryCondition>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::VictoryCondition>;
    const h3svg::VictoryConditionType victory_condition_type = readField<h3svg::VictoryConditionType>(value, Fields::kType);
    const Json::Value& details_json = getJsonField(value, Fields::kDetails);
    switch (victory_condition_type)
    {
    case h3svg::VictoryConditionType::AcquireArtifact:
    {
      h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::AcquireArtifact> details{
        fromJson<h3svg::SpecialVictoryConditionBase>(details_json)
      };
      readField(details.artifact_type, details_json, "artifact_type");
      return h3svg::VictoryCondition{ .details = details };
    }
    case h3svg::VictoryConditionType::AccumulateCreatures:
    {
      h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::AccumulateCreatures> details{
        fromJson<h3svg::SpecialVictoryConditionBase>(details_json)
      };
      readField(details.creatures, details_json, "creatures");
      return h3svg::VictoryCondition{ .details = details };
    }
    case h3svg::VictoryConditionType::DefeatHero:
    {
      h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::DefeatHero> details{
        fromJson<h3svg::SpecialVictoryConditionBase>(details_json)
      };
      readField(details.hero, details_json, "hero");
      return h3svg::VictoryCondition{ .details = details };
    }
    default:
      {
        // TODO: this is an ugly hack; expose API for reading h3m::VictoryConditionDetails from JSON instead.
        const h3m::VictoryCondition victory_condition_h3m = fromJson<h3m::VictoryCondition>(value);
        return std::visit([]<h3m::VictoryConditionType T> (const h3m::VictoryConditionDetails<T>& details) -> h3svg::VictoryCondition
                          {
                            if constexpr (std::is_base_of_v<h3m::VictoryConditionDetails<T>,
                                                     h3svg::VictoryConditionDetails<T>>)
                            {
                              return h3svg::VictoryCondition{
                                .details = h3svg::VictoryConditionDetails<T>{details}
                              };
                            }
                            else
                            {
                              throw std::runtime_error("JsonReader<h3svg::VictoryCondition>: unsupported VictoryConditionType.");
                            }
                          },
                          victory_condition_h3m.details);
      }
    }
  }
}
