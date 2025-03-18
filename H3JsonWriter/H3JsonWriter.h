#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/JsonWriter/JsonWriterFwd.h>
#include <h3mtxt/Map/MapFwd.h>

#include <cstddef>

// API for JSON serialization of H3 structures.
namespace Medea_NS
{

  // Serialize h3m::TerrainsBitmask as a JSON array.
  template<>
  struct JsonArrayWriter<h3m::TerrainsBitmask>
  {
    using ElementType = std::uint8_t;

    void operator()(ScopedArrayWriter<std::uint8_t>& scoped_array_writer, const h3m::TerrainsBitmask& bitmask) const;
  };

  template<>
  void JsonObjectWriter<h3m::ArtifactsBitmask>::operator()(FieldsWriter& out, const h3m::ArtifactsBitmask& bitmask) const;

  template<>
  void JsonObjectWriter<h3m::CreatureStack>::operator()(FieldsWriter& out, const h3m::CreatureStack& creature_stack) const;

  template<>
  void JsonObjectWriter<h3m::GlobalEvent>::operator()(FieldsWriter& out, const h3m::GlobalEvent& global_event) const;

  template<>
  void JsonObjectWriter<h3m::Guardians>::operator()(FieldsWriter& out, const h3m::Guardians& guardians) const;

  template<>
  void JsonObjectWriter<h3m::HeroArtifacts>::operator()(FieldsWriter& out, const h3m::HeroArtifacts& value) const;

  template<>
  void JsonObjectWriter<h3m::HeroSettings>::operator()(FieldsWriter& out, const h3m::HeroSettings& value) const;

  template<>
  void JsonObjectWriter<h3m::HeroesBitmask>::operator()(FieldsWriter& out, const h3m::HeroesBitmask& value) const;

  template<>
  void JsonObjectWriter<h3m::LossCondition>::operator()(FieldsWriter& out,
                                                        const h3m::LossCondition& loss_condition) const;

  template<>
  void JsonObjectWriter<h3m::MainTown>::operator()(FieldsWriter& out, const h3m::MainTown& value) const;

  template<>
  void JsonObjectWriter<h3m::Map>::operator()(FieldsWriter& out, const h3m::Map& value) const;

  template<>
  void JsonObjectWriter<h3m::MapAdditionalInfo>::operator()(FieldsWriter& out, const h3m::MapAdditionalInfo& value) const;

  template<>
  void JsonObjectWriter<h3m::MapBasicInfo>::operator()(FieldsWriter& out, const h3m::MapBasicInfo& value) const;

  template<>
  void JsonObjectWriter<h3m::MessageAndTreasure>::operator()(FieldsWriter& out,
                                                             const h3m::MessageAndTreasure& data) const;

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
  void JsonObjectWriter<h3m::ResourcesBitmask>::operator()(FieldsWriter& out,
                                                           const h3m::ResourcesBitmask& resources_bitmask) const;

  template<>
  void JsonObjectWriter<h3m::Reward>::operator()(FieldsWriter& out, const h3m::Reward& reward) const;

  template<>
  void JsonObjectWriter<h3m::Rumor>::operator()(FieldsWriter& out, const h3m::Rumor& value) const;

  template<>
  void JsonObjectWriter<h3m::SecondarySkill>::operator()(FieldsWriter& out, const h3m::SecondarySkill& skill) const;

  template<>
  void JsonObjectWriter<h3m::SecondarySkillsBitmask>::operator()(FieldsWriter& out,
                                                                 const h3m::SecondarySkillsBitmask& bitmask) const;

  template<>
  void JsonObjectWriter<h3m::SpellsBitmask>::operator()(FieldsWriter& out, const h3m::SpellsBitmask& bitmask) const;

  template<>
  void JsonObjectWriter<h3m::StartingHero>::operator()(FieldsWriter& out, const h3m::StartingHero& value) const;

  template<>
  void JsonObjectWriter<h3m::TeamsInfo>::operator()(FieldsWriter& out, const h3m::TeamsInfo& value) const;

  template<>
  void JsonObjectWriter<h3m::Tile>::operator()(FieldsWriter& out, const h3m::Tile& value) const;

  template<>
  void JsonObjectWriter<h3m::TownBuildingsBitmask>::operator()(
    FieldsWriter& out, const h3m::TownBuildingsBitmask& buildings_bitmask) const;

  template<>
  void JsonObjectWriter<h3m::TownBuildings>::operator()(FieldsWriter& out,
                                                        const h3m::TownBuildings& town_buildings) const;

  template<>
  void JsonObjectWriter<h3m::TownEvent>::operator()(FieldsWriter& out, const h3m::TownEvent& town_event) const;

  template<>
  void JsonObjectWriter<h3m::TownsBitmask>::operator()(FieldsWriter& out, const h3m::TownsBitmask& bitmask) const;

  template<>
  void JsonObjectWriter<h3m::VictoryCondition>::operator()(FieldsWriter& out,
                                                           const h3m::VictoryCondition& value) const;

  void printEventBase(FieldsWriter& out, const h3m::EventBase& event);

  void printTimedEventBase(FieldsWriter& out, const h3m::TimedEventBase& event);

  // === Campaign ===
  template<>
  void JsonObjectWriter<h3m::Campaign>::operator()(FieldsWriter& out, const h3m::Campaign& campaign) const;

  template<>
  void JsonObjectWriter<h3m::CampaignHeader>::operator()(FieldsWriter& out, const h3m::CampaignHeader& campaign) const;

  template<>
  void JsonObjectWriter<h3m::CampaignScenario>::operator()(FieldsWriter& out,
                                                           const h3m::CampaignScenario& scenario) const;

  template<>
  void JsonObjectWriter<h3m::CrossoverFeaturesBitmask>::operator()(FieldsWriter& out,
                                                                   const h3m::CrossoverFeaturesBitmask& bitmask) const;

  template<>
  void JsonObjectWriter<h3m::CrossoverOptions>::operator()(FieldsWriter& out,
                                                           const h3m::CrossoverOptions& cutscene) const;

  template<>
  void JsonObjectWriter<h3m::CutScene>::operator()(FieldsWriter& out, const h3m::CutScene& cutscene) const;

  template<>
  void JsonObjectWriter<h3m::StartingBonus>::operator()(FieldsWriter& out, const h3m::StartingBonus& bonus) const;

  template<>
  void JsonObjectWriter<h3m::StartingOptions>::operator()(FieldsWriter& out,
                                                          const h3m::StartingOptions& starting_options) const;
}

namespace h3m::H3JsonWriter_NS
{
  void printObject(Medea_NS::FieldsWriter& out,
                   const Object& object,
                   const ObjectTemplate* objects_templates,
                   std::size_t num_objects_templates);
}
