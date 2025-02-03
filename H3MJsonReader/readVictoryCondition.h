#pragma once

#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/Map/VictoryCondition.h>

#include <stdexcept>

namespace h3m
{
  inline void readSpecialVictoryConditionBaseFromJson(const Json::Value& value, SpecialVictoryConditionBase& base)
  {
    base.allow_normal_win = readField<Bool>(value, "allow_normal_win");
    base.applies_to_computer = readField<Bool>(value, "applies_to_computer");
  }

  template<>
  struct JsonReader<VictoryConditionDetails<VictoryConditionType::AcquireArtifact>>
  {
    VictoryConditionDetails<VictoryConditionType::AcquireArtifact> operator()(const Json::Value& value) const
    {
      VictoryConditionDetails<VictoryConditionType::AcquireArtifact> details;
      readSpecialVictoryConditionBaseFromJson(value, details);
      details.artifact_type = readField<ArtifactType>(value, "artifact_type");
      return details;
    }
  };

  template<>
  struct JsonReader<VictoryConditionDetails<VictoryConditionType::AccumulateCreatures>>
  {
    VictoryConditionDetails<VictoryConditionType::AccumulateCreatures> operator()(const Json::Value& value) const
    {
      VictoryConditionDetails<VictoryConditionType::AccumulateCreatures> details;
      readSpecialVictoryConditionBaseFromJson(value, details);
      details.creature_type = readField<CreatureType>(value, "creature_type");
      details.count = readField<std::uint32_t>(value, "count");
      return details;
    }
  };

  template<>
  struct JsonReader<VictoryConditionDetails<VictoryConditionType::AccumulateResources>>
  {
    VictoryConditionDetails<VictoryConditionType::AccumulateResources> operator()(const Json::Value& value) const
    {
      VictoryConditionDetails<VictoryConditionType::AccumulateResources> details;
      readSpecialVictoryConditionBaseFromJson(value, details);
      details.resource_type = readField<ResourceType>(value, "resource_type");
      details.amount = readField<std::uint32_t>(value, "amount");
      return details;
    }
  };

  template<>
  struct JsonReader<VictoryConditionDetails<VictoryConditionType::UpgradeTown>>
  {
    VictoryConditionDetails<VictoryConditionType::UpgradeTown> operator()(const Json::Value& value) const
    {
      VictoryConditionDetails<VictoryConditionType::UpgradeTown> details;
      readSpecialVictoryConditionBaseFromJson(value, details);
      details.x = readField<std::uint8_t>(value, "x");
      details.y = readField<std::uint8_t>(value, "y");
      details.z = readField<std::uint8_t>(value, "z");
      details.hall_level = readField<std::uint8_t>(value, "hall_level");
      details.castle_level = readField<std::uint8_t>(value, "castle_level");
      return details;
    }
  };

  template<class T>
  struct JsonReader<T, std::enable_if_t<std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::BuildGrail>> ||
                                        std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::DefeatHero>> ||
                                        std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::CaptureTown>> ||
                                        std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::DefeatMonster>>
                                       >>
  {
    T operator()(const Json::Value& value) const
    {
      T details {};
      readSpecialVictoryConditionBaseFromJson(value, details);
      details.x = readField<std::uint8_t>(value, "x");
      details.y = readField<std::uint8_t>(value, "y");
      details.z = readField<std::uint8_t>(value, "z");
      return details;
    }
  };

  template<class T>
  struct JsonReader<T, std::enable_if_t<std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::FlagDwellings>> ||
                                        std::is_same_v<T, VictoryConditionDetails<VictoryConditionType::FlagMines>>
                                       >>
  {
    T operator()(const Json::Value& value) const
    {
      T details {};
      readSpecialVictoryConditionBaseFromJson(value, details);
      return details;
    }
  };

  template<>
  struct JsonReader<VictoryConditionDetails<VictoryConditionType::TransportArtifact>>
  {
    VictoryConditionDetails<VictoryConditionType::TransportArtifact> operator()(const Json::Value& value) const
    {
      VictoryConditionDetails<VictoryConditionType::TransportArtifact> details;
      readSpecialVictoryConditionBaseFromJson(value, details);
      details.artifact_type = readField<std::uint8_t>(value, "artifact_type");
      details.x = readField<std::uint8_t>(value, "x");
      details.y = readField<std::uint8_t>(value, "y");
      details.z = readField<std::uint8_t>(value, "z");
      return details;
    }
  };

  template<>
  struct JsonReader<VictoryCondition>
  {
    VictoryCondition operator()(const Json::Value& value) const
    {
      const VictoryConditionType victory_condition_type = readField<VictoryConditionType>(value, "type");
      switch (victory_condition_type)
      {
      case VictoryConditionType::AcquireArtifact:
        return readField<VictoryConditionDetails<VictoryConditionType::AcquireArtifact>>(value, "details");
      case VictoryConditionType::AccumulateCreatures:
        return readField<VictoryConditionDetails<VictoryConditionType::AccumulateCreatures>>(value, "details");
      case VictoryConditionType::AccumulateResources:
        return readField<VictoryConditionDetails<VictoryConditionType::AccumulateResources>>(value, "details");
      case VictoryConditionType::UpgradeTown:
        return readField<VictoryConditionDetails<VictoryConditionType::UpgradeTown>>(value, "details");
      case VictoryConditionType::BuildGrail:
        return readField<VictoryConditionDetails<VictoryConditionType::BuildGrail>>(value, "details");
      case VictoryConditionType::DefeatHero:
        return readField<VictoryConditionDetails<VictoryConditionType::DefeatHero>>(value, "details");
      case VictoryConditionType::CaptureTown:
        return readField<VictoryConditionDetails<VictoryConditionType::CaptureTown>>(value, "details");
      case VictoryConditionType::DefeatMonster:
        return readField<VictoryConditionDetails<VictoryConditionType::DefeatMonster>>(value, "details");
      case VictoryConditionType::FlagDwellings:
        return readField<VictoryConditionDetails<VictoryConditionType::FlagDwellings>>(value, "details");
      case VictoryConditionType::FlagMines:
        return readField<VictoryConditionDetails<VictoryConditionType::FlagMines>>(value, "details");
      case VictoryConditionType::TransportArtifact:
        return readField<VictoryConditionDetails<VictoryConditionType::TransportArtifact>>(value, "details");
      case VictoryConditionType::Normal:
        return VictoryCondition();
      default:
        throw std::runtime_error("JsonReader<VictoryCondition>: invalid victory_condition_type");
      }
    }
  };
}
