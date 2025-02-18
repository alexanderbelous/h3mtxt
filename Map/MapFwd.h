#pragma once

#include <cstddef>
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

  enum class HeroPortrait : std::uint8_t;

  enum class HeroType : std::uint8_t;

  enum class LossConditionType : std::uint8_t;

  enum class MapDifficulty : std::uint8_t;

  // No explicit underlying type because this enum is not serialized anywhere in H3M.
  enum class MetaObjectType;

  enum class ObjectClass : std::uint32_t;

  enum class ObjectGroup : std::uint8_t;

  enum class PlayerBehavior : std::uint8_t;

  enum class PlayerColor : std::uint8_t;

  enum class QuestType : std::uint8_t;

  enum class ResourceType : std::uint8_t;

  enum class RewardType : std::uint8_t;

  enum class RiverType : std::uint8_t;

  enum class RoadType : std::uint8_t;

  enum class ScholarRewardType : std::uint8_t;

  enum class SecondarySkillType : std::uint8_t;

  enum class SpellType : std::uint8_t;

  enum class TerrainType : std::uint8_t;

  enum class TownBuildingType : std::uint8_t;

  enum class TownType : std::uint8_t;

  enum class VictoryConditionType : std::uint8_t;

  struct CreatureStack;

  // Wrapper around BitSet<NumBytes>.
  // * More convenient access to the stored bits - no need to explicitly cast enum values to integers.
  // * It improves type safety: EnumBitmask<PlayerColor, 1> cannot be used where EnumBitmask<ResourceType, 1>
  //   is expected, even though they are both simply wrappers around BitSet<1>.
  template<class Enum, std::size_t NumBytes>
  struct EnumBitmask;

  // Bitmask storing a bit for each artifact.
  //
  // There are 144 artifacts in Shadow of Death (the last 3 of them are unused content);
  // this bitmask stores exactly 144 bits.
  using ArtifactsBitmask = EnumBitmask<ArtifactType, 18>;

  // Bitmask storing a bit for each creature type.
  //
  // There are 150 creature types in Shadow of Death (the last 5 of them are war machines and arrow towers),
  // but this bitmask stores 152 bits.
  //
  // This is only used in CrossoverOptions.
  using CreaturesBitmask = EnumBitmask<CreatureType, 19>;

  // Bitmask storing a bit for each valid hero.
  //
  // Note that there are 156 heroes in Shadow of Death, but this bitmask stores 160 bits.
  using HeroesBitmask = EnumBitmask<HeroType, 20>;

  // Bitmask storing a bit for each player.
  //
  // .h3m file format uses such bitmasks in multiple places, e.g. which players can hire
  // a specific hero, Global Event, Event object on the adventure map, or a Event in a town).
  using PlayersBitmask = EnumBitmask<PlayerColor, 1>;

  // Bitmask storing a bit for each resource type.
  //
  // This is only used in ObjectDetailsData<MetaObjectType::ABANDONED_MINE>.
  using ResourcesBitmask = EnumBitmask<ResourceType, 1>;

  // Note that there are only 28 secondary skills in Shadow of Death, but this bitmask stores 32 bits.
  // The last 4 bits are normally set to 0 in .h3m regardless of the meaning of the bitmask.
  using SecondarySkillsBitmask = EnumBitmask<SecondarySkillType, 4>;

  // Note that there are only 70 spells in Shadow of Death, but this bitmask stores 72 bits.
  using SpellsBitmask = EnumBitmask<SpellType, 9>;

  // Note that there are only 9 towns in Shadow of Death, but this bitmask stores 16 bits.
  // The last 7 bits are normally set to 0 in .h3m regardless of the meaning of the bitmask.
  using TownsBitmask = EnumBitmask<TownType, 2>;

  // Note that there are only 41 town building types in Shadow of Death, but this bitmask stores 48 bits.
  using TownsBuildingsBitmask = EnumBitmask<TownBuildingType, 6>;

  struct EventBase;

  struct GlobalEvent;

  struct Guardians;

  struct HeroArtifacts;

  struct HeroSettings;

  class LossCondition;

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

  struct PrimarySkills;

  struct Quest;

  // "Extension" of Quest specific to QuestType.
  template<QuestType T>
  struct QuestDetails;

  template<class T>
  struct Resources;

  struct Reward;

  struct Rumor;

  struct SecondarySkill;

  struct StartingHero;

  struct TeamsInfo;

  struct Tile;

  struct TimedEventBase;

  struct TownBuildings;

  struct TownEvent;
}
