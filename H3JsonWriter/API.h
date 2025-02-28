#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>
#include <h3mtxt/Map/MapFwd.h>

// API for JSON serialization of H3 structures.
namespace Medea_NS
{
  template<>
  void JsonValueWriter<h3m::ArtifactsBitmask>::operator()(JsonDocumentWriter& out, const h3m::ArtifactsBitmask& bitmask) const;

  template<>
  void JsonObjectWriter<h3m::CreatureStack>::operator()(FieldsWriter& out, const h3m::CreatureStack& creature_stack) const;

  template<>
  void JsonObjectWriter<h3m::GlobalEvent>::operator()(FieldsWriter& out, const h3m::GlobalEvent& global_event) const;

  template<>
  void JsonObjectWriter<h3m::HeroArtifacts>::operator()(FieldsWriter& out, const h3m::HeroArtifacts& value) const;

  template<>
  void JsonObjectWriter<h3m::HeroSettings>::operator()(FieldsWriter& out, const h3m::HeroSettings& value) const;

  template<>
  void JsonObjectWriter<h3m::HeroesBitmask>::operator()(FieldsWriter& out, const h3m::HeroesBitmask& value) const;

  template<>
  void JsonValueWriter<h3m::HeroesSettings>::operator()(JsonDocumentWriter& out,
                                                        const h3m::HeroesSettings& value) const;

  template<>
  void JsonObjectWriter<h3m::MainTown>::operator()(FieldsWriter& out, const h3m::MainTown& value) const;

  template<>
  void JsonObjectWriter<h3m::Map>::operator()(FieldsWriter& out, const h3m::Map& value) const;

  template<>
  void JsonObjectWriter<h3m::MapAdditionalInfo>::operator()(FieldsWriter& out, const h3m::MapAdditionalInfo& value) const;

  template<>
  void JsonObjectWriter<h3m::MapBasicInfo>::operator()(FieldsWriter& out, const h3m::MapBasicInfo& value) const;

  template<>
  void JsonObjectWriter<h3m::ObjectTemplate>::operator()(FieldsWriter& out, const h3m::ObjectTemplate& value) const;

  template<>
  void JsonObjectWriter<h3m::PlayerSpecs>::operator()(FieldsWriter& out, const h3m::PlayerSpecs& value) const;

  template<>
  void JsonObjectWriter<h3m::PlayersBitmask>::operator()(FieldsWriter& out,
                                                         const h3m::PlayersBitmask& players_bitmask) const;

  template<>
  void JsonObjectWriter<h3m::PrimarySkills>::operator()(FieldsWriter& out, const h3m::PrimarySkills& value) const;

  template<>
  void JsonObjectWriter<h3m::Quest>::operator()(FieldsWriter& out, const h3m::Quest& quest) const;

  template<>
  void JsonObjectWriter<h3m::Resources>::operator()(FieldsWriter& out, const h3m::Resources& resources) const;

  template<>
  void JsonObjectWriter<h3m::Rumor>::operator()(FieldsWriter& out, const h3m::Rumor& value) const;

  template<>
  void JsonObjectWriter<h3m::SecondarySkill>::operator()(FieldsWriter& out, const h3m::SecondarySkill& skill) const;

  template<>
  void JsonObjectWriter<h3m::SecondarySkillsBitmask>::operator()(FieldsWriter& out,
                                                                 const h3m::SecondarySkillsBitmask& bitmask) const;

  template<>
  void JsonValueWriter<h3m::SpellsBitmask>::operator()(JsonDocumentWriter& out,
                                                       const h3m::SpellsBitmask& bitmask) const;

  template<>
  void JsonObjectWriter<h3m::StartingHero>::operator()(FieldsWriter& out, const h3m::StartingHero& value) const;

  template<>
  void JsonObjectWriter<h3m::TeamsInfo>::operator()(FieldsWriter& out, const h3m::TeamsInfo& value) const;

  template<>
  void JsonValueWriter<h3m::TerrainsBitmask>::operator()(JsonDocumentWriter& out,
                                                         const h3m::TerrainsBitmask& bitmask) const;

  template<>
  void JsonObjectWriter<h3m::Tile>::operator()(FieldsWriter& out, const h3m::Tile& value) const;

  template<>
  void JsonObjectWriter<h3m::TownsBitmask>::operator()(FieldsWriter& out, const h3m::TownsBitmask& bitmask) const;

  void printTimedEventBase(FieldsWriter& out, const h3m::TimedEventBase& event);
}
