#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/LossCondition.h>
#include <h3mtxt/Medea/Medea.h>

namespace Medea_NS
{
  template<>
  void JsonObjectWriter<h3m::LossConditionDetails<h3m::LossConditionType::LoseTown>>::operator()(
    FieldsWriter& out, const h3m::LossConditionDetails<h3m::LossConditionType::LoseTown>& value) const
  {
    using Fields = h3json::FieldNames<h3m::LossConditionDetails<h3m::LossConditionType::LoseTown>>;
    out.writeField(Fields::kCoordinates, value.coordinates);
  }

  template<>
  void JsonObjectWriter<h3m::LossConditionDetails<h3m::LossConditionType::LoseHero>>::operator()(
    FieldsWriter& out, const h3m::LossConditionDetails<h3m::LossConditionType::LoseHero>& value) const
  {
    using Fields = h3json::FieldNames<h3m::LossConditionDetails<h3m::LossConditionType::LoseHero>>;
    out.writeField(Fields::kCoordinates, value.coordinates);
  }

  template<>
  void JsonObjectWriter<h3m::LossConditionDetails<h3m::LossConditionType::TimeExpires>>::operator()(
    FieldsWriter& out, const h3m::LossConditionDetails<h3m::LossConditionType::TimeExpires>& value) const
  {
    using Fields = h3json::FieldNames<h3m::LossConditionDetails<h3m::LossConditionType::TimeExpires>>;
    out.writeField(Fields::kDays, value.days);
  }

  template<>
  void JsonObjectWriter<h3m::LossConditionDetails<h3m::LossConditionType::Normal>>::operator()(
    FieldsWriter&, const h3m::LossConditionDetails<h3m::LossConditionType::Normal>&) const
  {
  }

  void JsonObjectWriter<h3m::LossCondition>::operator()(FieldsWriter& out,
                                                        const h3m::LossCondition& loss_condition) const
  {
    using Fields = h3json::FieldNames<h3m::LossCondition>;
    out.writeField(Fields::kType, loss_condition.type());
    out.writeComment(h3m::getEnumString(loss_condition.type()), false);
    if (loss_condition.type() != h3m::LossConditionType::Normal)
    {
      std::visit([&out] <h3m::LossConditionType T> (const h3m::LossConditionDetails<T>& details)
                 { out.writeField(Fields::kDetails, details); },
                 loss_condition.details);
    }
  }
}
