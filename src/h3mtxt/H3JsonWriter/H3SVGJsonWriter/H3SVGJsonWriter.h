#pragma once

#include <h3mtxt/Map/Constants/LossConditionType.h>
#include <h3mtxt/Map/Constants/QuestType.h>
#include <h3mtxt/Map/Constants/RewardType.h>
#include <h3mtxt/Map/Constants/VictoryConditionType.h>
#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Medea/MedeaFwd.h>

// API for JSON serialization of structures used in HoMM3 saved game format.
namespace Medea_NS
{
  // ============================================================
  // Human-readable comments for enum values.
  // ------------------------------------------------------------
  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::ArtifactType8 value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::ArtifactType32 value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::BoatType value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::CampaignId value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::CreatureType8 value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::CreatureType32 value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::HeroType16 value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::ObjectClass8 value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::ObjectClass16 value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::PlayerControlType value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::PlayerPersonality value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::PlayerStartingBonusType value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::TurnDurationType value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::PrimarySkillType32 value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::ResourceType32 value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::SecondarySkillType32 value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::SeerName value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::SpellType32 value) const;

  template<>
  std::string_view EnumCommentGetter::operator()(h3svg::TownType32 value) const;
  // ============================================================

  // Serialize h3svg::FixedLengthString as JsonDataType::String.
  //
  // TODO: this is "lossy": the junk bytes after the first null terminator are ignored, so deserializing
  // FxiedWidthString from the generated JSON String will produce an unequal object.
  // Possible alternatives:
  // * Serialize as an array of bytes instead. Cons: poor readability.
  // * Serialize as a String only if all bytes after the first null terminator are also null terminators.
  // * Escape the null terminator and the bytes after it.
  template<std::size_t N>
  inline constexpr JsonDataType kJsonDataTypeFor<h3svg::FixedLengthString<N>> = JsonDataType::String;

  template<std::size_t N>
  struct JsonScalarGetter<h3svg::FixedLengthString<N>>
  {
    // Defined in Utils.h
    std::string_view operator()(const h3svg::FixedLengthString<N>& str) const;
  };

  template<>
  void JsonObjectWriter<h3svg::Artifact>::operator()(FieldsWriter& out, const h3svg::Artifact& artifact) const;

  // Serialize h3svg::ArtifactMerchants as a JSON array.
  template<>
  void JsonArrayWriter<h3svg::ArtifactMerchants>::operator()(const ArrayElementsWriter& out,
                                                             const h3svg::ArtifactMerchants& artifact_merchants) const;

  template<>
  void JsonObjectWriter<h3svg::Boat>::operator()(FieldsWriter& out, const h3svg::Boat& boat) const;

  template<>
  void JsonObjectWriter<h3svg::CampaignInfo>::operator()(FieldsWriter& out, const h3svg::CampaignInfo& info) const;

  template<>
  void JsonObjectWriter<h3svg::CoordinatesPacked>::operator()(FieldsWriter& out,
                                                              const h3svg::CoordinatesPacked& coordinates) const;

  template<>
  inline constexpr bool kIsSingleLineByDefault<h3svg::CoordinatesPacked> = true;

  template<>
  void JsonObjectWriter<h3svg::CrossoverInfo>::operator()(FieldsWriter& out, const h3svg::CrossoverInfo& info) const;

  template<>
  void JsonObjectWriter<h3svg::Date>::operator()(FieldsWriter& out, const h3svg::Date& date) const;

  template<>
  void JsonObjectWriter<h3svg::Dwelling>::operator()(FieldsWriter& out, const h3svg::Dwelling& dwelling) const;

  template<>
  void JsonObjectWriter<h3svg::EventBase>::operator()(FieldsWriter& out, const h3svg::EventBase& event) const;

  template<>
  void JsonObjectWriter<h3svg::Garrison>::operator()(FieldsWriter& out, const h3svg::Garrison& garrison) const;

  template<>
  void JsonObjectWriter<h3svg::Guardians>::operator()(FieldsWriter& out, const h3svg::Guardians& guardians) const;

  template<>
  void JsonObjectWriter<h3svg::Hero>::operator()(FieldsWriter& out, const h3svg::Hero& hero) const;

  template<>
  void JsonObjectWriter<h3svg::HeroArtifact>::operator()(FieldsWriter& out, const h3svg::HeroArtifact& artifact) const;

  template<>
  void JsonObjectWriter<h3svg::HeroArtifacts>::operator()(FieldsWriter& out,
                                                          const h3svg::HeroArtifacts& artifacts) const;

  template<>
  void JsonObjectWriter<h3svg::LossCondition>::operator()(FieldsWriter& out,
                                                          const h3svg::LossCondition& loss_condition) const;

  // Partial specialization for h3svg::LossConditionDetails.
  template<h3svg::LossConditionType T>
  struct JsonObjectWriter<h3svg::LossConditionDetails<T>>
  {
    // Defined in writeLossCondition.cpp.
    // Explicit instantiations are provided for LossConditionTypes that use the default template implementation.
    // A specialization for LossConditionType::LoseHero is declared below.
    void operator()(FieldsWriter& out, const h3svg::LossConditionDetails<T>& details) const;
  };

  template<>
  void JsonObjectWriter<h3svg::LossConditionDetails<h3svg::LossConditionType::LoseHero>>::operator()(
    FieldsWriter& out,
    const h3svg::LossConditionDetails<h3svg::LossConditionType::LoseHero>& details) const;

  template<>
  void JsonObjectWriter<h3svg::Mine>::operator()(FieldsWriter& out, const h3svg::Mine& mine) const;

  template<>
  void JsonObjectWriter<h3svg::Monster>::operator()(FieldsWriter& out, const h3svg::Monster& monster) const;

  template<>
  void JsonObjectWriter<h3svg::Obelisk>::operator()(FieldsWriter& out, const h3svg::Obelisk& obelisk) const;

  template<>
  void JsonObjectWriter<h3svg::ObjectPropertiesTables>::operator()(FieldsWriter& out,
                                                                   const h3svg::ObjectPropertiesTables& tables) const;

  template<>
  void JsonObjectWriter<h3svg::Object>::operator()(FieldsWriter& out, const h3svg::Object& object) const;

  template<>
  void JsonObjectWriter<h3svg::ObjectTemplate>::operator()(FieldsWriter& out,
                                                           const h3svg::ObjectTemplate& object_template) const;

  template<>
  void JsonObjectWriter<h3svg::Player>::operator()(FieldsWriter& out,
                                                   const h3svg::Player& player) const;

  template<>
  void JsonObjectWriter<h3svg::PlayerSpecs>::operator()(FieldsWriter& out,
                                                        const h3svg::PlayerSpecs& player_specs) const;

  template<>
  void JsonObjectWriter<h3svg::Quest>::operator()(FieldsWriter& out, const h3svg::Quest& quest) const;

  template<>
  void JsonObjectWriter<h3svg::QuestDetails<h3svg::QuestType::None>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetails<h3svg::QuestType::None>& details) const;

  template<>
  void JsonObjectWriter<h3svg::QuestDetails<h3svg::QuestType::Level>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetails<h3svg::QuestType::Level>& details) const;

  template<>
  void JsonObjectWriter<h3svg::QuestDetails<h3svg::QuestType::PrimarySkills>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetails<h3svg::QuestType::PrimarySkills>& details) const;

  template<>
  void JsonObjectWriter<h3svg::QuestDetails<h3svg::QuestType::DefeatHero>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetails<h3svg::QuestType::DefeatHero>& details) const;

  template<>
  void JsonObjectWriter<h3svg::QuestDetails<h3svg::QuestType::DefeatMonster>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetails<h3svg::QuestType::DefeatMonster>& details) const;

  template<>
  void JsonObjectWriter<h3svg::QuestDetails<h3svg::QuestType::Artifacts>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetails<h3svg::QuestType::Artifacts>& details) const;

  template<>
  void JsonObjectWriter<h3svg::QuestDetails<h3svg::QuestType::Creatures>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetails<h3svg::QuestType::Creatures>& details) const;

  template<>
  void JsonObjectWriter<h3svg::QuestDetails<h3svg::QuestType::Resources>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetails<h3svg::QuestType::Resources>& details) const;

  template<>
  void JsonObjectWriter<h3svg::QuestDetails<h3svg::QuestType::BeHero>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetails<h3svg::QuestType::BeHero>& details) const;

  template<>
  void JsonObjectWriter<h3svg::QuestDetails<h3svg::QuestType::BePlayer>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetails<h3svg::QuestType::BePlayer>& details) const;

  template<>
  void JsonObjectWriter<h3svg::QuestGuard>::operator()(FieldsWriter& out,
                                                       const h3svg::QuestGuard& quest_guard) const;

  template<>
  void JsonObjectWriter<h3svg::RegionInfo>::operator()(FieldsWriter& out,
                                                       const h3svg::RegionInfo& info) const;

  template<>
  void JsonObjectWriter<h3svg::Reward>::operator()(FieldsWriter& out, const h3svg::Reward& reward) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::None>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::None>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::Experience>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::Experience>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::SpellPoints>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::SpellPoints>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::Morale>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::Morale>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::Luck>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::Luck>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::Resource>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::Resource>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::PrimarySkill>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::PrimarySkill>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::SecondarySkill>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::SecondarySkill>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::Artifact>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::Artifact>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::Spell>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::Spell>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::Creatures>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::Creatures>& details) const;

  template<>
  void JsonObjectWriter<h3svg::Rumor>::operator()(FieldsWriter& out, const h3svg::Rumor& rumor) const;

  template<>
  void JsonObjectWriter<h3svg::SavedGame>::operator()(FieldsWriter& out, const h3svg::SavedGame& saved_game) const;

  template<>
  void JsonObjectWriter<h3svg::ScenarioStartingInfo>::operator()(FieldsWriter& out,
                                                                 const h3svg::ScenarioStartingInfo& starting_info) const;

  template<>
  void JsonObjectWriter<h3svg::SeersHut>::operator()(FieldsWriter& out, const h3svg::SeersHut& seers_hut) const;

  template<>
  void JsonObjectWriter<h3svg::Sign>::operator()(FieldsWriter& out, const h3svg::Sign& sign) const;

  template<>
  void JsonObjectWriter<h3svg::Tile>::operator()(FieldsWriter& out, const h3svg::Tile& tile) const;

  template<>
  void JsonObjectWriter<h3svg::TileVisibility>::operator()(FieldsWriter& out,
                                                           const h3svg::TileVisibility& tile_visibility) const;

  template<>
  void JsonObjectWriter<h3svg::TimedEvent>::operator()(FieldsWriter& out, const h3svg::TimedEvent& event) const;

  template<>
  void JsonObjectWriter<h3svg::TownEvent>::operator()(FieldsWriter& out, const h3svg::TownEvent& event) const;

  template<>
  void JsonObjectWriter<h3svg::Town>::operator()(FieldsWriter& out, const h3svg::Town& town) const;

  template<>
  void JsonObjectWriter<h3svg::TownUniqueBuildingsProperties>::operator()(
    FieldsWriter& out, const h3svg::TownUniqueBuildingsProperties& unique_buildings_properties) const;

  template<>
  void JsonObjectWriter<h3svg::Troops>::operator()(FieldsWriter& out, const h3svg::Troops& troops) const;

  template<>
  void JsonObjectWriter<h3svg::VictoryCondition>::operator()(FieldsWriter& out,
                                                             const h3svg::VictoryCondition& victory_condition) const;

  // Partial specialization for h3svg::VictoryConditionDetails.
  template<h3svg::VictoryConditionType T>
  struct JsonObjectWriter<h3svg::VictoryConditionDetails<T>>
  {
    // Defined in writeVictoryCondition.cpp.
    // Explicit instantiations are provided for VictoryConditionTypes that use the default template implementation.
    // A few specializations are declared below.
    void operator()(FieldsWriter& out, const h3svg::VictoryConditionDetails<T>& details) const;
  };

  template<>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::AcquireArtifact>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::AcquireArtifact>& details) const;

  template<>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::AccumulateCreatures>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::AccumulateCreatures>& details) const;

  template<>
  void JsonObjectWriter<h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::DefeatHero>>::operator()(
    FieldsWriter& out,
    const h3svg::VictoryConditionDetails<h3svg::VictoryConditionType::DefeatHero>& details) const;
}
