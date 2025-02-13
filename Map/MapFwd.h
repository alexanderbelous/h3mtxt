#pragma once

#include <cstdint>

// Forward declarations of some types used in h3m::Map.
//
// Note that the underlying types of enums are significant - they should always
// match the actual integer type used in the H3M file format.
namespace h3m
{
  enum class ArtifactType : std::uint16_t;

  enum class CreatureType : std::uint16_t;

  enum class Disposition : std::uint8_t;

  enum class Formation : std::uint8_t;

  enum class Gender : std::uint8_t;

  enum class LossConditionType : std::uint8_t;

  enum class MapDifficulty : std::uint8_t;

  // No explicit underlying type because this enum is not serialized anywhere in H3M.
  enum class MetaObjectType;

  enum class ObjectClass : std::uint32_t;

  enum class ObjectGroup : std::uint8_t;

  enum class PlayerBehavior : std::uint8_t;

  enum class PlayerColor : std::uint8_t;

  enum class QuestType : std::uint8_t;

  enum class RewardType : std::uint8_t;

  enum class RiverType : std::uint8_t;

  enum class RoadType : std::uint8_t;

  enum class ScholarRewardType : std::uint8_t;

  enum class SecondarySkillType : std::uint8_t;

  enum class TerrainType : std::uint8_t;

  enum class VictoryConditionType : std::uint8_t;

  struct CreatureStack;

  struct EventBase;

  struct GlobalEvent;

  struct Guardians;

  struct HeroArtifacts;

  struct HeroSettings;

  struct MainTown;

  struct Map;

  struct MapBasicInfo;

  struct MapAdditionalInfo;

  struct MessageAndTreasure;

  struct ObjectAttributes;

  struct ObjectDetails;

  // "Extension" of ObjectDetails specific to ObjectClass of this object.
  template<MetaObjectType T>
  struct ObjectDetailsData;

  struct PlayerSpecs;

  struct PlayersBitmask;

  struct PrimarySkills;

  struct Quest;

  // "Extension" of Quest specific to QuestType.
  template<QuestType T>
  struct QuestDetails;

  template<class T>
  struct Resources;

  struct ResourcesBitmask;

  struct Rumor;

  struct SecondarySkill;

  struct SecondarySkillsBitmask;

  struct StartingHero;

  struct TeamsInfo;

  struct Tile;

  struct TimedEventBase;

  struct TownBuildings;

  struct TownEvent;
}
