#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/VariantJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/VictoryCondition.h>

#include <stdexcept>

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

  template<VictoryConditionType T>
  VictoryConditionDetails<T>
  JsonReader<VictoryConditionDetails<T>>::operator()(const Json::Value& value) const
  {
    if constexpr (T == VictoryConditionType::Normal)
    {
      return {};
    }
    else
    {
      VictoryConditionDetails<T> details{ fromJson<h3m::SpecialVictoryConditionBase>(value) };
      if constexpr (T == VictoryConditionType::AcquireArtifact)
      {
        readField(details.artifact_type, value, "artifact_type");
      }
      else if constexpr (T == VictoryConditionType::AccumulateCreatures)
      {
        readField(details.creatures, value, "creatures");
      }
      else if constexpr (T == VictoryConditionType::AccumulateResources)
      {
        readField(details.resources, value, "resources");
      }
      else if constexpr (T == VictoryConditionType::UpgradeTown)
      {
        readField(details.coordinates, value, "coordinates");
        readField(details.hall_level, value, "hall_level");
        readField(details.castle_level, value, "castle_level");
      }
      else if constexpr (T == VictoryConditionType::BuildGrail ||
                         T == VictoryConditionType::DefeatHero ||
                         T == VictoryConditionType::CaptureTown ||
                         T == VictoryConditionType::DefeatMonster)
      {
        readField(details.coordinates, value, "coordinates");
      }
      else if constexpr (T == VictoryConditionType::FlagDwellings ||
                         T == VictoryConditionType::FlagMines ||
                         T == VictoryConditionType::DefeatAllMonsters)
      {
        // No fields other than those inherited from SpecialVictoryConditionBase.
      }
      else if constexpr (T == VictoryConditionType::TransportArtifact)
      {
        readField(details.artifact_type, value, "artifact_type");
        readField(details.destination, value, "destination");
      }
      else if constexpr (T == VictoryConditionType::SurviveBeyondATimeLimit)
      {
        readField(details.days, value, "days");
      }
      else
      {
        static_assert(false, "Invalid VictoryConditionType.");
      }
      return details;
    }
  }

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
