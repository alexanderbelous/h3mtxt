#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/LossCondition.h>

namespace h3m::H3JsonReader_NS
{
  template<>
  struct JsonReader<LossConditionDetails<LossConditionType::LoseTown>>
  {
    LossConditionDetails<LossConditionType::LoseTown> operator()(const Json::Value& value) const
    {
      LossConditionDetails<LossConditionType::LoseTown> details;
      readField(details.coordinates, value, "coordinates");
      return details;
    }
  };

  template<>
  struct JsonReader<LossConditionDetails<LossConditionType::LoseHero>>
  {
    LossConditionDetails<LossConditionType::LoseHero> operator()(const Json::Value& value) const
    {
      LossConditionDetails<LossConditionType::LoseHero> details;
      readField(details.coordinates, value, "coordinates");
      return details;
    }
  };

  template<>
  struct JsonReader<LossConditionDetails<LossConditionType::TimeExpires>>
  {
    LossConditionDetails<LossConditionType::TimeExpires> operator()(const Json::Value& value) const
    {
      LossConditionDetails<LossConditionType::TimeExpires> details;
      readField(details.days, value, "days");
      return details;
    }
  };

  LossCondition JsonReader<LossCondition>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<LossCondition>;
    const LossConditionType loss_condition_type = readField<LossConditionType>(value, Fields::kType);
    switch (loss_condition_type)
    {
    case LossConditionType::LoseTown:
      return LossCondition{readField<LossConditionDetails<LossConditionType::LoseTown>>(value, Fields::kDetails)};
    case LossConditionType::LoseHero:
      return LossCondition{readField<LossConditionDetails<LossConditionType::LoseHero>>(value, Fields::kDetails)};
    case LossConditionType::TimeExpires:
      return LossCondition{readField<LossConditionDetails<LossConditionType::TimeExpires>>(value, Fields::kDetails)};
    case LossConditionType::Normal:
      return LossCondition{};
    default:
      throw std::runtime_error("JsonReader<LossCondition>: invalid loss_condition_type");
    }
  }
}
