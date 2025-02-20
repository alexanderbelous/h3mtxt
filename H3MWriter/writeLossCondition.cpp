#include <h3mtxt/H3MWriter/H3Writer.h>
#include <h3mtxt/H3MWriter/Utils.h>
#include <h3mtxt/Map/LossCondition.h>

namespace h3m
{
  namespace
  {
    template<LossConditionType T>
    void writeLossConditionDetails(std::ostream& stream, const LossConditionDetails<T>& details);

    template<>
    void writeLossConditionDetails<LossConditionType::LoseTown>(
      std::ostream& stream, const LossConditionDetails<LossConditionType::LoseTown>& value)
    {
      writeData(stream, value.x);
      writeData(stream, value.y);
      writeData(stream, value.z);
    }

    template<>
    void writeLossConditionDetails< LossConditionType::LoseHero>(
      std::ostream& stream, const LossConditionDetails<LossConditionType::LoseHero>& value)
    {
      writeData(stream, value.x);
      writeData(stream, value.y);
      writeData(stream, value.z);
    }

    template<>
    void writeLossConditionDetails<LossConditionType::TimeExpires>(
      std::ostream& stream, const LossConditionDetails<LossConditionType::TimeExpires>& value)
    {
      writeData(stream, value.days);
    }

    template<>
    void writeLossConditionDetails<LossConditionType::Normal>(
      std::ostream&, const LossConditionDetails<LossConditionType::Normal>&)
    {
    }
  }

  void H3MWriter<LossCondition>::operator()(std::ostream& stream, const LossCondition& loss_condition) const
  {
    writeData(stream, loss_condition.type());
    std::visit([&stream] <LossConditionType T> (const LossConditionDetails<T>& details)
               { writeLossConditionDetails<T>(stream, details); },
               loss_condition.details);
  }
}
