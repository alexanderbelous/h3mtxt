#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>

#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/SavedGame/VictoryCondition.h>

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
    // Sanity checks.
    static_assert(std::is_base_of_v<h3m::VictoryConditionDetails<T>, VictoryConditionDetails<T>>,
                  "h3svg::VictoryConditionDetails<T> must be derived from h3m::VictoryConditionDetails<T>.");
    static_assert(sizeof(VictoryConditionDetails<T>) == sizeof(h3m::VictoryConditionDetails<T>),
                  "h3svg::VictoryConditionDetails<T> must have the same size as h3m::VictoryConditionDetails<T>.");
    h3m::H3MWriter{ stream_, format() }.writeData(static_cast<const h3m::VictoryConditionDetails<T>&>(details));
  }

  // Explicit instantiations of H3SVGWriter::writeData(const VictoryConditionDetails<T>&)
  // for VictoryConditionTypes that use the default implementation.
  template void H3SVGWriter::writeData(const VictoryConditionDetails<VictoryConditionType::AccumulateResources>&) const;
  template void H3SVGWriter::writeData(const VictoryConditionDetails<VictoryConditionType::UpgradeTown>&) const;
  template void H3SVGWriter::writeData(const VictoryConditionDetails<VictoryConditionType::BuildGrail>&) const;
  template void H3SVGWriter::writeData(const VictoryConditionDetails<VictoryConditionType::CaptureTown>&) const;
  template void H3SVGWriter::writeData(const VictoryConditionDetails<VictoryConditionType::DefeatMonster>&) const;
  template void H3SVGWriter::writeData(const VictoryConditionDetails<VictoryConditionType::FlagDwellings>&) const;
  template void H3SVGWriter::writeData(const VictoryConditionDetails<VictoryConditionType::FlagMines>&) const;
  template void H3SVGWriter::writeData(const VictoryConditionDetails<VictoryConditionType::TransportArtifact>&) const;
  template void H3SVGWriter::writeData(const VictoryConditionDetails<VictoryConditionType::DefeatAllMonsters>&) const;
  template void H3SVGWriter::writeData(const VictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit>&) const;
  template void H3SVGWriter::writeData(const VictoryConditionDetails<VictoryConditionType::Normal>&) const;

  template<>
  void H3SVGWriter::writeData(const VictoryConditionDetails<VictoryConditionType::AcquireArtifact>& details) const
  {
    writeData(static_cast<const SpecialVictoryConditionBase&>(details));
    writeData(details.artifact_type);
  }

  template<>
  void H3SVGWriter::writeData(const VictoryConditionDetails<VictoryConditionType::AccumulateCreatures>& details) const
  {
    writeData(static_cast<const SpecialVictoryConditionBase&>(details));
    writeData(details.creatures);
  }

  template<>
  void H3SVGWriter::writeData(const VictoryConditionDetails<VictoryConditionType::DefeatHero>& details) const
  {
    writeData(static_cast<const SpecialVictoryConditionBase&>(details));
    writeData(details.hero);
  }
}
