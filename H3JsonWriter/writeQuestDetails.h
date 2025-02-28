#include <h3mtxt/JsonWriter/JsonWriterFwd.h>
#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Constants/QuestType.h>

// API for JSON serialization of h3m::QuestDetails.
//
// These specializations are declared here rather than in API.h because I don't want to
// include the full definition of QuestType in API.h.
namespace Medea_NS
{
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
}
