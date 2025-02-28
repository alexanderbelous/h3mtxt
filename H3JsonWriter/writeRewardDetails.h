#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>
#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/RewardType.h>

// API for JSON serialization of h3m::RewardDetails.
namespace Medea_NS
{
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
}
