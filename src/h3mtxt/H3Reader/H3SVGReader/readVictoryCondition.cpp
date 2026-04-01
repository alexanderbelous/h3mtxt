#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>

#include <h3mtxt/Map/Utils/EnumSequence.h>
#include <h3mtxt/SavedGame/VictoryCondition.h>

#include <array>

namespace h3svg
{
  namespace
  {
    using ::h3m::EnumSequence;
    using ::h3m::MakeEnumSequence;

    // TODO: reuse the code from H3MReader.
    void readSpecialVictoryConditionBase(const H3SVGReader& reader, SpecialVictoryConditionBase& base)
    {
      base.allow_normal_win = reader.readBool();
      base.applies_to_computer = reader.readBool();
    }

    template<VictoryConditionType T>
    VictoryCondition::Details readVictoryConditionDetailsAsVariant(const H3SVGReader& reader)
    {
      return reader.readVictoryConditionDetails<T>();
    }

    VictoryCondition::Details readVictoryConditionDetailsVariant(const H3SVGReader& reader,
                                                                 VictoryConditionType victory_condition_type)
    {
      // Type of a pointer to a function that takes const H3SVGReader& and returns VictoryCondition::Details.
      using ReadVictoryConditionDetailsPtr = VictoryCondition::Details(*)(const H3SVGReader& reader);
      // Generate (at compile time) an array of function pointers for each instantiation of
      // readVictoryConditionDetailsAsVariant() ordered by VictoryConditionType.
      static constexpr std::array<ReadVictoryConditionDetailsPtr, kNumSpecialVictoryConditions>
      kVictoryConditionDetailsReaders =
        [] <VictoryConditionType... victory_condition_types>
        (EnumSequence<VictoryConditionType, victory_condition_types...> seq)
        consteval
      {
        return std::array<ReadVictoryConditionDetailsPtr, sizeof...(victory_condition_types)>
        {
          &readVictoryConditionDetailsAsVariant<victory_condition_types>...
        };
      }(MakeEnumSequence<VictoryConditionType, kNumSpecialVictoryConditions>{});

      // Edge case for VictoryConditionType::Normal.
      if (victory_condition_type == VictoryConditionType::Normal)
      {
        return readVictoryConditionDetailsAsVariant<VictoryConditionType::Normal>(reader);
      }
      // Otherwise, invoke a function from the generated array.
      return kVictoryConditionDetailsReaders.at(static_cast<std::size_t>(victory_condition_type))(reader);
    }
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::AcquireArtifact> H3SVGReader::readVictoryConditionDetails() const
  {
    VictoryConditionDetails<VictoryConditionType::AcquireArtifact> details;
    readSpecialVictoryConditionBase(*this, details);
    details.artifact_type = readEnum<ArtifactType8>();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::AccumulateCreatures> H3SVGReader::readVictoryConditionDetails() const
  {
    VictoryConditionDetails<VictoryConditionType::AccumulateCreatures> details;
    readSpecialVictoryConditionBase(*this, details);
    details.creature_type = readEnum<CreatureType8>();
    details.count = readInt<std::int32_t>();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::AccumulateResources> H3SVGReader::readVictoryConditionDetails() const
  {
    // TODO: reuse the code from H3MReader
    VictoryConditionDetails<VictoryConditionType::AccumulateResources> details;
    readSpecialVictoryConditionBase(*this, details);
    details.resource_type = readEnum<ResourceType>();
    details.amount = readInt<std::int32_t>();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::UpgradeTown> H3SVGReader::readVictoryConditionDetails() const
  {
    // TODO: reuse the code from H3MReader
    VictoryConditionDetails<VictoryConditionType::UpgradeTown> details;
    readSpecialVictoryConditionBase(*this, details);
    details.coordinates = readCoordinates();
    details.hall_level = readInt<std::uint8_t>();
    details.castle_level = readInt<std::uint8_t>();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::BuildGrail> H3SVGReader::readVictoryConditionDetails() const
  {
    // TODO: reuse the code from H3MReader
    VictoryConditionDetails<VictoryConditionType::BuildGrail> details;
    readSpecialVictoryConditionBase(*this, details);
    details.coordinates = readCoordinates();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::DefeatHero> H3SVGReader::readVictoryConditionDetails() const
  {
    VictoryConditionDetails<VictoryConditionType::DefeatHero> details;
    readSpecialVictoryConditionBase(*this, details);
    details.hero = readEnum<HeroType>();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::CaptureTown> H3SVGReader::readVictoryConditionDetails() const
  {
    // TODO: reuse the code from H3MReader
    VictoryConditionDetails<VictoryConditionType::CaptureTown> details;
    readSpecialVictoryConditionBase(*this, details);
    details.coordinates = readCoordinates();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::DefeatMonster> H3SVGReader::readVictoryConditionDetails() const
  {
    // TODO: reuse the code from H3MReader
    VictoryConditionDetails<VictoryConditionType::DefeatMonster> details;
    readSpecialVictoryConditionBase(*this, details);
    details.coordinates = readCoordinates();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::FlagDwellings> H3SVGReader::readVictoryConditionDetails() const
  {
    // TODO: reuse the code from H3MReader
    VictoryConditionDetails<VictoryConditionType::FlagDwellings> details;
    readSpecialVictoryConditionBase(*this, details);
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::FlagMines> H3SVGReader::readVictoryConditionDetails() const
  {
    // TODO: reuse the code from H3MReader
    VictoryConditionDetails<VictoryConditionType::FlagMines> details;
    readSpecialVictoryConditionBase(*this, details);
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::TransportArtifact> H3SVGReader::readVictoryConditionDetails() const
  {
    // TODO: reuse the code from H3MReader
    VictoryConditionDetails<VictoryConditionType::TransportArtifact> details;
    readSpecialVictoryConditionBase(*this, details);
    details.artifact_type = readInt<std::uint8_t>();
    details.destination = readCoordinates();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::DefeatAllMonsters> H3SVGReader::readVictoryConditionDetails() const
  {
    // TODO: reuse the code from H3MReader
    VictoryConditionDetails<VictoryConditionType::DefeatAllMonsters> details;
    readSpecialVictoryConditionBase(*this, details);
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit> H3SVGReader::readVictoryConditionDetails() const
  {
    // TODO: reuse the code from H3MReader
    VictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit> details;
    readSpecialVictoryConditionBase(*this, details);
    details.days = readInt<std::int32_t>();
    return details;
  }

  template<>
  VictoryConditionDetails<VictoryConditionType::Normal> H3SVGReader::readVictoryConditionDetails() const
  {
    // TODO: reuse the code from H3MReader
    return {};
  }

  VictoryCondition H3SVGReader::readVictoryCondition() const
  {
    const VictoryConditionType victory_condition_type = readEnum<VictoryConditionType>();
    return VictoryCondition{ .details = readVictoryConditionDetailsVariant(*this, victory_condition_type) };
  }
}
