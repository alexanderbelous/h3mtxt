#pragma once

#include <h3mtxt/Map/Constants/QuestType.h>
#include <h3mtxt/Map/Constants/RewardType.h>
#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Medea/MedeaFwd.h>

// API for JSON serialization of structures used in HoMM3 saved game format.
namespace Medea_NS
{
  template<>
  void JsonObjectWriter<h3svg::Artifact>::operator()(FieldsWriter& out, const h3svg::Artifact& artifact) const;

  // Serialize h3svg::BlackMarket as a JSON array.
  template<>
  void JsonArrayWriter<h3svg::BlackMarket>::operator()(const ArrayElementsWriter& out,
                                                       const h3svg::BlackMarket& black_market) const;

  template<>
  void JsonObjectWriter<h3svg::Boat>::operator()(FieldsWriter& out, const h3svg::Boat& boat) const;

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
  void JsonObjectWriter<h3svg::RewardDetails<h3svg::RewardType::Creature>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetails<h3svg::RewardType::Creature>& details) const;

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
  void JsonObjectWriter<h3svg::TimedEvent>::operator()(FieldsWriter& out, const h3svg::TimedEvent& event) const;

  template<>
  void JsonObjectWriter<h3svg::TownEvent>::operator()(FieldsWriter& out, const h3svg::TownEvent& event) const;

  template<>
  void JsonObjectWriter<h3svg::Town>::operator()(FieldsWriter& out, const h3svg::Town& town) const;

  template<>
  void JsonObjectWriter<h3svg::Troops>::operator()(FieldsWriter& out, const h3svg::Troops& troops) const;
}
