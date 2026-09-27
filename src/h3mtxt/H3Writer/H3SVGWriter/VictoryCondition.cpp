#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/SavedGame/VictoryCondition.h>

#include <type_traits>

namespace h3svg
{
  void H3SVGWriter::writeData(const SpecialVictoryConditionBase& base) const
  {
    h3m::H3MWriter{ stream_, format() }.writeData(base);
  }

  void H3SVGWriter::writeData(const VictoryCondition& victory_condition) const
  {
    writeData(victory_condition.type());
    std::visit([this] <VictoryConditionType T> (const VictoryConditionDetails<T>& details)
               { writeData(details); },
               victory_condition.details);
  }

  template<VictoryConditionType T>
  void H3SVGWriter::writeData(const VictoryConditionDetails<T>& details) const
  {
    if constexpr (std::is_base_of_v<h3m::VictoryConditionDetails<T>, VictoryConditionDetails<T>> &&
                  sizeof(VictoryConditionDetails<T>) == sizeof(h3m::VictoryConditionDetails<T>))
    {
      // Reuse H3MWriter.
      h3m::H3MWriter{ stream_, format() }.writeData(static_cast<const h3m::VictoryConditionDetails<T>&>(details));
    }
    else
    {
      writeData(static_cast<const SpecialVictoryConditionBase&>(details));
      if constexpr (T == VictoryConditionType::AcquireArtifact)
      {
        writeData(details.artifact_type);
      }
      else if constexpr (T == VictoryConditionType::AccumulateCreatures)
      {
        writeData(details.creatures);
      }
      else if constexpr (T == VictoryConditionType::DefeatHero)
      {
        writeData(details.hero);
      }
      else
      {
        static_assert(false, "Invalid VictoryConditionType.");
      }
    }
  }
}
