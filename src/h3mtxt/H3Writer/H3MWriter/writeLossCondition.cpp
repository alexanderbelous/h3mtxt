#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/LossCondition.h>

namespace h3m
{
  template<>
  void H3MWriter::writeData(const LossConditionDetails<LossConditionType::LoseTown>& details) const
  {
    writeData(details.coordinates);
  }

  template<>
  void H3MWriter::writeData(const LossConditionDetails<LossConditionType::LoseHero>& details) const
  {
    writeData(details.coordinates);
  }

  template<>
  void H3MWriter::writeData(const LossConditionDetails<LossConditionType::TimeExpires>& details) const
  {
    writeData(details.days);
  }

  template<>
  void H3MWriter::writeData(const LossConditionDetails<LossConditionType::Normal>&) const
  {
  }

  void H3MWriter::writeData(const LossCondition& loss_condition) const
  {
    writeData(loss_condition.type());
    std::visit([this] <LossConditionType T> (const LossConditionDetails<T>& details) { writeData(details); },
               loss_condition.details);
  }
}
