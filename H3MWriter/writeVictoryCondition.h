#pragma once

#include <h3mtxt/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/VictoryCondition.h>

#include <type_traits>

namespace h3m
{
  // Writes common data of a special victory conditions into the given stream.
  // \param stream - output stream.
  // \param base - common data of a special victory condtion.
  inline void writeSpecialVictoryConditionBase(std::ostream& stream, const SpecialVictoryConditionBase& base)
  {
    writeData(stream, base.allow_normal_win);
    writeData(stream, base.applies_to_computer);
  }

  template<>
  struct H3MWriter<VictoryConditionDetails<VictoryConditionType::AcquireArtifact>>
  {
    void operator()(std::ostream& stream, const VictoryConditionDetails<VictoryConditionType::AcquireArtifact>& value) const
    {
      writeSpecialVictoryConditionBase(stream, value);
      writeData(stream, value.artifact_type);
    }
  };

  template<>
  struct H3MWriter<VictoryConditionDetails<VictoryConditionType::AccumulateCreatures>>
  {
    void operator()(std::ostream& stream, const VictoryConditionDetails<VictoryConditionType::AccumulateCreatures>& value) const
    {
      writeSpecialVictoryConditionBase(stream, value);
      writeData(stream, value.creature_type);
      writeData(stream, value.count);
    }
  };

  template<>
  struct H3MWriter<VictoryConditionDetails<VictoryConditionType::AccumulateResources>>
  {
    void operator()(std::ostream& stream, const VictoryConditionDetails<VictoryConditionType::AccumulateResources>& value) const
    {
      writeSpecialVictoryConditionBase(stream, value);
      writeData(stream, value.resource_type);
      writeData(stream, value.amount);
    }
  };

  template<>
  struct H3MWriter<VictoryConditionDetails<VictoryConditionType::UpgradeTown>>
  {
    void operator()(std::ostream& stream, const VictoryConditionDetails<VictoryConditionType::UpgradeTown>& value) const
    {
      writeSpecialVictoryConditionBase(stream, value);
      writeData(stream, value.x);
      writeData(stream, value.y);
      writeData(stream, value.z);
      writeData(stream, value.hall_level);
      writeData(stream, value.castle_level);
    }
  };

  template<class T>
  struct H3MWriter<T, std::enable_if_t<std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::BuildGrail>> ||
                                       std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::DefeatHero>> || 
                                       std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::CaptureTown>> ||
                                       std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::DefeatMonster>>>>
  {
    void operator()(std::ostream& stream, const T& value) const
    {
      writeSpecialVictoryConditionBase(stream, value);
      writeData(stream, value.x);
      writeData(stream, value.y);
      writeData(stream, value.z);
    }
  };

  template<class T>
  struct H3MWriter<T, std::enable_if_t<std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::FlagDwellings>> ||
                                       std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::FlagMines>>>>
  {
    void operator()(std::ostream& stream, const T& value) const
    {
      writeSpecialVictoryConditionBase(stream, value);
    }
  };

  template<>
  struct H3MWriter<VictoryConditionDetails<VictoryConditionType::TransportArtifact>>
  {
    void operator()(std::ostream& stream, const VictoryConditionDetails<VictoryConditionType::TransportArtifact>& value) const
    {
      writeSpecialVictoryConditionBase(stream, value);
      writeData(stream, value.artifact_type);
      writeData(stream, value.x);
      writeData(stream, value.y);
      writeData(stream, value.z);
    }
  };

  template<>
  struct H3MWriter<VictoryConditionDetails<VictoryConditionType::Normal>>
  {
    void operator()(std::ostream&, const VictoryConditionDetails<VictoryConditionType::Normal>&) const
    {
    }
  };

  template<>
  struct H3MWriter<VictoryCondition>
  {
    void operator()(std::ostream& stream, const VictoryCondition& victory_condition) const
    {
      writeData(stream, victory_condition.type());
      std::visit([&stream](auto&& value) { writeData(stream, std::forward<decltype(value)>(value)); },
                 victory_condition.details);
    }
  };
}
