#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/LossCondition.h>

namespace h3m
{
  namespace
  {
    template<LossConditionType T>
    void writeLossConditionDetails(const H3MWriter& writer, const LossConditionDetails<T>& details);

    template<>
    void writeLossConditionDetails<LossConditionType::LoseTown>(
      const H3MWriter& writer, const LossConditionDetails<LossConditionType::LoseTown>& value)
    {
      writer.writeData(value.coordinates);
    }

    template<>
    void writeLossConditionDetails<LossConditionType::LoseHero>(
      const H3MWriter& writer, const LossConditionDetails<LossConditionType::LoseHero>& value)
    {
      writer.writeData(value.coordinates);
    }

    template<>
    void writeLossConditionDetails<LossConditionType::TimeExpires>(
      const H3MWriter& writer, const LossConditionDetails<LossConditionType::TimeExpires>& value)
    {
      writer.writeData(value.days);
    }

    template<>
    void writeLossConditionDetails<LossConditionType::Normal>(
      const H3MWriter&, const LossConditionDetails<LossConditionType::Normal>&)
    {
    }
  }

  void H3MWriter::writeData(const LossCondition& loss_condition) const
  {
    writeData(loss_condition.type());
    std::visit([this] <LossConditionType T> (const LossConditionDetails<T>& details)
               { writeLossConditionDetails<T>(*this, details); },
               loss_condition.details);
  }
}
