#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/getEnumString.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/LossCondition.h>
#include <h3mtxt/Medea/Medea.h>

namespace Medea_NS
{
  template<h3svg::LossConditionType T>
  void JsonObjectWriter<h3svg::LossConditionDetails<T>>::operator()(
    FieldsWriter& out, const h3svg::LossConditionDetails<T>& details) const
  {
    // Sanity checks.
    static_assert(std::is_base_of_v<h3m::LossConditionDetails<T>, h3svg::LossConditionDetails<T>>,
                  "h3svg::LossConditionDetails<T> must be derived from h3m::LossConditionDetails<T>.");
    static_assert(sizeof(h3svg::LossConditionDetails<T>) == sizeof(h3m::LossConditionDetails<T>),
                  "h3svg::LossConditionDetails<T> must have the same size as h3m::LossConditionDetails<T>.");
    // Reuse the code from H3MJsonWriter.
    JsonObjectWriter<h3m::LossConditionDetails<T>>{}(out, details);
  }

  // Explicit instantiations for LossConditionTypes that use the default template implementation.
  template
  void JsonObjectWriter<h3svg::LossConditionDetails<h3svg::LossConditionType::LoseTown>>::operator()(
    FieldsWriter& out, const h3svg::LossConditionDetails<h3svg::LossConditionType::LoseTown>& details) const;

  template
    void JsonObjectWriter<h3svg::LossConditionDetails<h3svg::LossConditionType::TimeExpires>>::operator()(
      FieldsWriter& out, const h3svg::LossConditionDetails<h3svg::LossConditionType::TimeExpires>& details) const;

  template
    void JsonObjectWriter<h3svg::LossConditionDetails<h3svg::LossConditionType::Normal>>::operator()(
      FieldsWriter& out, const h3svg::LossConditionDetails<h3svg::LossConditionType::Normal>& details) const;

  // Specialization for LossConditionType::LoseHero.
  template<>
  void JsonObjectWriter<h3svg::LossConditionDetails<h3svg::LossConditionType::LoseHero>>::operator()(
    FieldsWriter& out, const h3svg::LossConditionDetails<h3svg::LossConditionType::LoseHero>& details) const
  {
    using Fields = h3json::FieldNames<h3svg::LossConditionDetails<h3svg::LossConditionType::LoseHero>>;
    out.writeField(Fields::kHero, details.hero);
    if (const std::string_view enum_str = getEnumString(details.hero); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
  }

  void JsonObjectWriter<h3svg::LossCondition>::operator()(FieldsWriter& out,
                                                          const h3svg::LossCondition& loss_condition) const
  {
    using Fields = h3json::FieldNames<h3svg::LossCondition>;
    out.writeField(Fields::kType, loss_condition.type());
    out.writeComment(getEnumString(loss_condition.type()), false);
    if (loss_condition.type() != h3svg::LossConditionType::Normal)
    {
      std::visit([&out] <h3svg::LossConditionType T> (const h3svg::LossConditionDetails<T>& details)
                 { out.writeField(Fields::kDetails, details); },
                 loss_condition.details);
    }
  }
}
