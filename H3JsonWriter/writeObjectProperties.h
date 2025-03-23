#pragma once

#include <h3mtxt/Medea/MedeaFwd.h>
#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/MetaObjectType.h>

// API for JSON serialization of h3m::ObjectProperties.
namespace Medea_NS
{
  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::ABANDONED_MINE>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::ABANDONED_MINE>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::ARTIFACT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::ARTIFACT>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::EVENT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::EVENT>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::GARRISON>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::GARRISON>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::GENERIC_NO_PROPERTIES>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::GENERIC_NO_PROPERTIES>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::GRAIL>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::GRAIL>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::HERO>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::HERO>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::MONSTER>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::MONSTER>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::PANDORAS_BOX>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::PANDORAS_BOX>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::PLACEHOLDER_HERO>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::PLACEHOLDER_HERO>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::QUEST_GUARD>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::QUEST_GUARD>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::RANDOM_DWELLING>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::RANDOM_DWELLING>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::RANDOM_DWELLING_PRESET_ALIGNMENT>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::RANDOM_DWELLING_PRESET_LEVEL>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::RESOURCE>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::RESOURCE>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::SCHOLAR>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::SCHOLAR>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::SEERS_HUT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::SEERS_HUT>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::SHRINE>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::SHRINE>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::SIGN>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::SIGN>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::SPELL_SCROLL>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::SPELL_SCROLL>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::TOWN>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::TOWN>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::TRIVIAL_OWNED_OBJECT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::TRIVIAL_OWNED_OBJECT>& details) const;

  template<>
  void JsonObjectWriter<h3m::ObjectProperties<h3m::MetaObjectType::WITCH_HUT>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::MetaObjectType::WITCH_HUT>& details) const;
}
