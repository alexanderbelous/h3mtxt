#pragma once

#include <h3mtxt/Medea/MedeaFwd.h>
#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/Campaign/Constants/StartingBonusType.h>

// API for JSON serialization of h3m::StartingBonusDetails.
namespace Medea_NS
{
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
}
