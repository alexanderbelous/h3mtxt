#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/Map/VictoryCondition.h>

#include <array>
#include <stdexcept>
#include <type_traits>

namespace h3m::H3Reader_NS
{
  namespace
  {
    void readSpecialVictoryConditionBase(std::istream& stream, SpecialVictoryConditionBase& base)
    {
      base.allow_normal_win = readBool(stream);
      base.applies_to_computer = readBool(stream);
    }

    template<VictoryConditionType T, class Enable = void>
    struct ReadVictoryConditionDetails
    {
      VictoryConditionDetails<T> operator()(std::istream& stream) const
      {
        static_assert(false, "Missing specialization for ReadVictoryConditionDetails<T>.");
      }
    };

    template<>
    struct ReadVictoryConditionDetails<VictoryConditionType::AcquireArtifact>
    {
      VictoryConditionDetails<VictoryConditionType::AcquireArtifact> operator()(std::istream& stream) const
      {
        VictoryConditionDetails<VictoryConditionType::AcquireArtifact> details;
        readSpecialVictoryConditionBase(stream, details);
        details.artifact_type = readEnum<ArtifactType>(stream);
        return details;
      }
    };

    template<>
    struct ReadVictoryConditionDetails<VictoryConditionType::AccumulateCreatures>
    {
      VictoryConditionDetails<VictoryConditionType::AccumulateCreatures> operator()(std::istream& stream) const
      {
        VictoryConditionDetails<VictoryConditionType::AccumulateCreatures> details;
        readSpecialVictoryConditionBase(stream, details);
        details.creature_type = readEnum<CreatureType>(stream);
        details.count = readInt<std::int32_t>(stream);
        return details;
      }
    };

    template<>
    struct ReadVictoryConditionDetails<VictoryConditionType::AccumulateResources>
    {
      VictoryConditionDetails<VictoryConditionType::AccumulateResources> operator()(std::istream& stream) const
      {
        VictoryConditionDetails<VictoryConditionType::AccumulateResources> details;
        readSpecialVictoryConditionBase(stream, details);
        details.resource_type = readEnum<ResourceType>(stream);
        details.amount = readInt<std::uint32_t>(stream);
        return details;
      }
    };

    template<>
    struct ReadVictoryConditionDetails<VictoryConditionType::UpgradeTown>
    {
      VictoryConditionDetails<VictoryConditionType::UpgradeTown> operator()(std::istream& stream) const
      {
        VictoryConditionDetails<VictoryConditionType::UpgradeTown> details;
        readSpecialVictoryConditionBase(stream, details);
        details.x = readInt<std::uint8_t>(stream);
        details.y = readInt<std::uint8_t>(stream);
        details.z = readInt<std::uint8_t>(stream);
        details.hall_level = readInt<std::uint8_t>(stream);
        details.castle_level = readInt<std::uint8_t>(stream);
        return details;
      }
    };

    template<VictoryConditionType T>
    struct ReadVictoryConditionDetails<T, std::enable_if_t<T == VictoryConditionType::BuildGrail ||
                                                           T == VictoryConditionType::DefeatHero ||
                                                           T == VictoryConditionType::CaptureTown ||
                                                           T == VictoryConditionType::DefeatMonster>>
    {
      VictoryConditionDetails<T> operator()(std::istream& stream) const
      {
        VictoryConditionDetails<T> details;
        readSpecialVictoryConditionBase(stream, details);
        details.x = readInt<std::uint8_t>(stream);
        details.y = readInt<std::uint8_t>(stream);
        details.z = readInt<std::uint8_t>(stream);
        return details;
      }
    };

    template<VictoryConditionType T>
    struct ReadVictoryConditionDetails<T, std::enable_if_t<T == VictoryConditionType::FlagDwellings ||
                                                           T == VictoryConditionType::FlagMines>>
    {
      VictoryConditionDetails<T> operator()(std::istream& stream) const
      {
        VictoryConditionDetails<T> details;
        readSpecialVictoryConditionBase(stream, details);
        return details;
      }
    };

    template<>
    struct ReadVictoryConditionDetails<VictoryConditionType::TransportArtifact>
    {
      VictoryConditionDetails<VictoryConditionType::TransportArtifact> operator()(std::istream& stream) const
      {
        VictoryConditionDetails<VictoryConditionType::TransportArtifact> details;
        readSpecialVictoryConditionBase(stream, details);
        details.artifact_type = readInt<std::uint8_t>(stream);
        details.x = readInt<std::uint8_t>(stream);
        details.y = readInt<std::uint8_t>(stream);
        details.z = readInt<std::uint8_t>(stream);
        return details;
      }
    };

    template<>
    struct ReadVictoryConditionDetails<VictoryConditionType::Normal>
    {
      VictoryConditionDetails<VictoryConditionType::Normal> operator()(std::istream&) const
      {
        return {};
      }
    };

    template<VictoryConditionType T>
    VictoryConditionDetails<T> readVictoryConditionDetails(std::istream& stream)
    {
      return ReadVictoryConditionDetails<T>{}(stream);
    }

    VictoryCondition::Details readVictoryConditionDetailsVariant(std::istream& stream,
                                                                 VictoryConditionType victory_condition_type)
    {
      switch (victory_condition_type)
      {
      case VictoryConditionType::AcquireArtifact:
        return readVictoryConditionDetails<VictoryConditionType::AcquireArtifact>(stream);
      case VictoryConditionType::AccumulateCreatures:
        return readVictoryConditionDetails<VictoryConditionType::AccumulateCreatures>(stream);
      case VictoryConditionType::AccumulateResources:
        return readVictoryConditionDetails<VictoryConditionType::AccumulateResources>(stream);
      case VictoryConditionType::UpgradeTown:
        return readVictoryConditionDetails<VictoryConditionType::UpgradeTown>(stream);
      case VictoryConditionType::BuildGrail:
        return readVictoryConditionDetails<VictoryConditionType::BuildGrail>(stream);
      case VictoryConditionType::DefeatHero:
        return readVictoryConditionDetails<VictoryConditionType::DefeatHero>(stream);
      case VictoryConditionType::CaptureTown:
        return readVictoryConditionDetails<VictoryConditionType::CaptureTown>(stream);
      case VictoryConditionType::DefeatMonster:
        return readVictoryConditionDetails<VictoryConditionType::DefeatMonster>(stream);
      case VictoryConditionType::FlagDwellings:
        return readVictoryConditionDetails<VictoryConditionType::FlagDwellings>(stream);
      case VictoryConditionType::FlagMines:
        return readVictoryConditionDetails<VictoryConditionType::FlagMines>(stream);
      case VictoryConditionType::TransportArtifact:
        return readVictoryConditionDetails<VictoryConditionType::TransportArtifact>(stream);
      case VictoryConditionType::Normal:
        return readVictoryConditionDetails<VictoryConditionType::Normal>(stream);
      default:
        throw std::runtime_error("Invalid victory condition type.");
      }
    }
  }

  VictoryCondition readVictoryCondition(std::istream& stream)
  {
    const VictoryConditionType victory_condition_type = readEnum<VictoryConditionType>(stream);
    return VictoryCondition{readVictoryConditionDetailsVariant(stream, victory_condition_type)};
  }
}
