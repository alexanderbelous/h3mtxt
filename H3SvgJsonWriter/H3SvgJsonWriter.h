#pragma once

#include <h3mtxt/Map/Constants/QuestType.h>
#include <h3mtxt/Map/Constants/RewardType.h>
#include <h3mtxt/SavedGame/SavedGameFwd.h>
#include <h3mtxt/Medea/MedeaFwd.h>

// API for JSON serialization of structures used in HoMM3 saved game format.
namespace Medea_NS
{
  template<>
  void JsonObjectWriter<h3m::ArtifactSvg>::operator()(FieldsWriter& out, const h3m::ArtifactSvg& artifact) const;

  // Serialize h3m::BlackMarket as a JSON array.
  template<>
  void JsonArrayWriter<h3m::BlackMarket>::operator()(const ArrayElementsWriter& out,
                                                     const h3m::BlackMarket& black_market) const;

  template<>
  void JsonObjectWriter<h3m::BoatSvg>::operator()(FieldsWriter& out, const h3m::BoatSvg& boat) const;

  template<>
  void JsonObjectWriter<h3m::DwellingSvg>::operator()(FieldsWriter& out, const h3m::DwellingSvg& dwelling) const;

  template<>
  void JsonObjectWriter<h3m::EventBaseSvg>::operator()(FieldsWriter& out, const h3m::EventBaseSvg& event) const;

  template<>
  void JsonObjectWriter<h3m::GarrisonSvg>::operator()(FieldsWriter& out, const h3m::GarrisonSvg& garrison) const;

  template<>
  void JsonObjectWriter<h3m::GuardiansSvg>::operator()(FieldsWriter& out, const h3m::GuardiansSvg& guardians) const;

  template<>
  void JsonObjectWriter<h3m::MineSvg>::operator()(FieldsWriter& out, const h3m::MineSvg& mine) const;

  template<>
  void JsonObjectWriter<h3m::MonsterSvg>::operator()(FieldsWriter& out, const h3m::MonsterSvg& monster) const;

  template<>
  void JsonObjectWriter<h3m::ObeliskSvg>::operator()(FieldsWriter& out, const h3m::ObeliskSvg& obelisk) const;

  template<>
  void JsonObjectWriter<h3m::ObjectPropertiesTables>::operator()(FieldsWriter& out,
                                                                 const h3m::ObjectPropertiesTables& tables) const;

  template<>
  void JsonObjectWriter<h3m::ObjectSvg>::operator()(FieldsWriter& out, const h3m::ObjectSvg& object) const;

  template<>
  void JsonObjectWriter<h3m::ObjectTemplateSvg>::operator()(FieldsWriter& out,
                                                            const h3m::ObjectTemplateSvg& object_template) const;

  template<>
  void JsonObjectWriter<h3m::PlayerSvg>::operator()(FieldsWriter& out,
                                                    const h3m::PlayerSvg& player) const;

  template<>
  void JsonObjectWriter<h3m::PlayerSpecsSvg>::operator()(FieldsWriter& out,
                                                         const h3m::PlayerSpecsSvg& player_specs) const;

  template<>
  void JsonObjectWriter<h3m::QuestSvg>::operator()(FieldsWriter& out, const h3m::QuestSvg& quest) const;

  template<>
  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::None>>::operator()(
    FieldsWriter& out, const h3m::QuestDetailsSvg<h3m::QuestType::None>& details) const;

  template<>
  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::Level>>::operator()(
    FieldsWriter& out, const h3m::QuestDetailsSvg<h3m::QuestType::Level>& details) const;

  template<>
  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::PrimarySkills>>::operator()(
    FieldsWriter& out, const h3m::QuestDetailsSvg<h3m::QuestType::PrimarySkills>& details) const;

  template<>
  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::DefeatHero>>::operator()(
    FieldsWriter& out, const h3m::QuestDetailsSvg<h3m::QuestType::DefeatHero>& details) const;

  template<>
  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::DefeatMonster>>::operator()(
    FieldsWriter& out, const h3m::QuestDetailsSvg<h3m::QuestType::DefeatMonster>& details) const;

  template<>
  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::Artifacts>>::operator()(
    FieldsWriter& out, const h3m::QuestDetailsSvg<h3m::QuestType::Artifacts>& details) const;

  template<>
  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::Creatures>>::operator()(
    FieldsWriter& out, const h3m::QuestDetailsSvg<h3m::QuestType::Creatures>& details) const;

  template<>
  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::Resources>>::operator()(
    FieldsWriter& out, const h3m::QuestDetailsSvg<h3m::QuestType::Resources>& details) const;

  template<>
  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::BeHero>>::operator()(
    FieldsWriter& out, const h3m::QuestDetailsSvg<h3m::QuestType::BeHero>& details) const;

  template<>
  void JsonObjectWriter<h3m::QuestDetailsSvg<h3m::QuestType::BePlayer>>::operator()(
    FieldsWriter& out, const h3m::QuestDetailsSvg<h3m::QuestType::BePlayer>& details) const;

  template<>
  void JsonObjectWriter<h3m::QuestGuardSvg>::operator()(FieldsWriter& out,
                                                        const h3m::QuestGuardSvg& quest_guard) const;

  template<>
  void JsonObjectWriter<h3m::RewardSvg>::operator()(FieldsWriter& out, const h3m::RewardSvg& reward) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::None>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::None>& details) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::Experience>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::Experience>& details) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::SpellPoints>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::SpellPoints>& details) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::Morale>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::Morale>& details) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::Luck>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::Luck>& details) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::Resource>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::Resource>& details) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::PrimarySkill>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::PrimarySkill>& details) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::SecondarySkill>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::SecondarySkill>& details) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::Artifact>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::Artifact>& details) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::Spell>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::Spell>& details) const;

  template<>
  void JsonObjectWriter<h3m::RewardDetailsSvg<h3m::RewardType::Creature>>::operator()(
    FieldsWriter& out, const h3m::RewardDetailsSvg<h3m::RewardType::Creature>& details) const;

  template<>
  void JsonObjectWriter<h3m::RumorSvg>::operator()(FieldsWriter& out, const h3m::RumorSvg& rumor) const;

  template<>
  void JsonObjectWriter<h3m::SavedGame>::operator()(FieldsWriter& out, const h3m::SavedGame& saved_game) const;

  template<>
  void JsonObjectWriter<h3m::ScenarioStartingInfo>::operator()(FieldsWriter& out,
                                                               const h3m::ScenarioStartingInfo& starting_info) const;

  template<>
  void JsonObjectWriter<h3m::SeersHutSvg>::operator()(FieldsWriter& out, const h3m::SeersHutSvg& seers_hut) const;

  template<>
  void JsonObjectWriter<h3m::SignSvg>::operator()(FieldsWriter& out, const h3m::SignSvg& sign) const;

  template<>
  void JsonObjectWriter<h3m::TileSvg>::operator()(FieldsWriter& out, const h3m::TileSvg& tile) const;

  template<>
  void JsonObjectWriter<h3m::TimedEventSvg>::operator()(FieldsWriter& out, const h3m::TimedEventSvg& event) const;

  template<>
  void JsonObjectWriter<h3m::TownEventSvg>::operator()(FieldsWriter& out, const h3m::TownEventSvg& event) const;

  template<>
  void JsonObjectWriter<h3m::TroopsSvg>::operator()(FieldsWriter& out, const h3m::TroopsSvg& troops) const;
}
