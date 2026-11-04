#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/DateUtils.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/LossCondition.h>
#include <h3mtxt/Medea/Medea.h>

using ::h3m::LossConditionDetails;
using ::h3m::LossConditionType;

namespace Medea_NS
{
  namespace
  {
    std::string makeTimeExpiresComment(std::int16_t days)
    {
      if (days <= 0)
      {
        days = 1;
      }
      return "Fail to win before " + h3json::Detail_NS::makeDateComment(days);
    }
  }

  template<LossConditionType T>
  void JsonObjectWriter<LossConditionDetails<T>>::operator()(FieldsWriter& out,
                                                             const LossConditionDetails<T>& value) const
  {
    using Fields = h3json::FieldNames<LossConditionDetails<T>>;
    if constexpr (T == LossConditionType::LoseTown ||
                  T == LossConditionType::LoseHero)
    {
      out.writeField(Fields::kCoordinates, value.coordinates);
    }
    else if constexpr (T == LossConditionType::TimeExpires)
    {
      out.writeField(Fields::kDays, value.days);
      out.writeComment(makeTimeExpiresComment(value.days), false);
    }
    else if constexpr (T == LossConditionType::Normal)
    {
      // No fields.
    }
    else
    {
      static_assert(false, "Invalid LossConditionType.");
    }
  }

  template<>
  void JsonObjectWriter<h3m::LossCondition>::operator()(FieldsWriter& out,
                                                        const h3m::LossCondition& loss_condition) const
  {
    using Fields = h3json::FieldNames<h3m::LossCondition>;
    out.writeField(Fields::kType, loss_condition.type());
    if (loss_condition.type() != LossConditionType::Normal)
    {
      std::visit([&out] <LossConditionType T> (const LossConditionDetails<T>& details)
                 { out.writeField(Fields::kDetails, details); },
                 loss_condition.details);
    }
  }
}
