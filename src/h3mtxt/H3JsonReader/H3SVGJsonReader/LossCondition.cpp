#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/VariantJsonReader.h>
#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/LossCondition.h>

#include <stdexcept>

namespace h3json
{
  template<h3svg::LossConditionType T>
  h3svg::LossConditionDetails<T>
  JsonReader<h3svg::LossConditionDetails<T>>::operator()(const Json::Value& value) const
  {
    // Sanity checks
    static_assert(std::is_base_of_v<h3m::LossConditionDetails<T>, h3svg::LossConditionDetails<T>>,
                  "h3svg::LossConditionDetails<T> must be derived from h3m::LossConditionDetails<T>");
    static_assert(sizeof(h3m::LossConditionDetails<T>) == sizeof(h3svg::LossConditionDetails<T>),
                  "h3svg::LossConditionDetails<T> must have the same size as h3m::LossConditionDetails<T>");
    return h3svg::LossConditionDetails<T>{ fromJson<h3m::LossConditionDetails<T>>(value) };
  }

  // Explicit instantiations for LossConditionTypes that use the default implementation.
  template
  h3svg::LossConditionDetails<h3svg::LossConditionType::LoseTown>
  JsonReader<h3svg::LossConditionDetails<h3svg::LossConditionType::LoseTown>>::operator()(const Json::Value&) const;

  template
  h3svg::LossConditionDetails<h3svg::LossConditionType::TimeExpires>
  JsonReader<h3svg::LossConditionDetails<h3svg::LossConditionType::TimeExpires>>::operator()(const Json::Value&) const;

  template
  h3svg::LossConditionDetails<h3svg::LossConditionType::Normal>
  JsonReader<h3svg::LossConditionDetails<h3svg::LossConditionType::Normal>>::operator()(const Json::Value&) const;

  template<>
  h3svg::LossConditionDetails<h3svg::LossConditionType::LoseHero>
  JsonReader<h3svg::LossConditionDetails<h3svg::LossConditionType::LoseHero>>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::LossConditionDetails<h3svg::LossConditionType::LoseHero>>;
    h3svg::LossConditionDetails<h3svg::LossConditionType::LoseHero> details;
    readField(details.hero, value, Fields::kHero);
    return details;
  }

  template<>
  h3svg::LossCondition JsonReader<h3svg::LossCondition>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3svg::LossCondition>;
    const h3svg::LossConditionType loss_condition_type = readField<h3svg::LossConditionType>(value, Fields::kType);
    h3svg::LossCondition loss_condition;
    if (loss_condition_type != h3svg::LossConditionType::Normal)
    {
      const std::size_t variant_alternative_idx = h3svg::LossCondition::getAlternativeIdx(loss_condition_type);
      if (variant_alternative_idx == std::variant_npos)
      {
        throw std::runtime_error("JsonReader<h3svg::LossCondition>: invalid loss_condition_type");
      }
      loss_condition.details = VariantJsonReader<h3svg::LossCondition::Details>{}(getJsonField(value, Fields::kDetails),
                                                                                  variant_alternative_idx);
    }
    return loss_condition;
  }
}
