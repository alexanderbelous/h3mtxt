#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/SavedGame/LossCondition.h>

namespace h3svg
{
  template<LossConditionType T>
  void H3SVGWriter::writeData(const LossConditionDetails<T>& details) const
  {
    if constexpr (T == LossConditionType::LoseHero)
    {
      writeData(details.hero);
    }
    else
    {
      // Sanity checks.
      static_assert(std::is_base_of_v<h3m::LossConditionDetails<T>, LossConditionDetails<T>>,
                    "h3svg::LossConditionDetails<T> must be derived from h3m::LossConditionDetails<T>.");
      static_assert(sizeof(LossConditionDetails<T>) == sizeof(h3m::LossConditionDetails<T>),
                    "h3svg::LossConditionDetails<T> must have the same size as h3m::LossConditionDetails<T>.");
      h3m::H3MWriter{ stream_, format() }.writeData(details);
    }
  }

  void H3SVGWriter::writeData(const LossCondition& loss_condition) const
  {
    writeData(loss_condition.type());
    std::visit([this] <LossConditionType T> (const LossConditionDetails<T>& details)
               { writeData(details); },
               loss_condition.details);
  }
}
