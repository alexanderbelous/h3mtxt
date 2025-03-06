#include <h3mtxt/H3JsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/VictoryCondition.h>

#include <stdexcept>

namespace h3m::H3JsonReader_NS
{
  namespace
  {
    void readSpecialVictoryConditionBaseFromJson(const Json::Value& value, SpecialVictoryConditionBase& base)
    {
      base.allow_normal_win = readField<Bool>(value, "allow_normal_win");
      base.applies_to_computer = readField<Bool>(value, "applies_to_computer");
    }
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
      details.count = readField<std::int32_t>(value, "count");
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

  namespace
  {
    VictoryCondition::Details readVictoryConditionDetailsVariant(const Json::Value& value,
                                                                 VictoryConditionType victory_condition_type)
    {
      switch (victory_condition_type)
      {
      case VictoryConditionType::AcquireArtifact:
        return fromJson<VictoryConditionDetails<VictoryConditionType::AcquireArtifact>>(value);
      case VictoryConditionType::AccumulateCreatures:
        return fromJson<VictoryConditionDetails<VictoryConditionType::AccumulateCreatures>>(value);
      case VictoryConditionType::AccumulateResources:
        return fromJson<VictoryConditionDetails<VictoryConditionType::AccumulateResources>>(value);
      case VictoryConditionType::UpgradeTown:
        return fromJson<VictoryConditionDetails<VictoryConditionType::UpgradeTown>>(value);
      case VictoryConditionType::BuildGrail:
        return fromJson<VictoryConditionDetails<VictoryConditionType::BuildGrail>>(value);
      case VictoryConditionType::DefeatHero:
        return fromJson<VictoryConditionDetails<VictoryConditionType::DefeatHero>>(value);
      case VictoryConditionType::CaptureTown:
        return fromJson<VictoryConditionDetails<VictoryConditionType::CaptureTown>>(value);
      case VictoryConditionType::DefeatMonster:
        return fromJson<VictoryConditionDetails<VictoryConditionType::DefeatMonster>>(value);
      case VictoryConditionType::FlagDwellings:
        return fromJson<VictoryConditionDetails<VictoryConditionType::FlagDwellings>>(value);
      case VictoryConditionType::FlagMines:
        return fromJson<VictoryConditionDetails<VictoryConditionType::FlagMines>>(value);
      case VictoryConditionType::TransportArtifact:
        return fromJson<VictoryConditionDetails<VictoryConditionType::TransportArtifact>>(value);
      case VictoryConditionType::Normal:
        return VictoryCondition::Details{};
      default:
        throw std::runtime_error("JsonReader<VictoryCondition>: invalid victory_condition_type");
      }
    }
  }

  VictoryCondition JsonReader<VictoryCondition>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<VictoryCondition>;
    const VictoryConditionType victory_condition_type = readField<VictoryConditionType>(value, Fields::kType);
    VictoryCondition victory_condition;
    if (victory_condition_type != VictoryConditionType::Normal)
    {
      const Json::Value& details_json = getJsonField(value, Fields::kDetails);
      victory_condition.details = readVictoryConditionDetailsVariant(details_json, victory_condition_type);
    }
    return victory_condition;
  }
}
