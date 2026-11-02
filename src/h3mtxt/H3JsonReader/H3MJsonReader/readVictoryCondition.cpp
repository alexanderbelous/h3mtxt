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
  h3m::SpecialVictoryConditionBase JsonReader2<h3m::SpecialVictoryConditionBase>::operator()() const
  {
    using Fields = FieldNames<h3m::SpecialVictoryConditionBase>;
    h3m::SpecialVictoryConditionBase base;
    readField(Fields::kAllowNormalWin, base.allow_normal_win);
    readField(Fields::kAppliesToComputer, base.applies_to_computer);
    return base;
  }

  template<VictoryConditionType T>
  VictoryConditionDetails<T> JsonReader2<VictoryConditionDetails<T>>::operator()() const
  {
    if constexpr (T == VictoryConditionType::Normal)
    {
      return {};
    }
    else
    {
      VictoryConditionDetails<T> details{ fromJson<h3m::SpecialVictoryConditionBase>(value()) };
      if constexpr (T == VictoryConditionType::AcquireArtifact)
      {
        readField("artifact_type", details.artifact_type);
      }
      else if constexpr (T == VictoryConditionType::AccumulateCreatures)
      {
        readField("creatures", details.creatures);
      }
      else if constexpr (T == VictoryConditionType::AccumulateResources)
      {
        readField("resources", details.resources);
      }
      else if constexpr (T == VictoryConditionType::UpgradeTown)
      {
        readField("coordinates", details.coordinates);
        readField("hall_level", details.hall_level);
        readField("castle_level", details.castle_level);
      }
      else if constexpr (T == VictoryConditionType::BuildGrail ||
                         T == VictoryConditionType::DefeatHero ||
                         T == VictoryConditionType::CaptureTown ||
                         T == VictoryConditionType::DefeatMonster)
      {
        readField("coordinates", details.coordinates);
      }
      else if constexpr (T == VictoryConditionType::FlagDwellings ||
                         T == VictoryConditionType::FlagMines ||
                         T == VictoryConditionType::DefeatAllMonsters)
      {
        // No fields other than those inherited from SpecialVictoryConditionBase.
      }
      else if constexpr (T == VictoryConditionType::TransportArtifact)
      {
        readField("artifact_type", details.artifact_type);
        readField("destination", details.destination);
      }
      else if constexpr (T == VictoryConditionType::SurviveBeyondATimeLimit)
      {
        readField("days", details.days);
      }
      else
      {
        static_assert(false, "Invalid VictoryConditionType.");
      }
      return details;
    }
  }

  template<>
  VictoryCondition JsonReader2<VictoryCondition>::operator()() const
  {
    using Fields = FieldNames<VictoryCondition>;
    const VictoryConditionType victory_condition_type = readField<VictoryConditionType>(Fields::kType);
    VictoryCondition victory_condition;
    if (victory_condition_type != VictoryConditionType::Normal)
    {
      const std::size_t variant_alternative_idx = VictoryCondition::getAlternativeIdx(victory_condition_type);
      if (variant_alternative_idx == std::variant_npos)
      {
        throw std::runtime_error("JsonReader<h3m::VictoryCondition>: invalid victory_condition_type");
      }
      victory_condition.details = VariantJsonReader<VictoryCondition::Details>{}(getField(Fields::kDetails),
                                                                                 variant_alternative_idx);
    }
    return victory_condition;
  }
}
