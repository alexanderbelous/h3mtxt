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
  h3svg::LossConditionDetails<T> JsonReader2<h3svg::LossConditionDetails<T>>::operator()() const
  {
    if constexpr (T == h3svg::LossConditionType::LoseHero)
    {
      using Fields = h3json::FieldNames<h3svg::LossConditionDetails<h3svg::LossConditionType::LoseHero>>;
      h3svg::LossConditionDetails<h3svg::LossConditionType::LoseHero> details;
      readField(Fields::kHero, details.hero);
      return details;
    }
    else
    {
      // Sanity checks
      static_assert(std::is_base_of_v<h3m::LossConditionDetails<T>, h3svg::LossConditionDetails<T>>,
                    "h3svg::LossConditionDetails<T> must be derived from h3m::LossConditionDetails<T>");
      static_assert(sizeof(h3m::LossConditionDetails<T>) == sizeof(h3svg::LossConditionDetails<T>),
                    "h3svg::LossConditionDetails<T> must have the same size as h3m::LossConditionDetails<T>");
      return h3svg::LossConditionDetails<T>{ fromJson<h3m::LossConditionDetails<T>>(value()) };
    }
  }

  template<>
  h3svg::LossCondition JsonReader2<h3svg::LossCondition>::operator()() const
  {
    using Fields = FieldNames<h3svg::LossCondition>;
    const h3svg::LossConditionType loss_condition_type = readField<h3svg::LossConditionType>(Fields::kType);
    h3svg::LossCondition loss_condition;
    if (loss_condition_type != h3svg::LossConditionType::Normal)
    {
      const std::size_t variant_alternative_idx = h3svg::LossCondition::getAlternativeIdx(loss_condition_type);
      if (variant_alternative_idx == std::variant_npos)
      {
        throw std::runtime_error("JsonReader<h3svg::LossCondition>: invalid loss_condition_type");
      }
      loss_condition.details = VariantJsonReader<h3svg::LossCondition::Details>{}(getField(Fields::kDetails),
                                                                                  variant_alternative_idx);
    }
    return loss_condition;
  }
}
