#pragma once

#include <h3mtxt/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/LossCondition.h>

namespace h3m
{
  template<>
  struct H3MWriter<LossConditionDetails<LossConditionType::LoseTown>>
  {
    void operator()(std::ostream& stream, const LossConditionDetails<LossConditionType::LoseTown>& value) const
    {
      writeData(stream, value.x);
      writeData(stream, value.y);
      writeData(stream, value.z);
    }
  };

  template<>
  struct H3MWriter<LossConditionDetails<LossConditionType::LoseHero>>
  {
    void operator()(std::ostream& stream, const LossConditionDetails<LossConditionType::LoseHero>& value) const
    {
      writeData(stream, value.x);
      writeData(stream, value.y);
      writeData(stream, value.z);
    }
  };

  template<>
  struct H3MWriter<LossConditionDetails<LossConditionType::TimeExpires>>
  {
    void operator()(std::ostream& stream, const LossConditionDetails<LossConditionType::TimeExpires>& value) const
    {
      writeData(stream, value.days);
    }
  };

  template<>
  struct H3MWriter<LossConditionDetails<LossConditionType::Normal>>
  {
    void operator()(std::ostream&, const LossConditionDetails<LossConditionType::Normal>&) const
    {
    }
  };

  template<>
  struct H3MWriter<LossCondition>
  {
    void operator()(std::ostream& stream, const LossCondition& loss_condition) const
    {
      writeData(stream, loss_condition.type());
      std::visit([&stream](auto&& value) { writeData(stream, std::forward<decltype(value)>(value)); },
                 loss_condition.details);
    }
  };
}
