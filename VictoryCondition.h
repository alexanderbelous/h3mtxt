#pragma once

#include <h3mparser/Constants/CreatureType.h>
#include <h3mparser/Constants/ResourceType.h>
#include <h3mparser/Constants/VictoryConditionType.h>
#include <h3mparser/Base.h>

#include <cstdint>
#include <variant>

namespace h3m
{

// Template class for storing details of a victory condition.
// The default implementation stores no details.
template<VictoryConditionType T>
struct VictoryConditionDetails
{
};

// Base class for special victory conditions.
struct SpecialVictoryConditionBase
{
  // True if the normal victory condition (defeat all enemies) is also enabled, false otherwise.
  Bool allow_normal_win {};
  // True if the special victory condition applies to the computer, false otherwise.
  Bool applies_to_computer {};
};

// Specialization for AcquireArtifact.
template<>
struct VictoryConditionDetails<VictoryConditionType::AcquireArtifact> : SpecialVictoryConditionBase
{
  // TODO: probably should be an enum.
  std::uint16_t artifact_type {};
};

// Specialization for AccumulateCreatures.
template<>
struct VictoryConditionDetails<VictoryConditionType::AccumulateCreatures> : SpecialVictoryConditionBase
{
  CreatureType creature_type {};
  // The number of creatures to accumulate.
  std::uint32_t count {};
};

// Specialization for AccumulateResources.
template<>
struct VictoryConditionDetails<VictoryConditionType::AccumulateResources> : SpecialVictoryConditionBase
{
  ResourceType resource_type {};
  // The number of creatures to accumulate.
  std::uint32_t amount {};
};

// Specialization for UpgradeTown.
template<>
struct VictoryConditionDetails<VictoryConditionType::UpgradeTown> : SpecialVictoryConditionBase
{
  // If all x/y/z are equal to 0xFF, implies any town.
  std::uint8_t x {};
  std::uint8_t y {};
  std::uint8_t z {};
  // 0 - Town, 1 - City, 2 - Capitol.
  std::uint8_t hall_level {};
  // 0 - Fort, 1 - Citadel, 2 - Castle.
  std::uint8_t castle_level {};
};

// Specialization for FlagDwellings.
template<>
struct VictoryConditionDetails<VictoryConditionType::FlagDwellings> : SpecialVictoryConditionBase
{
};

// Specialization for FlagMines.
template<>
struct VictoryConditionDetails<VictoryConditionType::FlagMines> : SpecialVictoryConditionBase
{
};

// Specialization for TransportArtifact.
template<>
struct VictoryConditionDetails<VictoryConditionType::TransportArtifact> : SpecialVictoryConditionBase
{
  // Interestingly, the type is stored here in a single byte, even though in AcquireArtifact it's stored in 2 bytes.
  std::uint8_t artifact_type {};
  std::uint8_t x {};
  std::uint8_t y {};
  std::uint8_t z {};
};

class VictoryCondition
{
public:
  // Constructs a victory condition.
  // \param T - type of the victory condition.
  // \param details - details of the victory condition.
  // \return the constructed victory condition.
  template<VictoryConditionType T>
  static VictoryCondition makeVictoryCondition(VictoryConditionDetails<T> details);

  // \return the type of the victory condition.
  VictoryConditionType type() const;

  // Get the details of the victory condition.
  // \param T - type of the victory condition.
  // \return the details of the victory condition, nullptr if T doesn't match the type returned by type().
  template<VictoryConditionType T>
  const VictoryConditionDetails<T>* details() const;

private:
  std::variant<
    VictoryConditionDetails<VictoryConditionType::AcquireArtifact>,
    VictoryConditionDetails<VictoryConditionType::AccumulateCreatures>,
    VictoryConditionDetails<VictoryConditionType::AccumulateResources>,
    VictoryConditionDetails<VictoryConditionType::UpgradeTown>,
    VictoryConditionDetails<VictoryConditionType::BuildGrail>,
    VictoryConditionDetails<VictoryConditionType::DefeatHero>,
    VictoryConditionDetails<VictoryConditionType::CaptureTown>,
    VictoryConditionDetails<VictoryConditionType::DefeatMonster>,
    VictoryConditionDetails<VictoryConditionType::FlagDwellings>,
    VictoryConditionDetails<VictoryConditionType::FlagMines>,
    VictoryConditionDetails<VictoryConditionType::TransportArtifact>,
    VictoryConditionDetails<VictoryConditionType::Normal>
  > details_ {};
};

}
