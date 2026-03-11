#include <h3mtxt/H3SvgJsonWriter/H3SvgJsonWriter.h>

#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3SvgJsonWriter/getEnumString.h>
#include <h3mtxt/JsonCommon/FieldNamesSvg.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/ObjectPropertiesTables.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3svg::Artifact>::operator()(FieldsWriter& out, const h3svg::Artifact& artifact) const
  {
    using Fields = h3json::FieldNames<h3svg::Artifact>;
    out.writeField(Fields::kGuardians, artifact.guardians);
  }

  void JsonObjectWriter<h3svg::Boat>::operator()(FieldsWriter& out, const h3svg::Boat& boat) const
  {
    using Fields = h3json::FieldNames<h3svg::Boat>;

    out.writeField(Fields::kUnknown1, boat.unknown1);
    out.writeField(Fields::kObjectSubclass, boat.object_sublcass);
    out.writeField(Fields::kDirection, boat.direction);
    out.writeField(Fields::kOwner, boat.owner);
    if (std::string_view enum_str = getEnumString(boat.owner); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kOwnerHero, boat.owner_hero);
    out.writeField(Fields::kIsOccupied, boat.is_occupied);
    out.writeField(Fields::kX, boat.x);
    out.writeField(Fields::kY, boat.y);
    out.writeField(Fields::kZ, boat.z);
    out.writeField(Fields::kUnknown2, boat.unknown2);
  }

  void JsonObjectWriter<h3svg::Dwelling>::operator()(FieldsWriter& out, const h3svg::Dwelling& dwelling) const
  {
    using Fields = h3json::FieldNames<h3svg::Dwelling>;
    out.writeField(Fields::kOwner, dwelling.owner);
    if (std::string_view enum_str = getEnumString(dwelling.owner); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kObjectClass, dwelling.object_class);
    out.writeField(Fields::kObjectSubclass, dwelling.object_subclass);
    out.writeField(Fields::kCreatureTypes, dwelling.creature_types);
    out.writeField(Fields::kCreatureCounts, dwelling.creature_counts);
    out.writeField(Fields::kCoordinates, dwelling.coordinates);
    out.writeField(Fields::kGuardians, dwelling.guardians);
    out.writeField(Fields::kUnknown, dwelling.unknown);
  }

  void JsonObjectWriter<h3svg::EventBase>::operator()(FieldsWriter& out, const h3svg::EventBase& event) const
  {
    using Fields = h3json::FieldNames<h3svg::EventBase>;
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
  }

  void JsonObjectWriter<h3svg::Garrison>::operator()(FieldsWriter& out, const h3svg::Garrison& garrison) const
  {
    using Fields = h3json::FieldNames<h3svg::Garrison>;
    out.writeField(Fields::kOwner, garrison.owner);
    if (std::string_view enum_str = getEnumString(garrison.owner); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kCreatures, garrison.creatures);
    out.writeField(Fields::kCoordinates, garrison.coordinates);
    out.writeField(Fields::kCanRemoveUnits, garrison.can_remove_units);
  }

  void JsonObjectWriter<h3svg::Guardians>::operator()(FieldsWriter& out, const h3svg::Guardians& guardians) const
  {
    using Fields = h3json::FieldNames<h3svg::Guardians>;
    out.writeField(Fields::kMessage, guardians.message);
    if (guardians.creatures)
    {
      out.writeField(Fields::kCreatures, *guardians.creatures);
    }
  }

  void JsonObjectWriter<h3svg::Mine>::operator()(FieldsWriter& out, const h3svg::Mine& mine) const
  {
    using Fields = h3json::FieldNames<h3svg::Mine>;
    out.writeField(Fields::kOwner, mine.owner);
    if (std::string_view enum_str = getEnumString(mine.owner); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kUnknown, mine.unknown);
    out.writeField(Fields::kCreatures, mine.creatures);
    out.writeField(Fields::kCoordinates, mine.coordinates);
  }

  void JsonObjectWriter<h3svg::Monster>::operator()(FieldsWriter& out, const h3svg::Monster& monster) const
  {
    using Fields = h3json::FieldNames<h3svg::Monster>;
    out.writeField(Fields::kMessage, monster.message);
    out.writeField(Fields::kResources, monster.resources);
    out.writeField(Fields::kArtifact, monster.artifact);
    if (std::string_view enum_str = getEnumString(monster.artifact); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
  }

  void JsonObjectWriter<h3svg::Obelisk>::operator()(FieldsWriter& out, const h3svg::Obelisk& obelisk) const
  {
    using Fields = h3json::FieldNames<h3svg::Obelisk>;
    out.writeField(Fields::kVisitedBy, obelisk.visited_by);
  }

  void JsonObjectWriter<h3svg::QuestGuard>::operator()(FieldsWriter& out,
                                                       const h3svg::QuestGuard& quest_guard) const
  {
    using Fields = h3json::FieldNames<h3svg::QuestGuard>;
    out.writeField(Fields::kQuest, quest_guard.quest);
    out.writeField(Fields::kVisitedBy, quest_guard.visited_by);
  }

  void JsonObjectWriter<h3svg::SeersHut>::operator()(FieldsWriter& out, const h3svg::SeersHut& seers_hut) const
  {
    using Fields = h3json::FieldNames<h3svg::SeersHut>;
    out.writeField(Fields::kQuest, seers_hut.quest);
    out.writeField(Fields::kReward, seers_hut.reward);
    out.writeField(Fields::kReserved, seers_hut.reserved);
    out.writeField(Fields::kVisitedBy, seers_hut.visited_by);
    out.writeField(Fields::kName, seers_hut.name);
    if (std::string_view enum_str = getEnumString(seers_hut.name); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
  }

  void JsonObjectWriter<h3svg::Sign>::operator()(FieldsWriter& out, const h3svg::Sign& sign) const
  {
    using Fields = h3json::FieldNames<h3svg::Sign>;
    out.writeField(Fields::kMessage, sign.message);
    out.writeField(Fields::kIsCustom, sign.is_custom);
  }

  void JsonObjectWriter<h3svg::TimedEvent>::operator()(FieldsWriter& out,
                                                       const h3svg::TimedEvent& event) const
  {
    using Fields = h3json::FieldNames<h3svg::TimedEvent>;
    out.writeField(Fields::kMessage, event.message);
    out.writeField(Fields::kResources, event.resources);
    out.writeField(Fields::kAffectedPlayers, event.affected_players);
    out.writeField(Fields::kAppliesToHuman, event.applies_to_human);
    out.writeField(Fields::kAppliesToComputer, event.applies_to_computer);
    out.writeField(Fields::kDayOfFirstOccurence, event.day_of_first_occurence);
    out.writeField(Fields::kRepeatAfterDays, event.repeat_after_days);
  }

  void JsonObjectWriter<h3svg::TownEvent>::operator()(FieldsWriter& out, const h3svg::TownEvent& event) const
  {
    using Fields = h3json::FieldNames<h3svg::TownEvent>;
    JsonObjectWriter<h3svg::TimedEvent>{}(out, event);
    out.writeField(Fields::kTownId, event.town_id);
    out.writeField(Fields::kBuildings, event.buildings);
    out.writeField(Fields::kReserved, event.reserved);
    out.writeField(Fields::kCreatures, event.creatures);
  }

  void JsonObjectWriter<h3svg::Troops>::operator()(FieldsWriter& out, const h3svg::Troops& troops) const
  {
    using Fields = h3json::FieldNames<h3svg::Troops>;
    out.writeField(Fields::kCreatureTypes, troops.creature_types);
    out.writeField(Fields::kCreatureCounts, troops.creature_counts);
  }

  void JsonObjectWriter<h3svg::ObjectPropertiesTables>::operator()(FieldsWriter& out,
                                                                   const h3svg::ObjectPropertiesTables& tables) const
  {
    using Fields = h3json::FieldNames<h3svg::ObjectPropertiesTables>;
    out.writeField(Fields::kEventsAndPandorasBoxes, tables.events_and_pandoras_boxes);
    out.writeField(Fields::kArtifactsAndSpellScrolls, tables.artifacts_and_spell_scrolls);
    out.writeField(Fields::kMonsters, tables.monsters);
    out.writeField(Fields::kSeersHuts, tables.seers_huts);
    out.writeField(Fields::kQuestGuards, tables.quest_guards);
    out.writeField(Fields::kGlobalEvents, tables.global_events);
    out.writeField(Fields::kTownEvents, tables.town_events);
    out.writeField(Fields::kSignsAndOceanBottles, tables.signs_and_ocean_bottles);
    out.writeField(Fields::kMinesAndLighthouses, tables.mines_and_lighthouses);
    out.writeField(Fields::kDwellings, tables.dwellings);
    out.writeField(Fields::kGarrisons, tables.garrisons);
    out.writeField(Fields::kBoats, tables.boats);
    out.writeField(Fields::kNumObelisks, tables.num_obelisks);
    out.writeField(Fields::kObelisks, tables.obelisks);
  }
}
