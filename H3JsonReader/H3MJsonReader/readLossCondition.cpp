#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/LossCondition.h>

namespace h3json
{
  template<>
  struct JsonReader<h3m::LossConditionDetails<h3m::LossConditionType::LoseTown>>
  {
    h3m::LossConditionDetails<h3m::LossConditionType::LoseTown> operator()(const Json::Value& value) const
    {
      h3m::LossConditionDetails<h3m::LossConditionType::LoseTown> details;
      readField(details.coordinates, value, "coordinates");
      return details;
    }
  };

  template<>
  struct JsonReader<h3m::LossConditionDetails<h3m::LossConditionType::LoseHero>>
  {
    h3m::LossConditionDetails<h3m::LossConditionType::LoseHero> operator()(const Json::Value& value) const
    {
      h3m::LossConditionDetails<h3m::LossConditionType::LoseHero> details;
      readField(details.coordinates, value, "coordinates");
      return details;
    }
  };

  template<>
  struct JsonReader<h3m::LossConditionDetails<h3m::LossConditionType::TimeExpires>>
  {
    h3m::LossConditionDetails<h3m::LossConditionType::TimeExpires> operator()(const Json::Value& value) const
    {
      h3m::LossConditionDetails<h3m::LossConditionType::TimeExpires> details;
      readField(details.days, value, "days");
      return details;
    }
  };

  h3m::LossCondition JsonReader<h3m::LossCondition>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::LossCondition>;
    const h3m::LossConditionType loss_condition_type = readField<h3m::LossConditionType>(value, Fields::kType);
    if (loss_condition_type == h3m::LossConditionType::Normal)
    {
      return h3m::LossCondition{};
    }
    const Json::Value& details_json = getJsonField(value, Fields::kDetails);
    switch (loss_condition_type)
    {
    case h3m::LossConditionType::LoseTown:
      return { fromJson<h3m::LossConditionDetails<h3m::LossConditionType::LoseTown>>(details_json) };
    case h3m::LossConditionType::LoseHero:
      return { fromJson<h3m::LossConditionDetails<h3m::LossConditionType::LoseHero>>(details_json) };
    case h3m::LossConditionType::TimeExpires:
      return { fromJson<h3m::LossConditionDetails<h3m::LossConditionType::TimeExpires>>(details_json) };
    default:
      throw std::runtime_error("JsonReader<LossCondition>: invalid loss_condition_type");
    }
  }
}
