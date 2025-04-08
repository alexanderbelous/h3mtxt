#pragma once

#include <h3mtxt/Campaign/CampaignFwd.h>
#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Medea/MedeaFwd.h>

#include <cstddef>

// API for JSON serialization of H3 structures.
namespace Medea_NS
{
  // Default implementation for h3m::EnumBitmask: serializes the bitmask as a JSON object.
  template<class Enum, std::size_t NumBytes>
  struct JsonObjectWriter<h3m::EnumBitmask<Enum, NumBytes>>
  {
    // Defined in Utils.h.
    void operator()(FieldsWriter& out, const h3m::EnumBitmask<Enum, NumBytes>& bitmask) const;
  };

  // Serializes h3m::BitSet as a JSON array.
  template<std::size_t NumBytes>
  struct JsonArrayWriter<h3m::BitSet<NumBytes>>
  {
    // Defined in Utils.h
    void operator()(const ArrayElementsWriter& elements_writer, const h3m::BitSet<NumBytes>& bitset) const;
  };

  // Serialize h3m::BitSet on a single line by default.
  template<std::size_t NumBytes>
  inline constexpr bool kIsSingleLineByDefault<h3m::BitSet<NumBytes>> = true;

  // Serializes h3m::ReservedData as a JSON array.
  template<std::size_t NumBytes>
  struct JsonArrayWriter<h3m::ReservedData<NumBytes>>
  {
    // Defined in Utils.h
    void operator()(const ArrayElementsWriter& elements_writer,
                    const h3m::ReservedData<NumBytes>& reserved_data) const;
  };

  // Serialize h3m::ReservedData on a single line by default.
  template<std::size_t NumBytes>
  inline constexpr bool kIsSingleLineByDefault<h3m::ReservedData<NumBytes>> = true;

  template<>
  void JsonObjectWriter<h3m::CreatureStack>::operator()(FieldsWriter& out, const h3m::CreatureStack& creature_stack) const;

  template<>
  void JsonObjectWriter<h3m::EventBase>::operator()(FieldsWriter& out, const h3m::EventBase& event) const;

  template<>
  void JsonObjectWriter<h3m::Guardians>::operator()(FieldsWriter& out, const h3m::Guardians& guardians) const;

  template<>
  void JsonObjectWriter<h3m::HeroArtifacts>::operator()(FieldsWriter& out, const h3m::HeroArtifacts& value) const;

  template<>
  void JsonObjectWriter<h3m::HeroSettings>::operator()(FieldsWriter& out, const h3m::HeroSettings& value) const;

  // Serialize h3m::HeroesSettings as a JSON array.
  template<>
  void JsonArrayWriter<h3m::HeroesSettings>::operator()(const ArrayElementsWriter& out,
                                                        const h3m::HeroesSettings& value) const;

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
  struct JsonObjectWriter<h3m::Object>
  {
    // Constructs a writer that won't print any comments about the object's template.
    constexpr JsonObjectWriter() noexcept = default;

    // Constructs a writer that will print comments about the object's template.
    constexpr JsonObjectWriter(const h3m::ObjectTemplate* objects_templates,
                               std::size_t num_objects_templates) noexcept:
      objects_templates_(objects_templates),
      num_objects_templates_(num_objects_templates)
    {}

    void operator()(FieldsWriter& out, const h3m::Object& object) const;

  private:
    const h3m::ObjectTemplate* objects_templates_ = nullptr;
    std::size_t num_objects_templates_ = 0;
  };

  template<>
  void JsonObjectWriter<h3m::ObjectTemplate>::operator()(FieldsWriter& out, const h3m::ObjectTemplate& value) const;

  template<>
  void JsonObjectWriter<h3m::PlayerSpecs>::operator()(FieldsWriter& out, const h3m::PlayerSpecs& value) const;

  template<>
  void JsonObjectWriter<h3m::PrimarySkills>::operator()(FieldsWriter& out, const h3m::PrimarySkills& value) const;

  template<>
  void JsonObjectWriter<h3m::Quest>::operator()(FieldsWriter& out, const h3m::Quest& quest) const;

  template<>
  void JsonObjectWriter<h3m::Resources>::operator()(FieldsWriter& out, const h3m::Resources& resources) const;

  template<>
  void JsonObjectWriter<h3m::Reward>::operator()(FieldsWriter& out, const h3m::Reward& reward) const;

  template<>
  void JsonObjectWriter<h3m::Rumor>::operator()(FieldsWriter& out, const h3m::Rumor& value) const;

  template<>
  void JsonObjectWriter<h3m::SecondarySkill>::operator()(FieldsWriter& out, const h3m::SecondarySkill& skill) const;

  template<>
  void JsonObjectWriter<h3m::StartingHero>::operator()(FieldsWriter& out, const h3m::StartingHero& value) const;

  template<>
  void JsonObjectWriter<h3m::TeamsInfo>::operator()(FieldsWriter& out, const h3m::TeamsInfo& value) const;

  // Serialize h3m::TerrainsBitmask as a JSON array.
  template<>
  void JsonArrayWriter<h3m::TerrainsBitmask>::operator()(const ArrayElementsWriter& elements_writer,
                                                         const h3m::TerrainsBitmask& bitmask) const;

  // Serialize h3m::TerrainsBitmask on a single line by default.
  template<>
  inline constexpr bool kIsSingleLineByDefault<h3m::TerrainsBitmask> = true;

  template<>
  void JsonObjectWriter<h3m::Tile>::operator()(FieldsWriter& out, const h3m::Tile& value) const;

  // Serialize h3m::TileFlags on a single line by default.
  // This is done to reduce the number of lines in the output JSON.
  template<>
  inline constexpr bool kIsSingleLineByDefault<h3m::TileFlags> = true;

  template<>
  void JsonObjectWriter<h3m::TimedEvent>::operator()(FieldsWriter& out, const h3m::TimedEvent& event) const;

  template<>
  void JsonObjectWriter<h3m::TownBuildings>::operator()(FieldsWriter& out,
                                                        const h3m::TownBuildings& town_buildings) const;

  template<>
  void JsonObjectWriter<h3m::TownEvent>::operator()(FieldsWriter& out, const h3m::TownEvent& town_event) const;

  template<>
  void JsonObjectWriter<h3m::VictoryCondition>::operator()(FieldsWriter& out,
                                                           const h3m::VictoryCondition& value) const;

  // === Campaign ===
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
  void JsonObjectWriter<h3m::StartingOptions>::operator()(FieldsWriter& out,
                                                          const h3m::StartingOptions& starting_options) const;
}
