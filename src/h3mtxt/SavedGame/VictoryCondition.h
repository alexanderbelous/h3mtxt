#pragma once

#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <h3mtxt/Map/Constants/HeroType.h>
#include <h3mtxt/Map/Constants/VictoryConditionType.h>
#include <h3mtxt/Map/VictoryCondition.h>

#include <cstdint>
#include <type_traits>
#include <variant>

namespace h3svg
{
  // Reuse a few things from H3M.
  using ::h3m::kNumSpecialVictoryConditions;

  // The default implementation reuses h3m::VictoryConditionDetails
  template<VictoryConditionType T>
  struct VictoryConditionDetails : h3m::VictoryConditionDetails<T>
  {};

  // Specialization for AcquireArtifact.
  // In H3SVG the artifact type is encoded as an 8-bit integer,
  // unlike H3M, where it's encoded as a 16-bit integer.
  template<>
  struct VictoryConditionDetails<VictoryConditionType::AcquireArtifact> : SpecialVictoryConditionBase
  {
    ArtifactType8 artifact_type {};
  };

  // Specialization for AccumulateCreatures.
  // In H3SVG the creature type is encoded as an 8-bit integer,
  // unlike H3M, where it's encoded as a 16-bit integer.
  template<>
  struct VictoryConditionDetails<VictoryConditionType::AccumulateCreatures> : SpecialVictoryConditionBase
  {
    CreatureType8 creature_type {};
    std::int32_t count {};
  };

  // Specialization for DefeatHero.
  // In H3SVG this victory condition stores the hero's type rather than their coordinates.
  template<>
  struct VictoryConditionDetails<VictoryConditionType::DefeatHero> : SpecialVictoryConditionBase
  {
    HeroType hero {};
  };

  // The equivalent of h3m::VictoryCondition stored in saved games.
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

    Details details = VictoryConditionDetails<VictoryConditionType::Normal>{};
  };

  constexpr VictoryConditionType VictoryCondition::type() const noexcept
  {
    static_assert(std::is_same_v<std::variant_alternative_t<kNumSpecialVictoryConditions, Details>,
                                 VictoryConditionDetails<VictoryConditionType::Normal>>,
                  "kNumSpecialVictoryConditions must be the index of the alternative for Normal victory condition.");

    const std::size_t index = details.index();
    if (index == kNumSpecialVictoryConditions)
    {
      return VictoryConditionType::Normal;
    }
    return static_cast<VictoryConditionType>(index);
  }
}
