#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/LossCondition.h>
#include <h3mtxt/Medea/Medea.h>

#include <type_traits>

namespace Medea_NS
{
  template<h3svg::LossConditionType T>
  void JsonObjectWriter<h3svg::LossConditionDetails<T>>::operator()(
    FieldsWriter& out, const h3svg::LossConditionDetails<T>& details) const
  {
    if constexpr (T == h3svg::LossConditionType::LoseHero)
    {
      using Fields = h3json::FieldNames<h3svg::LossConditionDetails<T>>;
      out.writeField(Fields::kHero, details.hero);
    }
    else
    {
      // Sanity checks.
      static_assert(std::is_base_of_v<h3m::LossConditionDetails<T>, h3svg::LossConditionDetails<T>>,
                    "h3svg::LossConditionDetails<T> must be derived from h3m::LossConditionDetails<T>.");
      static_assert(sizeof(h3svg::LossConditionDetails<T>) == sizeof(h3m::LossConditionDetails<T>),
                    "h3svg::LossConditionDetails<T> must have the same size as h3m::LossConditionDetails<T>.");
      // Reuse H3MJsonWriter.
      JsonObjectWriter<h3m::LossConditionDetails<T>>{}(out, details);
    }
  }

  template<>
  void JsonObjectWriter<h3svg::LossCondition>::operator()(FieldsWriter& out,
                                                          const h3svg::LossCondition& loss_condition) const
  {
    using Fields = h3json::FieldNames<h3svg::LossCondition>;
    out.writeField(Fields::kType, loss_condition.type());
    if (loss_condition.type() != h3svg::LossConditionType::Normal)
    {
      std::visit([&out] <h3svg::LossConditionType T> (const h3svg::LossConditionDetails<T>& details)
                 { out.writeField(Fields::kDetails, details); },
                 loss_condition.details);
    }
  }
}
