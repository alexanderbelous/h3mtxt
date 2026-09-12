#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/VictoryCondition.h>

#include <type_traits>

namespace h3m
{
  namespace
  {
    template<VictoryConditionType T, class Enable = void>
    struct VictoryConditionDetailsWriter;

    template<>
    struct VictoryConditionDetailsWriter<VictoryConditionType::AcquireArtifact>
    {
      void operator()(const H3MWriter& writer,
                      const VictoryConditionDetails<VictoryConditionType::AcquireArtifact>& details) const
      {
        writer.writeData(static_cast<const SpecialVictoryConditionBase&>(details));
        writer.writeData(details.artifact_type);
      }
    };

    template<>
    struct VictoryConditionDetailsWriter<VictoryConditionType::AccumulateCreatures>
    {
      void operator()(const H3MWriter& writer,
                      const VictoryConditionDetails<VictoryConditionType::AccumulateCreatures>& details) const
      {
        writer.writeData(static_cast<const SpecialVictoryConditionBase&>(details));
        writer.writeData(details.creatures);
      }
    };

    template<>
    struct VictoryConditionDetailsWriter<VictoryConditionType::AccumulateResources>
    {
      void operator()(const H3MWriter& writer,
                      const VictoryConditionDetails<VictoryConditionType::AccumulateResources>& details) const
      {
        writer.writeData(static_cast<const SpecialVictoryConditionBase&>(details));
        writer.writeData(details.resources);
      }
    };

    template<>
    struct VictoryConditionDetailsWriter<VictoryConditionType::UpgradeTown>
    {
      void operator()(const H3MWriter& writer,
                      const VictoryConditionDetails<VictoryConditionType::UpgradeTown>& details) const
      {
        writer.writeData(static_cast<const SpecialVictoryConditionBase&>(details));
        writer.writeData(details.coordinates);
        writer.writeData(details.hall_level);
        writer.writeData(details.castle_level);
      }
    };

    template<VictoryConditionType T>
    struct VictoryConditionDetailsWriter<T, std::enable_if_t<T == VictoryConditionType::BuildGrail ||
                                                             T == VictoryConditionType::DefeatHero || 
                                                             T == VictoryConditionType::CaptureTown ||
                                                             T == VictoryConditionType::DefeatMonster>>
    {
      void operator()(const H3MWriter& writer, const VictoryConditionDetails<T>& details) const
      {
        writer.writeData(static_cast<const SpecialVictoryConditionBase&>(details));
        writer.writeData(details.coordinates);
      }
    };

    template<VictoryConditionType T>
    struct VictoryConditionDetailsWriter<T, std::enable_if_t<T == VictoryConditionType::FlagDwellings ||
                                                             T == VictoryConditionType::FlagMines ||
                                                             T == VictoryConditionType::DefeatAllMonsters>>
    {
      void operator()(const H3MWriter& writer, const VictoryConditionDetails<T>& details) const
      {
        writer.writeData(static_cast<const SpecialVictoryConditionBase&>(details));
      }
    };

    template<>
    struct VictoryConditionDetailsWriter<VictoryConditionType::TransportArtifact>
    {
      void operator()(const H3MWriter& writer,
                      const VictoryConditionDetails<VictoryConditionType::TransportArtifact>& details) const
      {
        writer.writeData(static_cast<const SpecialVictoryConditionBase&>(details));
        writer.writeData(details.artifact_type);
        writer.writeData(details.destination);
      }
    };

    template<>
    struct VictoryConditionDetailsWriter<VictoryConditionType::SurviveBeyondATimeLimit>
    {
      void operator()(const H3MWriter& writer,
                      const VictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit>& details) const
      {
        writer.writeData(static_cast<const SpecialVictoryConditionBase&>(details));
        writer.writeData(details.days);
      }
    };

    template<>
    struct VictoryConditionDetailsWriter<VictoryConditionType::Normal>
    {
      void operator()(const H3MWriter&, const VictoryConditionDetails<VictoryConditionType::Normal>&) const
      {
      }
    };
  }

  void H3MWriter::writeData(const SpecialVictoryConditionBase& base) const
  {
    writeData(base.allow_normal_win);
    writeData(base.applies_to_computer);
  }

  void H3MWriter::writeData(const VictoryCondition& victory_condition) const
  {
    writeData(victory_condition.type());
    std::visit([this] <VictoryConditionType T> (const VictoryConditionDetails<T>& details)
               { writeData(details); },
               victory_condition.details);
  }

  template<VictoryConditionType T>
  void H3MWriter::writeData(const VictoryConditionDetails<T>& details) const
  {
    VictoryConditionDetailsWriter<T>{}(*this, details);
  }

  // Explicit instantiations of H3MWriter::writeData(const VictoryConditionDetails<T>&)
  // for all valid VictoryConditionTypes.
  template void H3MWriter::writeData(const VictoryConditionDetails<VictoryConditionType::AcquireArtifact>&) const;
  template void H3MWriter::writeData(const VictoryConditionDetails<VictoryConditionType::AccumulateCreatures>&) const;
  template void H3MWriter::writeData(const VictoryConditionDetails<VictoryConditionType::AccumulateResources>&) const;
  template void H3MWriter::writeData(const VictoryConditionDetails<VictoryConditionType::UpgradeTown>&) const;
  template void H3MWriter::writeData(const VictoryConditionDetails<VictoryConditionType::BuildGrail>&) const;
  template void H3MWriter::writeData(const VictoryConditionDetails<VictoryConditionType::DefeatHero>&) const;
  template void H3MWriter::writeData(const VictoryConditionDetails<VictoryConditionType::CaptureTown>&) const;
  template void H3MWriter::writeData(const VictoryConditionDetails<VictoryConditionType::DefeatMonster>&) const;
  template void H3MWriter::writeData(const VictoryConditionDetails<VictoryConditionType::FlagDwellings>&) const;
  template void H3MWriter::writeData(const VictoryConditionDetails<VictoryConditionType::FlagMines>&) const;
  template void H3MWriter::writeData(const VictoryConditionDetails<VictoryConditionType::TransportArtifact>&) const;
  template void H3MWriter::writeData(const VictoryConditionDetails<VictoryConditionType::DefeatAllMonsters>&) const;
  template void H3MWriter::writeData(const VictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit>&) const;
  template void H3MWriter::writeData(const VictoryConditionDetails<VictoryConditionType::Normal>&) const;
}
