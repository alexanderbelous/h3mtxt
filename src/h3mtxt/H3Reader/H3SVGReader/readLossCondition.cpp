#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>
#include <h3mtxt/SavedGame/LossCondition.h>

#include <stdexcept>

namespace h3svg
{
  namespace
  {
    LossCondition::Details readLossConditionDetailsVariant(const H3SVGReader& reader, LossConditionType loss_condition_type)
    {
      switch (loss_condition_type)
      {
      case LossConditionType::LoseTown:
        return reader.readLossConditionDetails<LossConditionType::LoseTown>();
      case LossConditionType::LoseHero:
        return reader.readLossConditionDetails<LossConditionType::LoseHero>();
      case LossConditionType::TimeExpires:
        return reader.readLossConditionDetails<LossConditionType::TimeExpires>();
      case LossConditionType::Normal:
        return reader.readLossConditionDetails<LossConditionType::Normal>();
      default:
        throw std::runtime_error("H3SVGReader::readLossCondition(): invalid LossConditionType.");
      }
    }
  }

  // TODO: reuse H3MReader where applicable.

  template<>
  LossConditionDetails<LossConditionType::LoseTown> H3SVGReader::readLossConditionDetails() const
  {
    return LossConditionDetails<LossConditionType::LoseTown> {
      h3m::LossConditionDetails<LossConditionType::LoseTown> {
        .coordinates = readCoordinates()
      }
    };
  }

  template<>
  LossConditionDetails<LossConditionType::LoseHero> H3SVGReader::readLossConditionDetails() const
  {
    return LossConditionDetails<LossConditionType::LoseHero> {
      .hero = readEnum<HeroType16>()
    };
  }

  template<>
  LossConditionDetails<LossConditionType::TimeExpires> H3SVGReader::readLossConditionDetails() const
  {
    return LossConditionDetails<LossConditionType::TimeExpires> {
      h3m::LossConditionDetails<LossConditionType::TimeExpires> {
        .days = readInt<std::int16_t>()
      }
    };
  }

  template<>
  LossConditionDetails<LossConditionType::Normal> H3SVGReader::readLossConditionDetails() const
  {
    return LossConditionDetails<LossConditionType::Normal>{};
  }

  LossCondition H3SVGReader::readLossCondition() const
  {
    const LossConditionType loss_condition_type = readEnum<LossConditionType>();
    return LossCondition{ .details = readLossConditionDetailsVariant(*this, loss_condition_type) };
  }
}
