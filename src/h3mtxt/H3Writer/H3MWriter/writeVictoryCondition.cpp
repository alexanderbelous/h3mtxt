#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/VictoryCondition.h>

#include <type_traits>

namespace h3m
{
  namespace
  {
    // Writes common data of a special victory conditions into the given stream.
    // \param stream - output stream.
    // \param base - common data of a special victory condtion.
    void writeSpecialVictoryConditionBase(const H3MWriter& writer, const SpecialVictoryConditionBase& base)
    {
      writer.writeData(base.allow_normal_win);
      writer.writeData(base.applies_to_computer);
    }

    template<VictoryConditionType T, class Enable = void>
    struct VictoryConditionDetailsWriter;

    template<>
    struct VictoryConditionDetailsWriter<VictoryConditionType::AcquireArtifact>
    {
      void operator()(const H3MWriter& writer, const VictoryConditionDetails<VictoryConditionType::AcquireArtifact>& value) const
      {
        writeSpecialVictoryConditionBase(writer, value);
        writer.writeData(value.artifact_type);
      }
    };

    template<>
    struct VictoryConditionDetailsWriter<VictoryConditionType::AccumulateCreatures>
    {
      void operator()(const H3MWriter& writer, const VictoryConditionDetails<VictoryConditionType::AccumulateCreatures>& value) const
      {
        writeSpecialVictoryConditionBase(writer, value);
        writer.writeData(value.creature_type);
        writer.writeData(value.count);
      }
    };

    template<>
    struct VictoryConditionDetailsWriter<VictoryConditionType::AccumulateResources>
    {
      void operator()(const H3MWriter& writer, const VictoryConditionDetails<VictoryConditionType::AccumulateResources>& value) const
      {
        writeSpecialVictoryConditionBase(writer, value);
        writer.writeData(value.resource_type);
        writer.writeData(value.amount);
      }
    };

    template<>
    struct VictoryConditionDetailsWriter<VictoryConditionType::UpgradeTown>
    {
      void operator()(const H3MWriter& writer, const VictoryConditionDetails<VictoryConditionType::UpgradeTown>& value) const
      {
        writeSpecialVictoryConditionBase(writer, value);
        writer.writeData(value.coordinates);
        writer.writeData(value.hall_level);
        writer.writeData(value.castle_level);
      }
    };

    template<VictoryConditionType T>
    struct VictoryConditionDetailsWriter<T, std::enable_if_t<T == VictoryConditionType::BuildGrail ||
                                                             T == VictoryConditionType::DefeatHero || 
                                                             T == VictoryConditionType::CaptureTown ||
                                                             T == VictoryConditionType::DefeatMonster>>
    {
      void operator()(const H3MWriter& writer, const VictoryConditionDetails<T>& value) const
      {
        writeSpecialVictoryConditionBase(writer, value);
        writer.writeData(value.coordinates);
      }
    };

    template<VictoryConditionType T>
    struct VictoryConditionDetailsWriter<T, std::enable_if_t<T == VictoryConditionType::FlagDwellings ||
                                                             T == VictoryConditionType::FlagMines ||
                                                             T == VictoryConditionType::DefeatAllMonsters>>
    {
      void operator()(const H3MWriter& writer, const VictoryConditionDetails<T>& value) const
      {
        writeSpecialVictoryConditionBase(writer, value);
      }
    };

    template<>
    struct VictoryConditionDetailsWriter<VictoryConditionType::TransportArtifact>
    {
      void operator()(const H3MWriter& writer, const VictoryConditionDetails<VictoryConditionType::TransportArtifact>& value) const
      {
        writeSpecialVictoryConditionBase(writer, value);
        writer.writeData(value.artifact_type);
        writer.writeData(value.destination);
      }
    };

    template<>
    struct VictoryConditionDetailsWriter<VictoryConditionType::SurviveBeyondATimeLimit>
    {
      void operator()(const H3MWriter& writer, const VictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit>& value) const
      {
        writeSpecialVictoryConditionBase(writer, value);
        writer.writeData(value.days);
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

  void H3MWriter::writeData(const VictoryCondition& victory_condition) const
  {
    writeData(victory_condition.type());
    std::visit([this] <VictoryConditionType T> (const VictoryConditionDetails<T>& value)
               { VictoryConditionDetailsWriter<T>{}(*this, value); },
               victory_condition.details);
  }
}
