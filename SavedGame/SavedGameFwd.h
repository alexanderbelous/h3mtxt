#pragma once

#include <h3mtxt/Map/MapFwd.h>

#include <cstddef>
#include <cstdint>

// Forward declarations of some types used in h3m::SavedGame.
namespace h3m
{
  enum class ArtifactType8 : std::uint8_t;

  enum class ArtifactType32 : std::int32_t;

  enum class CreatureType32 : std::int32_t;

  enum class ObjectClass16 : std::uint16_t;

  // No explicit underlying type because this enum is not serialized anywhere in H3SVG.
  enum class ObjectPropertiesSvgType;

  enum class PlayerControlType : std::int8_t;

  enum class PlayerStartingBonusType : std::uint8_t;

  enum class PlayerTurnDurationType : std::uint8_t;

  enum class PrimarySkillType32 : std::uint32_t;

  enum class ResourceType32 : std::uint32_t;

  enum class SecondarySkillType32 : std::uint32_t;

  enum class SpellType32 : std::uint32_t;

  enum class TownType32 : std::int32_t;

  template<class Enum, class T, std::size_t NumElements>
  struct EnumIndexedArray;

  struct ArtifactSvg;

  struct BlackMarket;

  struct BoatSvg;

  struct DwellingSvg;

  struct EventBaseSvg;

  struct GarrisonSvg;

  struct GuardiansSvg;

  struct HeroSvg;

  struct MineSvg;

  struct MonsterSvg;

  struct ObeliskSvg;

  struct ObjectPropertiesTables;

  template<ObjectPropertiesSvgType T>
  struct ObjectPropertiesSvg;

  struct ObjectPropertiesSvgVariant;

  struct ObjectSvg;

  struct ObjectTemplateSvg;

  struct PlayerSpecsSvg;

  struct PlayerSvg;

  struct QuestSvg;

  template<QuestType T>
  struct QuestDetailsSvg;

  struct QuestGuardSvg;

  struct RewardSvg;

  template<RewardType T>
  struct RewardDetailsSvg;

  struct RumorSvg;

  struct SavedGame;

  struct ScenarioStartingInfo;

  struct SeersHutSvg;

  struct SignSvg;

  struct TileSvg;

  struct TimedEventSvg;

  struct TownEventSvg;

  struct TownSvg;

  struct TroopsSvg;
}