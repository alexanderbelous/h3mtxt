#pragma once

#include <h3mtxt/Map/LossCondition.h>
#include <h3mtxt/H3MTxtWriter/H3MTxtWriter.h>

namespace Util_NS
{
  template<class T>
  struct StructWriter<T, std::enable_if_t<std::is_same_v<T, h3m::LossConditionDetails<h3m::LossConditionType::LoseTown>> ||
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
  struct StructWriter<h3m::LossConditionDetails<h3m::LossConditionType::TimeExpires>>
  {
    void operator()(FieldsWriter& out,
                    const h3m::LossConditionDetails<h3m::LossConditionType::TimeExpires>& value) const
    {
      out.writeField("days", value.days);
    }
  };

  template<>
  struct StructWriter<h3m::LossConditionDetails<h3m::LossConditionType::Normal>>
  {
    void operator()(FieldsWriter&,
                    const h3m::LossConditionDetails<h3m::LossConditionType::Normal>&) const
    {
    }
  };

  template<>
  struct StructWriter<h3m::LossCondition>
  {
    void operator()(FieldsWriter& out, const h3m::LossCondition& loss_condition) const
    {
      const bool has_details = loss_condition.type() != h3m::LossConditionType::Normal;
      out.writeField("type", loss_condition.type());
      if (has_details)
      {
        std::visit([&out](auto&& details) { out.writeField("details", std::forward<decltype(details)>(details)); },
                   loss_condition.details);
      }
    }
  };
}