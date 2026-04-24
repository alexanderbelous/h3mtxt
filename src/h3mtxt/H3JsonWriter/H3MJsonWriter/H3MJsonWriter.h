#pragma once

#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/ObjectPropertiesType.h>
#include <h3mtxt/Map/Constants/QuestType.h>
#include <h3mtxt/Map/Constants/RewardType.h>
#include <h3mtxt/Map/Constants/VictoryConditionType.h>
#include <h3mtxt/Medea/MedeaFwd.h>

#include <cstddef>

// API for JSON serialization of structures from Map library.
namespace Medea_NS
{
  // Default implementation for h3m::EnumBitmask: serializes the bitmask as a JSON object.
  template<class Enum, std::size_t NumBytes>
  struct JsonObjectWriter<h3m::EnumBitmask<Enum, NumBytes>>
  {
    // Defined in Utils.h.
    void operator()(FieldsWriter& out, const h3m::EnumBitmask<Enum, NumBytes>& bitmask) const;
  };

  // Default implementation for h3m::EnumIndexedArray: serializes the value as a JSON object.
  template<class Enum, class T, std::size_t NumElements>
  struct JsonObjectWriter<h3m::EnumIndexedArray<Enum, T, NumElements>>
  {
    // Defined in Utils.h.
    void operator()(FieldsWriter& out, const h3m::EnumIndexedArray<Enum, T, NumElements>& enum_indexed_array) const;
  };

  // Serializes h3m::BitSet as a JSON array.
  template<std::size_t NumBytes>
  struct JsonArrayWriter<h3m::BitSet<NumBytes>>
  {
    // Defined in Utils.h
    void operator()(const ArrayElementsWriter& elements_writer, const h3m::BitSet<NumBytes>& bitset) const;
  };

  // Serialize h3m::BitSet on a single line by default.
  template<std::size_t NumBytes>
  inline constexpr bool kIsSingleLineByDefault<h3m::BitSet<NumBytes>> = true;

  // Serializes h3m::ReservedData as a JSON array.
  template<std::size_t NumBytes>
  struct JsonArrayWriter<h3m::ReservedData<NumBytes>>
  {
    // Defined in Utils.h
    void operator()(const ArrayElementsWriter& elements_writer,
                    const h3m::ReservedData<NumBytes>& reserved_data) const;
  };

  // Serialize h3m::ReservedData on a single line by default.
  template<std::size_t NumBytes>
  inline constexpr bool kIsSingleLineByDefault<h3m::ReservedData<NumBytes>> = true;

  template<>
  void JsonObjectWriter<h3m::Coordinates>::operator()(FieldsWriter& out, const h3m::Coordinates& coordinates) const;

  // Serialize h3m::Coordinates on a single line by default.
  template<>
  inline constexpr bool kIsSingleLineByDefault<h3m::Coordinates> = true;

  template<>
  void JsonObjectWriter<h3m::CreatureStack>::operator()(FieldsWriter& out, const h3m::CreatureStack& creature_stack) const;

  template<>
  void JsonObjectWriter<h3m::CustomHero>::operator()(FieldsWriter& out, const h3m::CustomHero& value) const;

  template<>
  void JsonObjectWriter<h3m::EventBase>::operator()(FieldsWriter& out, const h3m::EventBase& event) const;

  template<>
  void JsonObjectWriter<h3m::Guardians>::operator()(FieldsWriter& out, const h3m::Guardians& guardians) const;

  template<>
  void JsonObjectWriter<h3m::HeroArtifacts>::operator()(FieldsWriter& out, const h3m::HeroArtifacts& value) const;

  template<>
  void JsonObjectWriter<h3m::HeroSettings>::operator()(FieldsWriter& out, const h3m::HeroSettings& value) const;

  template<>
  void JsonObjectWriter<h3m::HeroesSettings>::operator()(FieldsWriter& out, const h3m::HeroesSettings& value) const;

  template<>
  void JsonObjectWriter<h3m::LossCondition>::operator()(FieldsWriter& out,
                                                        const h3m::LossCondition& loss_condition) const;

  template<>
  void JsonObjectWriter<h3m::MainTown>::operator()(FieldsWriter& out, const h3m::MainTown& value) const;

  template<>
  void JsonObjectWriter<h3m::Map>::operator()(FieldsWriter& out, const h3m::Map& value) const;

  template<>
  void JsonObjectWriter<h3m::MapAdditionalInfo>::operator()(FieldsWriter& out, const h3m::MapAdditionalInfo& value) const;

  template<>
  void JsonObjectWriter<h3m::MapBasicInfo>::operator()(FieldsWriter& out, const h3m::MapBasicInfo& value) const;

  template<>
  void JsonObjectWriter<h3m::MessageAndTreasure>::operator()(FieldsWriter& out,
                                                             const h3m::MessageAndTreasure& data) const;

  template<>
  struct JsonObjectWriter<h3m::Object>
  {
    // Constructs a writer that won't print any comments about the object's template.
    constexpr JsonObjectWriter() noexcept = default;

    // Constructs a writer that will print comments about the object's template.
    constexpr JsonObjectWriter(const h3m::ObjectTemplate* objects_templates,
                               std::size_t num_objects_templates) noexcept:
      objects_templates_(objects_templates),
      num_objects_templates_(num_objects_templates)
    {}

    void operator()(FieldsWriter& out, const h3m::Object& object) const;

  private:
    const h3m::ObjectTemplate* objects_templates_ = nullptr;
    std::size_t num_objects_templates_ = 0;
  };

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::ABANDONED_MINE>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::ABANDONED_MINE>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::ARTIFACT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::ARTIFACT>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::EVENT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::EVENT>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::GARRISON>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::GARRISON>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::NONE>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::NONE>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::GRAIL>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::GRAIL>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::HERO>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::HERO>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::MONSTER>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::MONSTER>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::PANDORAS_BOX>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::PANDORAS_BOX>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::PLACEHOLDER_HERO>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::PLACEHOLDER_HERO>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::QUEST_GUARD>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::QUEST_GUARD>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING_PRESET_ALIGNMENT>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::RANDOM_DWELLING_PRESET_LEVEL>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::RESOURCE>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::RESOURCE>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::SCHOLAR>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::SCHOLAR>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::SEERS_HUT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::SEERS_HUT>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::SHRINE>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::SHRINE>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::SIGN>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::SIGN>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::SPELL_SCROLL>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::SPELL_SCROLL>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::TOWN>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::TOWN>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::TRIVIAL_OWNED_OBJECT>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::WITCH_HUT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::WITCH_HUT>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectTemplate>::operator()(FieldsWriter& out, const h3m::ObjectTemplate& value) const;

  template<>
  void JsonObjectWriter<h3m::PlayerSpecs>::operator()(FieldsWriter& out, const h3m::PlayerSpecs& value) const;

  template<>
  void JsonObjectWriter<h3m::PrimarySkills>::operator()(FieldsWriter& out, const h3m::PrimarySkills& value) const;

  template<>
  void JsonObjectWriter<h3m::Quest>::operator()(FieldsWriter& out, const h3m::Quest& quest) const;

  template<>
  void JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::None>>::operator()(
    FieldsWriter&, const h3m::QuestDetails<h3m::QuestType::None>&) const;

  template<>
  void JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::Level>>::operator()(
    FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::Level>& details) const;

  template<>
  void JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::PrimarySkills>>::operator()(
    FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::PrimarySkills>& details) const;

  template<>
  void JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::DefeatHero>>::operator()(
    FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::DefeatHero>& details) const;

  template<>
  void JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::DefeatMonster>>::operator()(
    FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::DefeatMonster>& details) const;

  template<>
  void JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::Artifacts>>::operator()(
    FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::Artifacts>& details) const;

  template<>
  void JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::Creatures>>::operator()(
    FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::Creatures>& details) const;

  template<>
  void JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::Resources>>::operator()(
    FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::Resources>& details) const;

  template<>
  void JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::BeHero>>::operator()(
    FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::BeHero>& details) const;

  template<>
  void JsonObjectWriter<h3m::QuestDetails<h3m::QuestType::BePlayer>>::operator()(
    FieldsWriter& out, const h3m::QuestDetails<h3m::QuestType::BePlayer>& details) const;

  template<>
  void JsonObjectWriter<h3m::Reward>::operator()(FieldsWriter& out, const h3m::Reward& reward) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::None>>::operator()(
    FieldsWriter&, const h3m::RewardDetails<h3m::RewardType::None>&) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Experience>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Experience>& details) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::SpellPoints>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::SpellPoints>& details) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Morale>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Morale>& details) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Luck>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Luck>& details) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Resource>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Resource>& details) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::PrimarySkill>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::PrimarySkill>& details) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::SecondarySkill>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::SecondarySkill>& details) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Artifact>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Artifact>& details) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Spell>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Spell>& details) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetails<h3m::RewardType::Creature>>::operator()(
    FieldsWriter& out, const h3m::RewardDetails<h3m::RewardType::Creature>& details) const;

  template<>
  void JsonObjectWriter<h3m::Rumor>::operator()(FieldsWriter& out, const h3m::Rumor& value) const;

  // Serialize h3m::SpriteTilesBitmask as a JSON array.
  // Ideally, it should be serialized as a 2D array of boolean values; however, that would significantly
  // increase the size of the output JSON.
  template<>
  void JsonArrayWriter<h3m::SpriteTilesBitmask>::operator()(const ArrayElementsWriter& elements_writer,
                                                            const h3m::SpriteTilesBitmask& sprite_tiles_bitmask) const;

  // Serialize h3m::SpriteTilesBitmask on a single line by default.
  template<>
  inline constexpr bool kIsSingleLineByDefault<h3m::SpriteTilesBitmask> = true;

  template<>
  void JsonObjectWriter<h3m::SecondarySkill>::operator()(FieldsWriter& out, const h3m::SecondarySkill& skill) const;

  template<>
  void JsonObjectWriter<h3m::SpecialVictoryConditionBase>::operator()(
    FieldsWriter& out, const h3m::SpecialVictoryConditionBase& value) const;

  template<>
  void JsonObjectWriter<h3m::StartingHero>::operator()(FieldsWriter& out, const h3m::StartingHero& value) const;

  template<>
  void JsonObjectWriter<h3m::TeamsInfo>::operator()(FieldsWriter& out, const h3m::TeamsInfo& value) const;

  // Serialize h3m::TerrainsBitmask as a JSON array.
  template<>
  void JsonArrayWriter<h3m::TerrainsBitmask>::operator()(const ArrayElementsWriter& elements_writer,
                                                         const h3m::TerrainsBitmask& bitmask) const;

  // Serialize h3m::TerrainsBitmask on a single line by default.
  template<>
  inline constexpr bool kIsSingleLineByDefault<h3m::TerrainsBitmask> = true;

  template<>
  void JsonObjectWriter<h3m::Tile>::operator()(FieldsWriter& out, const h3m::Tile& value) const;

  // Serialize h3m::TileFlags on a single line by default.
  // This is done to reduce the number of lines in the output JSON.
  template<>
  inline constexpr bool kIsSingleLineByDefault<h3m::TileFlags> = true;

  template<>
  void JsonObjectWriter<h3m::TimedEvent>::operator()(FieldsWriter& out, const h3m::TimedEvent& event) const;

  template<>
  void JsonObjectWriter<h3m::TownBuildings>::operator()(FieldsWriter& out,
                                                        const h3m::TownBuildings& town_buildings) const;

  template<>
  void JsonObjectWriter<h3m::TownEvent>::operator()(FieldsWriter& out, const h3m::TownEvent& town_event) const;

  template<>
  void JsonObjectWriter<h3m::VictoryCondition>::operator()(FieldsWriter& out,
                                                           const h3m::VictoryCondition& value) const;

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::AcquireArtifact>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::AcquireArtifact>& value) const;

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::AccumulateCreatures>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::AccumulateCreatures>& value) const;

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::AccumulateResources>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::AccumulateResources>& value) const;

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::UpgradeTown>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::UpgradeTown>& value) const;

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::BuildGrail>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::BuildGrail>& value) const;

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::DefeatHero>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::DefeatHero>& value) const;

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::CaptureTown>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::CaptureTown>& value) const;

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::DefeatMonster>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::DefeatMonster>& value) const;

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::FlagDwellings>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::FlagDwellings>& value) const;

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::FlagMines>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::FlagMines>& value) const;

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::TransportArtifact>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::TransportArtifact>& value) const;

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::DefeatAllMonsters>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::DefeatAllMonsters>& value) const;

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::SurviveBeyondATimeLimit>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::SurviveBeyondATimeLimit>& value) const;

  template<>
  void JsonObjectWriter<h3m::VictoryConditionDetails<h3m::VictoryConditionType::Normal>>::operator()(
    FieldsWriter& out, const h3m::VictoryConditionDetails<h3m::VictoryConditionType::Normal>& value) const;
}
