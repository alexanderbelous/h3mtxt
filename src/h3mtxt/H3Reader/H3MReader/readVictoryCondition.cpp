#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/Utils/EnumSequence.h>
#include <h3mtxt/Map/VictoryCondition.h>

#include <array>
#include <type_traits>

namespace h3m
{
  namespace
  {
    template<VictoryConditionType T>
    VictoryCondition::Details readVictoryConditionDetails(const H3MReader& reader)
    {
      return reader.readVictoryConditionDetails<T>();
    }

    VictoryCondition::Details readVictoryConditionDetailsVariant(const H3MReader& reader,
                                                                 VictoryConditionType victory_condition_type)
    {
      // Type of a pointer to a function that takes const H3MReader& and returns VictoryCondition::Details.
      using ReadVictoryConditionDetailsPtr = VictoryCondition::Details(*)(const H3MReader& reader);
      // Generate (at compile time) an array of function pointers for each instantiation of
      // readVictoryConditionDetails() ordered by VictoryConditionType.
      static constexpr std::array<ReadVictoryConditionDetailsPtr, kNumSpecialVictoryConditions>
      kVictoryConditionDetailsReaders =
        [] <VictoryConditionType... victory_condition_types>
        (EnumSequence<VictoryConditionType, victory_condition_types...> seq)
        consteval
      {
        return std::array<ReadVictoryConditionDetailsPtr, sizeof...(victory_condition_types)>
        {
          &readVictoryConditionDetails<victory_condition_types>...
        };
      }(MakeEnumSequence<VictoryConditionType, kNumSpecialVictoryConditions>{});

      // Edge case for VictoryConditionType::Normal.
      if (victory_condition_type == VictoryConditionType::Normal)
      {
        return readVictoryConditionDetails<VictoryConditionType::Normal>(reader);
      }
      // Otherwise, invoke a function from the generated array.
      return kVictoryConditionDetailsReaders.at(static_cast<std::size_t>(victory_condition_type))(reader);
    }
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
    details.creature_type = readEnum<CreatureType>();
    details.count = readInt<std::int32_t>();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::AccumulateResources> H3MReader::readVictoryConditionDetails() const
  {
    VictoryConditionDetails<VictoryConditionType::AccumulateResources> details{ readSpecialVictoryConditionBase() };
    details.resource_type = readEnum<ResourceType>();
    details.amount = readInt<std::int32_t>();
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
    return {};
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::Normal> H3MReader::readVictoryConditionDetails() const
  {
    return {};
  }

  VictoryCondition H3MReader::readVictoryCondition() const
  {
    const VictoryConditionType victory_condition_type = readEnum<VictoryConditionType>();
    return VictoryCondition{readVictoryConditionDetailsVariant(*this, victory_condition_type)};
  }
}
