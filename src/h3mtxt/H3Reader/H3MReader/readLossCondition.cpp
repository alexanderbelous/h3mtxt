#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/LossCondition.h>

namespace h3m
{
  template<>
  LossConditionDetails<LossConditionType::LoseTown> H3MReader::readLossConditionDetails() const
  {
    return LossConditionDetails<LossConditionType::LoseTown>{
      .coordinates = readCoordinates()
    };
  }

  template<>
  LossConditionDetails<LossConditionType::LoseHero> H3MReader::readLossConditionDetails() const
  {
    return LossConditionDetails<LossConditionType::LoseHero>{
      .coordinates = readCoordinates()
    };
  }

  template<>
  LossConditionDetails<LossConditionType::TimeExpires> H3MReader::readLossConditionDetails() const
  {
    return LossConditionDetails<LossConditionType::TimeExpires>{
      .days = readInt<std::int16_t>()
    };
  }

  template<>
  LossConditionDetails<LossConditionType::Normal> H3MReader::readLossConditionDetails() const
  {
    return LossConditionDetails<LossConditionType::Normal>{};
  }

  LossCondition H3MReader::readLossCondition() const
  {
    const LossConditionType loss_condition_type = readEnum<LossConditionType>();
    switch (loss_condition_type)
    {
    case LossConditionType::LoseTown:
      return LossCondition{ .details = readLossConditionDetails<LossConditionType::LoseTown>() };
    case LossConditionType::LoseHero:
      return LossCondition{ .details = readLossConditionDetails<LossConditionType::LoseHero>() };
    case LossConditionType::TimeExpires:
      return LossCondition{ .details = readLossConditionDetails<LossConditionType::TimeExpires>() };
    case LossConditionType::Normal:
      return LossCondition{ .details = readLossConditionDetails<LossConditionType::Normal>() };
    default:
      throw std::runtime_error("Invalid loss condition type.");
    }
  }
}
