#pragma once

#include <h3mtxt/Map/MapFwd.h>

#include <cstddef>
#include <cstdint>

// Forward declarations of some types used in h3svg::SavedGame.
//
// Note that SavedGame uses a different namespace than Map. This is due to the fact that some
// structures are represented differently in H3SVG than they are in H3M - for example,
// h3svg::Tile is different from h3m::Tile because in H3SVG tiles store much more data than
// in H3M.
namespace h3svg
{
  // Reuse some types from H3M.
  using ::h3m::ArtifactSlot;
  using ::h3m::ArtifactType;
  using ::h3m::BitSet;
  using ::h3m::Bool;
  using ::h3m::Coordinates;
  using ::h3m::CreatureStack;
  using ::h3m::CreatureType;
  using ::h3m::CustomHero;
  using ::h3m::EnumBitmask;
  using ::h3m::EnumIndexedArray;
  using ::h3m::HeroClass;
  using ::h3m::HeroPortrait;
  using ::h3m::HeroType;
  using ::h3m::LossConditionType;
  using ::h3m::MapBasicInfo;
  using ::h3m::MapDifficulty;
  using ::h3m::MapFormat;
  using ::h3m::ObjectClass;
  using ::h3m::PlayerColor;
  using ::h3m::PlayerBehavior;
  using ::h3m::PlayersBitmask;
  using ::h3m::PrimarySkills;
  using ::h3m::PrimarySkillType;
  using ::h3m::QuestType;
  using ::h3m::ReservedData;
  using ::h3m::Resources;
  using ::h3m::ResourceType;
  using ::h3m::RewardType;
  using ::h3m::RiverType;
  using ::h3m::RoadType;
  using ::h3m::SecondarySkill;
  using ::h3m::SecondarySkillType;
  using ::h3m::SpecialVictoryConditionBase;
  using ::h3m::SpellsBitmask;
  using ::h3m::SpellType;
  using ::h3m::SpriteTilesBitmask;
  using ::h3m::StartingHero;
  using ::h3m::TeamsInfo;
  using ::h3m::TerrainType;
  using ::h3m::TownBuildingsBitmask;
  using ::h3m::TownBuildingType;
  using ::h3m::TownType;
  using ::h3m::TownsBitmask;
  using ::h3m::VictoryConditionType;

  enum class ArtifactSlotGroup : std::uint8_t;

  enum class ArtifactType8 : std::uint8_t;

  enum class ArtifactType32 : std::int32_t;

  enum class CreatureType8 : std::uint8_t;

  enum class CreatureType32 : std::int32_t;

  enum class HeroFlag;

  enum class HeroType16 : std::uint16_t;

  enum class KeymastersTentType : std::uint8_t;

  enum class ObjectClass8 : std::uint8_t;

  enum class ObjectClass16 : std::uint16_t;

  // No explicit underlying type because this enum is not serialized anywhere in H3SVG.
  enum class ObjectPropertiesType;

  enum class PlayerControlType : std::int8_t;

  enum class PlayerPersonality : std::uint32_t;

  enum class PlayerStartingBonusType : std::uint8_t;

  enum class PlayerTurnDurationType : std::uint8_t;

  enum class PrimarySkillType32 : std::uint32_t;

  enum class ResourceType32 : std::uint32_t;

  enum class SecondarySkillType32 : std::uint32_t;

  enum class SeerName : std::uint8_t;

  enum class SpellType32 : std::uint32_t;

  enum class TownBuildingTypeH3SVG : std::uint8_t;

  enum class TownType32 : std::int32_t;

  using HeroFlags = EnumBitmask<HeroFlag, 4>;

  struct Artifact;

  struct ArtifactMerchants;

  struct Boat;

  struct Dwelling;

  struct EventBase;

  struct Garrison;

  struct Guardians;

  struct Hero;

  struct HeroArtifact;

  struct HeroArtifacts;

  struct LossCondition;

  template<LossConditionType T>
  struct LossConditionDetails;

  struct Mine;

  struct Monster;

  struct Obelisk;

  struct ObjectPropertiesTables;

  template<ObjectPropertiesType T>
  struct ObjectProperties;

  struct ObjectPropertiesVariant;

  struct Object;

  struct ObjectTemplate;

  struct Player;

  struct PlayerSpecs;

  struct Quest;

  template<QuestType T>
  struct QuestDetails;

  struct QuestGuard;

  struct Reward;

  template<RewardType T>
  struct RewardDetails;

  struct Rumor;

  struct SavedGame;

  struct ScenarioStartingInfo;

  struct SeersHut;

  struct Sign;

  struct Tile;

  struct TileVisibility;

  struct TimedEvent;

  struct Town;

  struct TownEvent;

  struct TownUniqueBuildingsProperties;

  struct Troops;

  struct VictoryCondition;

  template<VictoryConditionType T>
  struct VictoryConditionDetails;
}
