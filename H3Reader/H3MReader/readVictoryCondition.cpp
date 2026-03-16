#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/Utils/EnumSequence.h>
#include <h3mtxt/Map/VictoryCondition.h>

#include <array>
#include <type_traits>

namespace h3m
{
  namespace
  {
    void readSpecialVictoryConditionBase(const H3MReader& reader, SpecialVictoryConditionBase& base)
    {
      base.allow_normal_win = reader.readBool();
      base.applies_to_computer = reader.readBool();
    }

    template<VictoryConditionType T, class Enable = void>
    struct ReadVictoryConditionDetails
    {
      VictoryConditionDetails<T> operator()(const H3MReader&) const
      {
        static_assert(false, "Missing specialization for ReadVictoryConditionDetails<T>.");
        return {};
      }
    };

    template<>
    struct ReadVictoryConditionDetails<VictoryConditionType::AcquireArtifact>
    {
      VictoryConditionDetails<VictoryConditionType::AcquireArtifact> operator()(const H3MReader& reader) const
      {
        VictoryConditionDetails<VictoryConditionType::AcquireArtifact> details;
        readSpecialVictoryConditionBase(reader, details);
        details.artifact_type = reader.readEnum<ArtifactType>();
        return details;
      }
    };

    template<>
    struct ReadVictoryConditionDetails<VictoryConditionType::AccumulateCreatures>
    {
      VictoryConditionDetails<VictoryConditionType::AccumulateCreatures> operator()(const H3MReader& reader) const
      {
        VictoryConditionDetails<VictoryConditionType::AccumulateCreatures> details;
        readSpecialVictoryConditionBase(reader, details);
        details.creature_type = reader.readEnum<CreatureType>();
        details.count = reader.readInt<std::int32_t>();
        return details;
      }
    };

    template<>
    struct ReadVictoryConditionDetails<VictoryConditionType::AccumulateResources>
    {
      VictoryConditionDetails<VictoryConditionType::AccumulateResources> operator()(const H3MReader& reader) const
      {
        VictoryConditionDetails<VictoryConditionType::AccumulateResources> details;
        readSpecialVictoryConditionBase(reader, details);
        details.resource_type = reader.readEnum<ResourceType>();
        details.amount = reader.readInt<std::int32_t>();
        return details;
      }
    };

    template<>
    struct ReadVictoryConditionDetails<VictoryConditionType::UpgradeTown>
    {
      VictoryConditionDetails<VictoryConditionType::UpgradeTown> operator()(const H3MReader& reader) const
      {
        VictoryConditionDetails<VictoryConditionType::UpgradeTown> details;
        readSpecialVictoryConditionBase(reader, details);
        details.coordinates = reader.readCoordinates();
        details.hall_level = reader.readInt<std::uint8_t>();
        details.castle_level = reader.readInt<std::uint8_t>();
        return details;
      }
    };

    template<VictoryConditionType T>
    struct ReadVictoryConditionDetails<T, std::enable_if_t<T == VictoryConditionType::BuildGrail ||
                                                           T == VictoryConditionType::DefeatHero ||
                                                           T == VictoryConditionType::CaptureTown ||
                                                           T == VictoryConditionType::DefeatMonster>>
    {
      VictoryConditionDetails<T> operator()(const H3MReader& reader) const
      {
        VictoryConditionDetails<T> details;
        readSpecialVictoryConditionBase(reader, details);
        details.coordinates = reader.readCoordinates();
        return details;
      }
    };

    template<VictoryConditionType T>
    struct ReadVictoryConditionDetails<T, std::enable_if_t<T == VictoryConditionType::FlagDwellings ||
                                                           T == VictoryConditionType::FlagMines ||
                                                           T == VictoryConditionType::DefeatAllMonsters>>
    {
      VictoryConditionDetails<T> operator()(const H3MReader& reader) const
      {
        VictoryConditionDetails<T> details;
        readSpecialVictoryConditionBase(reader, details);
        return details;
      }
    };

    template<>
    struct ReadVictoryConditionDetails<VictoryConditionType::TransportArtifact>
    {
      VictoryConditionDetails<VictoryConditionType::TransportArtifact> operator()(const H3MReader& reader) const
      {
        VictoryConditionDetails<VictoryConditionType::TransportArtifact> details;
        readSpecialVictoryConditionBase(reader, details);
        details.artifact_type = reader.readInt<std::uint8_t>();
        details.destination = reader.readCoordinates();
        return details;
      }
    };

    template<>
    struct ReadVictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit>
    {
      VictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit> operator()(const H3MReader& reader) const
      {
        VictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit> details;
        readSpecialVictoryConditionBase(reader, details);
        details.days = reader.readInt<std::int32_t>();
        return {};
      }
    };

    template<>
    struct ReadVictoryConditionDetails<VictoryConditionType::Normal>
    {
      VictoryConditionDetails<VictoryConditionType::Normal> operator()(const H3MReader&) const
      {
        return {};
      }
    };

    template<VictoryConditionType T>
    VictoryCondition::Details readVictoryConditionDetails(const H3MReader& reader)
    {
      return ReadVictoryConditionDetails<T>{}(reader);
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

  VictoryCondition H3MReader::readVictoryCondition() const
  {
    const VictoryConditionType victory_condition_type = readEnum<VictoryConditionType>();
    return VictoryCondition{readVictoryConditionDetailsVariant(*this, victory_condition_type)};
  }
}
