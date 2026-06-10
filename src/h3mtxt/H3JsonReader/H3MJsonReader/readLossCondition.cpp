#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/VariantJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/LossCondition.h>

namespace h3json
{
  template<>
  h3m::LossConditionDetails<h3m::LossConditionType::LoseTown>
  JsonReader<h3m::LossConditionDetails<h3m::LossConditionType::LoseTown>>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::LossConditionDetails<h3m::LossConditionType::LoseTown>>;
    h3m::LossConditionDetails<h3m::LossConditionType::LoseTown> details;
    readField(details.coordinates, value, Fields::kCoordinates);
    return details;
  }

  template<>
  h3m::LossConditionDetails<h3m::LossConditionType::LoseHero>
  JsonReader<h3m::LossConditionDetails<h3m::LossConditionType::LoseHero>>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::LossConditionDetails<h3m::LossConditionType::LoseHero>>;
    h3m::LossConditionDetails<h3m::LossConditionType::LoseHero> details;
    readField(details.coordinates, value, Fields::kCoordinates);
    return details;
  }

  template<>
  h3m::LossConditionDetails<h3m::LossConditionType::TimeExpires>
  JsonReader<h3m::LossConditionDetails<h3m::LossConditionType::TimeExpires>>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::LossConditionDetails<h3m::LossConditionType::TimeExpires>>;
    h3m::LossConditionDetails<h3m::LossConditionType::TimeExpires> details;
    readField(details.days, value, Fields::kDays);
    return details;
  }

  template<>
  h3m::LossConditionDetails<h3m::LossConditionType::Normal>
  JsonReader<h3m::LossConditionDetails<h3m::LossConditionType::Normal>>::operator()(const Json::Value&) const
  {
    return h3m::LossConditionDetails<h3m::LossConditionType::Normal>{};
  }

  template<>
  h3m::LossCondition JsonReader<h3m::LossCondition>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::LossCondition>;
    const h3m::LossConditionType loss_condition_type = readField<h3m::LossConditionType>(value, Fields::kType);
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
      .details = VariantJsonReader<h3m::LossCondition::Details>{}(getJsonField(value, Fields::kDetails),
                                                                  variant_alternative_idx)
    };
  }
}
