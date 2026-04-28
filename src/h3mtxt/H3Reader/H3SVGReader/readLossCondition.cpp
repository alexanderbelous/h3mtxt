#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>

#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/SavedGame/LossCondition.h>

#include <stdexcept>
#include <type_traits>

namespace h3svg
{
  // The default implementation reuses H3MReader.
  template<LossConditionType T>
  LossConditionDetails<T> H3SVGReader::readLossConditionDetails() const
  {
    // Sanity checks.
    static_assert(std::is_base_of_v<h3m::LossConditionDetails<T>, LossConditionDetails<T>>,
                  "h3svg::LossConditionDetails<T> must be derived from h3m::LossConditionDetails<T>.");
    static_assert(sizeof(LossConditionDetails<T>) == sizeof(h3m::LossConditionDetails<T>),
                  "h3svg::LossConditionDetails<T> must have the same size as h3m::LossConditionDetails<T>.");
    return { h3m::H3MReader{stream_}.readLossConditionDetails<T>() };
  }

  // Explicit instantiations of H3SVGReader::readLossConditionDetails()
  // for LossConditionType that use the default template implementation.
  //
  // This is only needed so that H3SVGReader::readLossConditionDetails() can be invoked outside of this file.
  template
  LossConditionDetails<LossConditionType::LoseTown> H3SVGReader::readLossConditionDetails() const;

  template
  LossConditionDetails<LossConditionType::TimeExpires> H3SVGReader::readLossConditionDetails() const;

  template
  LossConditionDetails<LossConditionType::Normal> H3SVGReader::readLossConditionDetails() const;

  // Specialization for LossConditionType::LoseHero, which uses a different format in H3SVG.
  template<>
  LossConditionDetails<LossConditionType::LoseHero> H3SVGReader::readLossConditionDetails() const
  {
    return LossConditionDetails<LossConditionType::LoseHero> {
      .hero = readEnum<HeroType16>()
    };
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
