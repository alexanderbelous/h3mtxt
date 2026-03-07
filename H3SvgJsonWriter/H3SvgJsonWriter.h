#pragma once

#include <h3mtxt/Map/Constants/QuestType.h>
#include <h3mtxt/Map/Constants/RewardType.h>
#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Medea/MedeaFwd.h>

// API for JSON serialization of structures used in HoMM3 saved game format.
namespace Medea_NS
{
  template<>
  void JsonObjectWriter<h3svg::ArtifactSvg>::operator()(FieldsWriter& out, const h3svg::ArtifactSvg& artifact) const;

  // Serialize h3svg::BlackMarket as a JSON array.
  template<>
  void JsonArrayWriter<h3svg::BlackMarket>::operator()(const ArrayElementsWriter& out,
                                                       const h3svg::BlackMarket& black_market) const;

  template<>
  void JsonObjectWriter<h3svg::BoatSvg>::operator()(FieldsWriter& out, const h3svg::BoatSvg& boat) const;

  template<>
  void JsonObjectWriter<h3svg::DwellingSvg>::operator()(FieldsWriter& out, const h3svg::DwellingSvg& dwelling) const;

  template<>
  void JsonObjectWriter<h3svg::EventBaseSvg>::operator()(FieldsWriter& out, const h3svg::EventBaseSvg& event) const;

  template<>
  void JsonObjectWriter<h3svg::GarrisonSvg>::operator()(FieldsWriter& out, const h3svg::GarrisonSvg& garrison) const;

  template<>
  void JsonObjectWriter<h3svg::GuardiansSvg>::operator()(FieldsWriter& out, const h3svg::GuardiansSvg& guardians) const;

  template<>
  void JsonObjectWriter<h3svg::HeroSvg>::operator()(FieldsWriter& out, const h3svg::HeroSvg& hero) const;

  template<>
  void JsonObjectWriter<h3svg::MineSvg>::operator()(FieldsWriter& out, const h3svg::MineSvg& mine) const;

  template<>
  void JsonObjectWriter<h3svg::MonsterSvg>::operator()(FieldsWriter& out, const h3svg::MonsterSvg& monster) const;

  template<>
  void JsonObjectWriter<h3svg::ObeliskSvg>::operator()(FieldsWriter& out, const h3svg::ObeliskSvg& obelisk) const;

  template<>
  void JsonObjectWriter<h3svg::ObjectPropertiesTables>::operator()(FieldsWriter& out,
                                                                   const h3svg::ObjectPropertiesTables& tables) const;

  template<>
  void JsonObjectWriter<h3svg::ObjectSvg>::operator()(FieldsWriter& out, const h3svg::ObjectSvg& object) const;

  template<>
  void JsonObjectWriter<h3svg::ObjectTemplateSvg>::operator()(FieldsWriter& out,
                                                              const h3svg::ObjectTemplateSvg& object_template) const;

  template<>
  void JsonObjectWriter<h3svg::PlayerSvg>::operator()(FieldsWriter& out,
                                                      const h3svg::PlayerSvg& player) const;

  template<>
  void JsonObjectWriter<h3svg::PlayerSpecsSvg>::operator()(FieldsWriter& out,
                                                           const h3svg::PlayerSpecsSvg& player_specs) const;

  template<>
  void JsonObjectWriter<h3svg::QuestSvg>::operator()(FieldsWriter& out, const h3svg::QuestSvg& quest) const;

  template<>
  void JsonObjectWriter<h3svg::QuestDetailsSvg<h3svg::QuestType::None>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetailsSvg<h3svg::QuestType::None>& details) const;

  template<>
  void JsonObjectWriter<h3svg::QuestDetailsSvg<h3svg::QuestType::Level>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetailsSvg<h3svg::QuestType::Level>& details) const;

  template<>
  void JsonObjectWriter<h3svg::QuestDetailsSvg<h3svg::QuestType::PrimarySkills>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetailsSvg<h3svg::QuestType::PrimarySkills>& details) const;

  template<>
  void JsonObjectWriter<h3svg::QuestDetailsSvg<h3svg::QuestType::DefeatHero>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetailsSvg<h3svg::QuestType::DefeatHero>& details) const;

  template<>
  void JsonObjectWriter<h3svg::QuestDetailsSvg<h3svg::QuestType::DefeatMonster>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetailsSvg<h3svg::QuestType::DefeatMonster>& details) const;

  template<>
  void JsonObjectWriter<h3svg::QuestDetailsSvg<h3svg::QuestType::Artifacts>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetailsSvg<h3svg::QuestType::Artifacts>& details) const;

  template<>
  void JsonObjectWriter<h3svg::QuestDetailsSvg<h3svg::QuestType::Creatures>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetailsSvg<h3svg::QuestType::Creatures>& details) const;

  template<>
  void JsonObjectWriter<h3svg::QuestDetailsSvg<h3svg::QuestType::Resources>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetailsSvg<h3svg::QuestType::Resources>& details) const;

  template<>
  void JsonObjectWriter<h3svg::QuestDetailsSvg<h3svg::QuestType::BeHero>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetailsSvg<h3svg::QuestType::BeHero>& details) const;

  template<>
  void JsonObjectWriter<h3svg::QuestDetailsSvg<h3svg::QuestType::BePlayer>>::operator()(
    FieldsWriter& out, const h3svg::QuestDetailsSvg<h3svg::QuestType::BePlayer>& details) const;

  template<>
  void JsonObjectWriter<h3svg::QuestGuardSvg>::operator()(FieldsWriter& out,
                                                          const h3svg::QuestGuardSvg& quest_guard) const;

  template<>
  void JsonObjectWriter<h3svg::RewardSvg>::operator()(FieldsWriter& out, const h3svg::RewardSvg& reward) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetailsSvg<h3svg::RewardType::None>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetailsSvg<h3svg::RewardType::None>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetailsSvg<h3svg::RewardType::Experience>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetailsSvg<h3svg::RewardType::Experience>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetailsSvg<h3svg::RewardType::SpellPoints>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetailsSvg<h3svg::RewardType::SpellPoints>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetailsSvg<h3svg::RewardType::Morale>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetailsSvg<h3svg::RewardType::Morale>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetailsSvg<h3svg::RewardType::Luck>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetailsSvg<h3svg::RewardType::Luck>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetailsSvg<h3svg::RewardType::Resource>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetailsSvg<h3svg::RewardType::Resource>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetailsSvg<h3svg::RewardType::PrimarySkill>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetailsSvg<h3svg::RewardType::PrimarySkill>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetailsSvg<h3svg::RewardType::SecondarySkill>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetailsSvg<h3svg::RewardType::SecondarySkill>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetailsSvg<h3svg::RewardType::Artifact>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetailsSvg<h3svg::RewardType::Artifact>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetailsSvg<h3svg::RewardType::Spell>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetailsSvg<h3svg::RewardType::Spell>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RewardDetailsSvg<h3svg::RewardType::Creature>>::operator()(
    FieldsWriter& out, const h3svg::RewardDetailsSvg<h3svg::RewardType::Creature>& details) const;

  template<>
  void JsonObjectWriter<h3svg::RumorSvg>::operator()(FieldsWriter& out, const h3svg::RumorSvg& rumor) const;

  template<>
  void JsonObjectWriter<h3svg::SavedGame>::operator()(FieldsWriter& out, const h3svg::SavedGame& saved_game) const;

  template<>
  void JsonObjectWriter<h3svg::ScenarioStartingInfo>::operator()(FieldsWriter& out,
                                                                 const h3svg::ScenarioStartingInfo& starting_info) const;

  template<>
  void JsonObjectWriter<h3svg::SeersHutSvg>::operator()(FieldsWriter& out, const h3svg::SeersHutSvg& seers_hut) const;

  template<>
  void JsonObjectWriter<h3svg::SignSvg>::operator()(FieldsWriter& out, const h3svg::SignSvg& sign) const;

  template<>
  void JsonObjectWriter<h3svg::TileSvg>::operator()(FieldsWriter& out, const h3svg::TileSvg& tile) const;

  template<>
  void JsonObjectWriter<h3svg::TimedEventSvg>::operator()(FieldsWriter& out, const h3svg::TimedEventSvg& event) const;

  template<>
  void JsonObjectWriter<h3svg::TownEventSvg>::operator()(FieldsWriter& out, const h3svg::TownEventSvg& event) const;

  template<>
  void JsonObjectWriter<h3svg::TownSvg>::operator()(FieldsWriter& out, const h3svg::TownSvg& town) const;

  template<>
  void JsonObjectWriter<h3svg::TroopsSvg>::operator()(FieldsWriter& out, const h3svg::TroopsSvg& troops) const;
}
