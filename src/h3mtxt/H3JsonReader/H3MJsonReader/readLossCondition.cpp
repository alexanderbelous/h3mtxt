#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/VariantJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/LossCondition.h>

namespace h3json
{
  template<h3m::LossConditionType T>
  h3m::LossConditionDetails<T>
  JsonReader2<h3m::LossConditionDetails<T>>::operator()() const
  {
    using Fields = FieldNames<h3m::LossConditionDetails<T>>;
    h3m::LossConditionDetails<T> details;
    if constexpr (T == h3m::LossConditionType::LoseTown ||
                  T == h3m::LossConditionType::LoseHero)
    {
      readField(Fields::kCoordinates, details.coordinates);
    }
    else if constexpr (T == h3m::LossConditionType::TimeExpires)
    {
      readField(Fields::kDays, details.days);
    }
    else if constexpr (T == h3m::LossConditionType::Normal)
    {
    }
    else
    {
      static_assert(false, "Invalid LossConditionType.");
    }
    return details;
  }

  template<>
  h3m::LossCondition JsonReader2<h3m::LossCondition>::operator()() const
  {
    using Fields = FieldNames<h3m::LossCondition>;
    const h3m::LossConditionType loss_condition_type = readField<h3m::LossConditionType>(Fields::kType);
    if (loss_condition_type == h3m::LossConditionType::Normal)
    {
      return h3m::LossCondition{};
    }
    const std::size_t variant_alternative_idx = h3m::LossCondition::getAlternativeIdx(loss_condition_type);
    if (variant_alternative_idx == std::variant_npos)
    {
      throw std::runtime_error("JsonReader<LossCondition>: invalid loss_condition_type");
    }
    return h3m::LossCondition{
      .details = VariantJsonReader<h3m::LossCondition::Details>{}(getField(Fields::kDetails),
                                                                  variant_alternative_idx)
    };
  }
}
