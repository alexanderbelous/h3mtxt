#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/SavedGame/VictoryCondition.h>

namespace h3svg
{
  namespace
  {
    void writeSpecialVictoryConditionBase(const H3SVGWriter& writer, const SpecialVictoryConditionBase& base)
    {
      writer.writeData(base.allow_normal_win);
      writer.writeData(base.applies_to_computer);
    }
  }

  void H3SVGWriter::writeData(const VictoryCondition& victory_condition) const
  {
    // writeData(victory_condition.type());
    std::visit([this] <VictoryConditionType T> (const VictoryConditionDetails<T>& details)
               {
                 // Ugly hack for now, because H3MWriter doesn't have a public API for writing
                 // h3m::VictoryConditionDetails.
                 if constexpr (T == VictoryConditionType::AcquireArtifact)
                 {
                   writeData(T);
                   writeSpecialVictoryConditionBase(*this, details);
                   writeData(details.artifact_type);
                 }
                 else if constexpr (T == VictoryConditionType::AccumulateCreatures)
                 {
                   writeData(T);
                   writeSpecialVictoryConditionBase(*this, details);
                   writeData(details.creatures);
                 }
                 else if constexpr (T == VictoryConditionType::DefeatHero)
                 {
                   writeData(T);
                   writeSpecialVictoryConditionBase(*this, details);
                   writeData(details.hero);
                 }
                 else
                 {
                   // Sanity checks.
                   static_assert(std::is_base_of_v<h3m::VictoryConditionDetails<T>, VictoryConditionDetails<T>>,
                                 "h3svg::VictoryConditionDetails<T> must be derived from h3m::VictoryConditionDetails<T>.");
                   static_assert(sizeof(VictoryConditionDetails<T>) == sizeof(h3m::VictoryConditionDetails<T>),
                                 "h3svg::VictoryConditionDetails<T> must have the same size as h3m::VictoryConditionDetails<T>.");
                   const h3m::VictoryConditionDetails<T>& details_base = details;
                   // TODO: eliminate copy construction.
                   h3m::H3MWriter{ stream_, format() }.writeData(h3m::VictoryCondition{ .details = details_base });
                 }
               },
               victory_condition.details);
  }
}
