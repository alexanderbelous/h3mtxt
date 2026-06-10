#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/VariantJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/VictoryCondition.h>

#include <stdexcept>
#include <type_traits>

namespace h3json
{
  using ::h3m::VictoryCondition;
  using ::h3m::VictoryConditionDetails;
  using ::h3m::VictoryConditionType;

  template<>
  h3m::SpecialVictoryConditionBase
  JsonReader<h3m::SpecialVictoryConditionBase>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::SpecialVictoryConditionBase>;
    h3m::SpecialVictoryConditionBase base;
    readField(base.allow_normal_win, value, Fields::kAllowNormalWin);
    readField(base.applies_to_computer, value, Fields::kAppliesToComputer);
    return base;
  }

  template<>
  struct JsonReader<VictoryConditionDetails<VictoryConditionType::AcquireArtifact>>
  {
    VictoryConditionDetails<VictoryConditionType::AcquireArtifact> operator()(const Json::Value& value) const
    {
      VictoryConditionDetails<VictoryConditionType::AcquireArtifact> details {
        fromJson<h3m::SpecialVictoryConditionBase>(value)
      };
      readField(details.artifact_type, value, "artifact_type");
      return details;
    }
  };

  template<>
  struct JsonReader<VictoryConditionDetails<VictoryConditionType::AccumulateCreatures>>
  {
    VictoryConditionDetails<VictoryConditionType::AccumulateCreatures> operator()(const Json::Value& value) const
    {
      VictoryConditionDetails<VictoryConditionType::AccumulateCreatures> details {
        fromJson<h3m::SpecialVictoryConditionBase>(value)
      };
      readField(details.creature_type, value, "creature_type");
      readField(details.count, value, "count");
      return details;
    }
  };

  template<>
  struct JsonReader<VictoryConditionDetails<VictoryConditionType::AccumulateResources>>
  {
    VictoryConditionDetails<VictoryConditionType::AccumulateResources> operator()(const Json::Value& value) const
    {
      VictoryConditionDetails<VictoryConditionType::AccumulateResources> details {
        fromJson<h3m::SpecialVictoryConditionBase>(value)
      };
      readField(details.resource_type, value, "resource_type");
      readField(details.amount, value, "amount");
      return details;
    }
  };

  template<>
  struct JsonReader<VictoryConditionDetails<VictoryConditionType::UpgradeTown>>
  {
    VictoryConditionDetails<VictoryConditionType::UpgradeTown> operator()(const Json::Value& value) const
    {
      VictoryConditionDetails<VictoryConditionType::UpgradeTown> details {
        fromJson<h3m::SpecialVictoryConditionBase>(value)
      };
      readField(details.coordinates, value, "coordinates");
      readField(details.hall_level, value, "hall_level");
      readField(details.castle_level, value, "castle_level");
      return details;
    }
  };

  template<VictoryConditionType T>
  struct JsonReader<VictoryConditionDetails<T>, std::enable_if_t<T == VictoryConditionType::BuildGrail ||
                                                                 T == VictoryConditionType::DefeatHero ||
                                                                 T == VictoryConditionType::CaptureTown ||
                                                                 T == VictoryConditionType::DefeatMonster>>
  {
    VictoryConditionDetails<T> operator()(const Json::Value& value) const
    {
      VictoryConditionDetails<T> details {
        fromJson<h3m::SpecialVictoryConditionBase>(value)
      };
      readField(details.coordinates, value, "coordinates");
      return details;
    }
  };

  template<VictoryConditionType T>
  struct JsonReader<VictoryConditionDetails<T>, std::enable_if_t<T == VictoryConditionType::FlagDwellings ||
                                                                 T == VictoryConditionType::FlagMines ||
                                                                 T == VictoryConditionType::DefeatAllMonsters>>
  {
    VictoryConditionDetails<T> operator()(const Json::Value& value) const
    {
      return VictoryConditionDetails<T>{ fromJson<h3m::SpecialVictoryConditionBase>(value) };
    }
  };

  template<>
  struct JsonReader<VictoryConditionDetails<VictoryConditionType::TransportArtifact>>
  {
    VictoryConditionDetails<VictoryConditionType::TransportArtifact> operator()(const Json::Value& value) const
    {
      VictoryConditionDetails<VictoryConditionType::TransportArtifact> details {
        fromJson<h3m::SpecialVictoryConditionBase>(value)
      };
      readField(details.artifact_type, value, "artifact_type");
      readField(details.destination, value, "destination");
      return details;
    }
  };

  template<>
  struct JsonReader<VictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit>>
  {
    VictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit> operator()(const Json::Value& value) const
    {
      VictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit> details {
        fromJson<h3m::SpecialVictoryConditionBase>(value)
      };
      readField(details.days, value, "days");
      return details;
    }
  };

  template<>
  struct JsonReader<VictoryConditionDetails<VictoryConditionType::Normal>>
  {
    VictoryConditionDetails<VictoryConditionType::Normal> operator()(const Json::Value&) const
    {
      return {};
    }
  };

  template<>
  VictoryCondition JsonReader<VictoryCondition>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<VictoryCondition>;
    const VictoryConditionType victory_condition_type = readField<VictoryConditionType>(value, Fields::kType);
    VictoryCondition victory_condition;
    if (victory_condition_type != VictoryConditionType::Normal)
    {
      const std::size_t variant_alternative_idx = VictoryCondition::getAlternativeIdx(victory_condition_type);
      if (variant_alternative_idx == std::variant_npos)
      {
        throw std::runtime_error("JsonReader<h3m::VictoryCondition>: invalid victory_condition_type");
      }
      victory_condition.details = VariantJsonReader<VictoryCondition::Details>{}(getJsonField(value, Fields::kDetails),
                                                                                 variant_alternative_idx);
    }
    return victory_condition;
  }
}
