#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/VictoryCondition.h>
#include <h3mtxt/Medea/Medea.h>

#include <type_traits>

namespace Medea_NS
{
  template<h3svg::VictoryConditionType T>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<T>>::operator()(
    FieldsWriter& out, const h3svg::VictoryConditionDetails<T>& details) const
  {
    if constexpr (std::is_base_of_v<h3m::VictoryConditionDetails<T>, h3svg::VictoryConditionDetails<T>> &&
                  sizeof(h3svg::VictoryConditionDetails<T>) == sizeof(h3m::VictoryConditionDetails<T>))
    {
      // Reuse H3MJsonWriter.
      JsonObjectWriter<h3m::VictoryConditionDetails<T>>{}(out, details);
    }
    else
    {
      JsonObjectWriter<h3svg::SpecialVictoryConditionBase>{}(out, details);

      if constexpr (T == h3svg::VictoryConditionType::AcquireArtifact)
      {
        out.writeField("artifact_type", details.artifact_type);
      }
      else if constexpr (T == h3svg::VictoryConditionType::AccumulateCreatures)
      {
        out.writeField("creatures", details.creatures);
      }
      else if constexpr (T == h3svg::VictoryConditionType::DefeatHero)
      {
        out.writeField("hero", details.hero);
      }
      else
      {
        static_assert(false, "Invalid VictoryConditionType.");
      }
    }
  }

  template<>
  void JsonObjectWriter<h3svg::VictoryCondition>::operator()(FieldsWriter& out,
                                                             const h3svg::VictoryCondition& victory_condition) const
  {
    using Fields = h3json::FieldNames<h3svg::VictoryCondition>;
    out.writeField(Fields::kType, victory_condition.type());
    if (victory_condition.type() != h3svg::VictoryConditionType::Normal)
    {
      std::visit([&out] <h3svg::VictoryConditionType T> (const h3svg::VictoryConditionDetails<T>& details)
                 { out.writeField(Fields::kDetails, details); },
                 victory_condition.details);
    }
  }
}
