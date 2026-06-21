#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/Utils/SwitchStatement.h>
#include <h3mtxt/Map/VictoryCondition.h>

namespace h3m
{
  namespace
  {
    template<VictoryConditionType T>
    VictoryCondition::Details readVictoryConditionDetails(const H3MReader& reader)
    {
      return reader.readVictoryConditionDetails<T>();
    }

    // Convert the function template readVictoryConditionDetails<T>() into an alias template,
    // so that it can be passed as a template template parameter to generateSwitchStatement().
    template<VictoryConditionType T>
    using VictoryConditionDetailsReaderTemplateAlias = SwitchStatement_NS::StaticConstant<&readVictoryConditionDetails<T>>;
  }

  SpecialVictoryConditionBase H3MReader::readSpecialVictoryConditionBase() const
  {
    SpecialVictoryConditionBase base;
    base.allow_normal_win = readBool();
    base.applies_to_computer = readBool();
    return base;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::AcquireArtifact> H3MReader::readVictoryConditionDetails() const
  {
    VictoryConditionDetails<VictoryConditionType::AcquireArtifact> details{ readSpecialVictoryConditionBase() };
    details.artifact_type = readEnum<ArtifactType>();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::AccumulateCreatures> H3MReader::readVictoryConditionDetails() const
  {
    VictoryConditionDetails<VictoryConditionType::AccumulateCreatures> details{ readSpecialVictoryConditionBase() };
    details.creatures = readTypedQuantity<CreatureType, std::int32_t>();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::AccumulateResources> H3MReader::readVictoryConditionDetails() const
  {
    VictoryConditionDetails<VictoryConditionType::AccumulateResources> details{ readSpecialVictoryConditionBase() };
    details.resources = readTypedQuantity<ResourceType, std::int32_t>();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::UpgradeTown> H3MReader::readVictoryConditionDetails() const
  {
    VictoryConditionDetails<VictoryConditionType::UpgradeTown> details{ readSpecialVictoryConditionBase() };
    details.coordinates = readCoordinates();
    details.hall_level = readInt<std::uint8_t>();
    details.castle_level = readInt<std::uint8_t>();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::BuildGrail> H3MReader::readVictoryConditionDetails() const
  {
    VictoryConditionDetails<VictoryConditionType::BuildGrail> details{ readSpecialVictoryConditionBase() };
    details.coordinates = readCoordinates();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::DefeatHero> H3MReader::readVictoryConditionDetails() const
  {
    VictoryConditionDetails<VictoryConditionType::DefeatHero> details{ readSpecialVictoryConditionBase() };
    details.coordinates = readCoordinates();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::CaptureTown> H3MReader::readVictoryConditionDetails() const
  {
    VictoryConditionDetails<VictoryConditionType::CaptureTown> details{ readSpecialVictoryConditionBase() };
    details.coordinates = readCoordinates();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::DefeatMonster> H3MReader::readVictoryConditionDetails() const
  {
    VictoryConditionDetails<VictoryConditionType::DefeatMonster> details{ readSpecialVictoryConditionBase() };
    details.coordinates = readCoordinates();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::FlagDwellings> H3MReader::readVictoryConditionDetails() const
  {
    return { readSpecialVictoryConditionBase() };
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::FlagMines> H3MReader::readVictoryConditionDetails() const
  {
    return { readSpecialVictoryConditionBase() };
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::TransportArtifact> H3MReader::readVictoryConditionDetails() const
  {
    VictoryConditionDetails<VictoryConditionType::TransportArtifact> details{ readSpecialVictoryConditionBase() };
    details.artifact_type = readInt<std::uint8_t>();
    details.destination = readCoordinates();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::DefeatAllMonsters> H3MReader::readVictoryConditionDetails() const
  {
    return { readSpecialVictoryConditionBase() };
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit> H3MReader::readVictoryConditionDetails() const
  {
    VictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit> details{ readSpecialVictoryConditionBase() };
    details.days = readInt<std::int32_t>();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::Normal> H3MReader::readVictoryConditionDetails() const
  {
    return {};
  }

  VictoryCondition H3MReader::readVictoryCondition() const
  {
    // Generate a switch statement for all *special* victory condition types.
    // read_victory_condition_details(N, reader) will trigger readVictoryConditionDetails<N>(reader).
    static constexpr auto read_special_victory_condition_details =
      SwitchStatement_NS::generateSwitchStatement<VictoryConditionType,
                                                  kNumSpecialVictoryConditions,
                                                  VictoryConditionDetailsReaderTemplateAlias>();

    // Read the type of the victory condition.
    const VictoryConditionType victory_condition_type = readEnum<VictoryConditionType>();
    // Edge case for VictoryConditionType::Normal.
    if (victory_condition_type == VictoryConditionType::Normal)
    {
      return VictoryCondition{ .details = readVictoryConditionDetails<VictoryConditionType::Normal>() };
    }
    // Otherwise, execute the generated switch statement.
    return VictoryCondition{ .details = read_special_victory_condition_details(victory_condition_type, *this) };
  }
}
