#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/JsonWriter/JsonWriter.h>
#include <h3mtxt/Map/LossCondition.h>

#include <type_traits>

namespace Medea_NS
{
  template<class T>
  struct JsonObjectWriter<T, std::enable_if_t<std::is_same_v<T, h3m::LossConditionDetails<h3m::LossConditionType::LoseTown>> ||
                                              std::is_same_v<T, h3m::LossConditionDetails<h3m::LossConditionType::LoseHero>>>>
  {
    void operator()(FieldsWriter& out, const T& value) const
    {
      out.writeField("x", value.x);
      out.writeField("y", value.y);
      out.writeField("z", value.z);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::LossConditionDetails<h3m::LossConditionType::TimeExpires>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::LossConditionDetails<h3m::LossConditionType::TimeExpires>& value) const
    {
      out.writeField("days", value.days);
    }
  };

  template<>
  struct JsonObjectWriter<h3m::LossConditionDetails<h3m::LossConditionType::Normal>>
  {
    void operator()(FieldsWriter&,
                    const h3m::LossConditionDetails<h3m::LossConditionType::Normal>&) const
    {
    }
  };

  void JsonObjectWriter<h3m::LossCondition>::operator()(FieldsWriter& out,
                                                        const h3m::LossCondition& loss_condition) const
  {
    using Fields = h3m::FieldNames<h3m::LossCondition>;
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
