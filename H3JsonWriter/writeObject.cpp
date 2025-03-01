#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/ObjectDetails.h>


namespace Medea_NS
{
  void JsonObjectWriter<h3m::ResourcesBitmask>::operator()(FieldsWriter& out,
                                                           const h3m::ResourcesBitmask& resources_bitmask) const
  {
    using Fields = h3m::FieldNames<h3m::ResourcesBitmask>;
    for (std::uint8_t i = 0; i < 8; ++i)
    {
      out.writeField(Fields::kNames[i], resources_bitmask[static_cast<h3m::ResourceType>(i)]);
    }
  }

  void JsonObjectWriter<h3m::TownBuildingsBitmask>::operator()(
    FieldsWriter& out, const h3m::TownBuildingsBitmask& buildings_bitmask) const
  {
    using Fields = h3m::FieldNames<h3m::TownBuildingsBitmask>;
    for (std::size_t i = 0; i < h3m::TownBuildingsBitmask::kNumBits; ++i)
    {
      out.writeField(Fields::kNames[i], buildings_bitmask.bitset[i]);
    }
  }

  void JsonObjectWriter<h3m::TownBuildings>::operator()(FieldsWriter& out,
                                                        const h3m::TownBuildings& town_buildings) const
  {
    using Fields = h3m::FieldNames<h3m::TownBuildings>;
    out.writeField(Fields::kIsBuilt, town_buildings.is_built);
    out.writeField(Fields::kIsDisabled, town_buildings.is_disabled);
  }

  void JsonObjectWriter<h3m::TownEvent>::operator()(FieldsWriter& out, const h3m::TownEvent& town_event) const
  {
    using Fields = h3m::FieldNames<h3m::TownEvent>;
    printTimedEventBase(out, town_event);
    out.writeField(Fields::kBuildings, town_event.buildings);
    out.writeField(Fields::kCreatures, town_event.creatures);
    out.writeField(Fields::kUnknown2, town_event.unknown2);
  }

  void JsonObjectWriter<h3m::Guardians>::operator()(FieldsWriter& out, const h3m::Guardians& guardians) const
  {
    using Fields = h3m::FieldNames<h3m::Guardians>;
    out.writeField(Fields::kMessage, guardians.message);
    if (guardians.creatures)
    {
      out.writeField(Fields::kCreatures, *guardians.creatures);
    }
    out.writeField(Fields::kUnknown, guardians.unknown);
  }

  void JsonObjectWriter<h3m::MessageAndTreasure>::operator()(FieldsWriter& out,
                                                             const h3m::MessageAndTreasure& data) const
  {
    using Fields = h3m::FieldNames<h3m::MessageAndTreasure>;
    out.writeField(Fields::kMessage, data.message);
    out.writeField(Fields::kResources, data.resources);
    out.writeField(Fields::kArtifact, data.artifact);
    const std::string_view artifact_str = (data.artifact == h3m::ArtifactType{ 0xFFFF }) ?
      "(None)" : h3m::getEnumString(data.artifact);
    if (!artifact_str.empty())
    {
      out.writeComment(artifact_str, false);
    }
  }

  void printEventBase(FieldsWriter& out, const h3m::EventBase& event)
  {
    using Fields = h3m::FieldNames<h3m::EventBase>;
    if (event.guardians)
    {
      out.writeField(Fields::kGuardians, *event.guardians);
    }
    out.writeField(Fields::kExperience, event.experience);
    out.writeField(Fields::kSpellPoints, event.spell_points);
    out.writeField(Fields::kMorale, event.morale);
    out.writeField(Fields::kLuck, event.luck);
    out.writeField(Fields::kResources, event.resources);
    out.writeField(Fields::kPrimarySkills, event.primary_skills);
    out.writeField(Fields::kSecondarySkills, event.secondary_skills);
    out.writeField(Fields::kArtifacts, event.artifacts);
    out.writeField(Fields::kSpells, event.spells);
    out.writeField(Fields::kCreatures, event.creatures);
    out.writeField(Fields::kUnknown, event.unknown);
  }
}
