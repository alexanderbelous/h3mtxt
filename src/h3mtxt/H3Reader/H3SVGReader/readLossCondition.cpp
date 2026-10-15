#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>

#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/SavedGame/LossCondition.h>

#include <stdexcept>
#include <type_traits>

namespace h3svg
{
  template<LossConditionType T>
  LossConditionDetails<T> H3SVGReader::readLossConditionDetails() const
  {
    if constexpr (T == LossConditionType::LoseHero)
    {
      return LossConditionDetails<LossConditionType::LoseHero> {
        .hero = readEnum<HeroType16>()
      };
    }
    else
    {
      // Sanity checks.
      static_assert(std::is_base_of_v<h3m::LossConditionDetails<T>, LossConditionDetails<T>>,
                    "h3svg::LossConditionDetails<T> must be derived from h3m::LossConditionDetails<T>.");
      static_assert(sizeof(LossConditionDetails<T>) == sizeof(h3m::LossConditionDetails<T>),
                    "h3svg::LossConditionDetails<T> must have the same size as h3m::LossConditionDetails<T>.");
      // Reuse H3MReader.
      return { h3m::H3MReader{stream_}.readLossConditionDetails<T>() };
    }
  }

  LossCondition H3SVGReader::readLossCondition() const
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
      throw std::runtime_error("H3SVGReader::readLossCondition(): invalid LossConditionType.");
    }
  }
}
