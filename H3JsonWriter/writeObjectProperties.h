#pragma once

#include <h3mtxt/Medea/MedeaFwd.h>
#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/ObjectPropertiesType.h>

// API for JSON serialization of h3m::ObjectProperties.
namespace Medea_NS
{
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
  void JsonObjectWriter<h3m::ObjectProperties<h3m::ObjectPropertiesType::GENERIC_NO_PROPERTIES>>::operator()(
    FieldsWriter& out, const h3m::ObjectProperties<h3m::ObjectPropertiesType::GENERIC_NO_PROPERTIES>& details) const;

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
}
