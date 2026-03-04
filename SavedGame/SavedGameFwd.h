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

  struct EventBaseSvg;

  struct GuardiansSvg;

  struct MonsterSvg;

  struct ObjectSvg;

  struct ObjectTemplateSvg;

  struct PlayerSpecsSvg;

  struct QuestSvg;

  template<QuestType T>
  struct QuestDetailsSvg;

  struct QuestGuardSvg;

  struct RewardSvg;

  template<RewardType T>
  struct RewardDetailsSvg;

  struct RumorSvg;

  struct SavedGame;

  struct SeersHutSvg;

  struct TileSvg;

  struct TimedEventSvg;

  struct TroopsSvg;
}