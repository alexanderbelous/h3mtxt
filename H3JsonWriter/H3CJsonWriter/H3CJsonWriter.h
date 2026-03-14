#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/Campaign/Constants/StartingBonusType.h>
#include <h3mtxt/Campaign/Constants/StartingOptionsType.h>
#include <h3mtxt/Medea/MedeaFwd.h>

// API for JSON serialization of structures from Campaign library.
namespace Medea_NS
{
  template<>
  void JsonObjectWriter<h3m::Campaign>::operator()(FieldsWriter& out, const h3m::Campaign& campaign) const;

  template<>
  void JsonObjectWriter<h3m::CampaignHeader>::operator()(FieldsWriter& out, const h3m::CampaignHeader& campaign) const;

  template<>
  void JsonObjectWriter<h3m::CampaignScenario>::operator()(FieldsWriter& out,
                                                           const h3m::CampaignScenario& scenario) const;

  template<>
  void JsonObjectWriter<h3m::CrossoverOptions>::operator()(FieldsWriter& out,
                                                           const h3m::CrossoverOptions& cutscene) const;

  template<>
  void JsonObjectWriter<h3m::CutScene>::operator()(FieldsWriter& out, const h3m::CutScene& cutscene) const;

  template<>
  void JsonObjectWriter<h3m::StartingBonus>::operator()(FieldsWriter& out, const h3m::StartingBonus& bonus) const;

  template<>
  void JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::Spell>>::operator()(
    FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::Spell>& details) const;

  template<>
  void JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::Creature>>::operator()(
    FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::Creature>& details) const;

  template<>
  void JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::Building>>::operator()(
    FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::Building>& details) const;

  template<>
  void JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::Artifact>>::operator()(
    FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::Artifact>& details) const;

  template<>
  void JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::SpellScroll>>::operator()(
    FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::SpellScroll>& details) const;

  template<>
  void JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::PrimarySkills>>::operator()(
    FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::PrimarySkills>& details) const;

  template<>
  void JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::SecondarySkill>>::operator()(
    FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::SecondarySkill>& details) const;

  template<>
  void JsonObjectWriter<h3m::StartingBonusDetails<h3m::StartingBonusType::Resource>>::operator()(
    FieldsWriter& out, const h3m::StartingBonusDetails<h3m::StartingBonusType::Resource>& details) const;

  template<>
  void JsonObjectWriter<h3m::StartingOptions>::operator()(FieldsWriter& out,
                                                          const h3m::StartingOptions& starting_options) const;

  template<>
  void JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::None>>::operator()(
    FieldsWriter&, const h3m::StartingOptionsDetails<h3m::StartingOptionsType::None>&) const;

  template<>
  void JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingBonus>>::operator()(
    FieldsWriter&, const h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingBonus>&) const;

  template<>
  void JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::HeroCrossover>>::operator()(
    FieldsWriter&, const h3m::StartingOptionsDetails<h3m::StartingOptionsType::HeroCrossover>&) const;

  template<>
  void JsonObjectWriter<h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingHero>>::operator()(
    FieldsWriter&, const h3m::StartingOptionsDetails<h3m::StartingOptionsType::StartingHero>&) const;
}
