#pragma once

#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/ArtifactType.h>
#include <h3mtxt/Map/Constants/CreatureType.h>
#include <h3mtxt/Map/Constants/ResourceType.h>
#include <h3mtxt/Map/Constants/VictoryConditionType.h>

#include <cstdint>
#include <variant>

namespace h3m
{
  // Template class for storing details of a victory condition.
  template<VictoryConditionType T, class Enable = void>
  struct VictoryConditionDetails;

  // Specialization for Normal.
  template<>
  struct VictoryConditionDetails<VictoryConditionType::Normal>
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
    // FYI: None (0xFFFF) can be used here, but it will trigger victory at the end of Day 1
    // ("Congratulations! You have found (null), and can claim victory!").
    ArtifactType artifact_type {};
  };

  // Specialization for AccumulateCreatures.
  template<>
  struct VictoryConditionDetails<VictoryConditionType::AccumulateCreatures> : SpecialVictoryConditionBase
  {
    CreatureType creature_type {};
    // The number of creatures to accumulate.
    // * The Map Editor only allows a value within [1; 99999], but any signed 32-bit integer can be used here
    //   (e.g., 1,000,000 Peasants).
    // * A negative value almost immediately leads to a victory, though.
    std::int32_t count {};
  };

  // Specialization for AccumulateResources.
  template<>
  struct VictoryConditionDetails<VictoryConditionType::AccumulateResources> : SpecialVictoryConditionBase
  {
    ResourceType resource_type {};
    // The amount to accumulate.
    // The Map Editor only allows setting a value from [1; 9999999], but any signed 32-bit integer can be used here.
    std::int32_t amount {};
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

  // Partial specialization for BuildGrail, DefeatHero, CaptureTown, DefeatMonster.
  template<VictoryConditionType T>
  struct VictoryConditionDetails<T, std::enable_if_t<T == VictoryConditionType::BuildGrail ||
                                                     T == VictoryConditionType::DefeatHero ||
                                                     T == VictoryConditionType::CaptureTown ||
                                                     T == VictoryConditionType::DefeatMonster>> : SpecialVictoryConditionBase
  {
    // Coordinates of the actionable spot. If T == BuildGrail and all x/y/z are equal to 0xFF, implies any town.
    std::uint8_t x {};
    std::uint8_t y {};
    std::uint8_t z {};
  };

  // Partial specialization for FlagDwellings, FlagMines, DefeatAllMonsters.
  template<VictoryConditionType T>
  struct VictoryConditionDetails<T, std::enable_if_t<T == VictoryConditionType::FlagDwellings ||
                                                     T == VictoryConditionType::FlagMines ||
                                                     T == VictoryConditionType::DefeatAllMonsters>> : SpecialVictoryConditionBase
  {
  };

  // Specialization for TransportArtifact.
  template<>
  struct VictoryConditionDetails<VictoryConditionType::TransportArtifact> : SpecialVictoryConditionBase
  {
    // Interestingly, the type is stored here in a single byte, even though in AcquireArtifact it's stored in 2 bytes.
    // The game supports "unusual" artifacts here (e.g., Spellbook), even though the Map Editor might freeze
    // for some of them when viewing the Victory Condition.
    std::uint8_t artifact_type {};
    std::uint8_t x {};
    std::uint8_t y {};
    std::uint8_t z {};
  };

  // Specialization for SurviveBeyondATimeLimit.
  template<>
  struct VictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit> : SpecialVictoryConditionBase
  {
    // TODO: check signedness.
    std::uint32_t days {};
  };

  // Victory condition for the map.
  //
  // This is an aggregate type; the default-constructed VictoryCondition represents VictoryConditionType::Normal.
  struct VictoryCondition
  {
    using Details = std::variant<
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
      VictoryConditionDetails<VictoryConditionType::DefeatAllMonsters>,
      VictoryConditionDetails<VictoryConditionType::SurviveBeyondATimeLimit>,
      VictoryConditionDetails<VictoryConditionType::Normal>
    >;

    // \return the type of the victory condition.
    constexpr VictoryConditionType type() const noexcept;

    // Details of the victory condition.
    Details details = VictoryConditionDetails<VictoryConditionType::Normal>{};
  };

  constexpr VictoryConditionType VictoryCondition::type() const noexcept
  {
    constexpr std::size_t kNormalDetailsIndex = 13;
    static_assert(std::is_same_v<std::variant_alternative_t<kNormalDetailsIndex, Details>,
                                 VictoryConditionDetails<VictoryConditionType::Normal>>,
                  "kNormalDetailsIndex must be the index of the alternative for Normal victory condition.");

    const std::size_t index = details.index();
    // Hack to avoid writing a switch statement over all victory condition types.
    if (index == kNormalDetailsIndex)
    {
      return VictoryConditionType::Normal;
    }
    return static_cast<VictoryConditionType>(index);
  }
}
