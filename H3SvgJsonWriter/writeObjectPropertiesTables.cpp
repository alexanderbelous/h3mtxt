#include <h3mtxt/H3SvgJsonWriter/H3SvgJsonWriter.h>

#include <h3mtxt/H3JsonWriter/getEnumString.h>
#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/H3SvgJsonWriter/getEnumString.h>
#include <h3mtxt/JsonCommon/FieldNamesSvg.h>
#include <h3mtxt/Medea/Medea.h>
#include <h3mtxt/SavedGame/ObjectPropertiesTables.h>

namespace Medea_NS
{
  void JsonObjectWriter<h3m::ArtifactSvg>::operator()(FieldsWriter& out, const h3m::ArtifactSvg& artifact) const
  {
    using Fields = h3m::FieldNames<h3m::ArtifactSvg>;
    out.writeField(Fields::kGuardians, artifact.guardians);
  }

  void JsonObjectWriter<h3m::BoatSvg>::operator()(FieldsWriter& out, const h3m::BoatSvg& boat) const
  {
    using Fields = h3m::FieldNames<h3m::BoatSvg>;

    out.writeField(Fields::kUnknown1, boat.unknown1);
    out.writeField(Fields::kObjectSubclass, boat.object_sublcass);
    out.writeField(Fields::kDirection, boat.direction);
    out.writeField(Fields::kOwner, boat.owner);
    if (std::string_view enum_str = h3m::getEnumString(boat.owner); !enum_str.empty())
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

  void JsonObjectWriter<h3m::DwellingSvg>::operator()(FieldsWriter& out, const h3m::DwellingSvg& dwelling) const
  {
    using Fields = h3m::FieldNames<h3m::DwellingSvg>;
    out.writeField(Fields::kOwner, dwelling.owner);
    if (std::string_view enum_str = h3m::getEnumString(dwelling.owner); !enum_str.empty())
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

  void JsonObjectWriter<h3m::EventBaseSvg>::operator()(FieldsWriter& out, const h3m::EventBaseSvg& event) const
  {
    using Fields = h3m::FieldNames<h3m::EventBaseSvg>;
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

  void JsonObjectWriter<h3m::GarrisonSvg>::operator()(FieldsWriter& out, const h3m::GarrisonSvg& garrison) const
  {
    using Fields = h3m::FieldNames<h3m::GarrisonSvg>;
    out.writeField(Fields::kOwner, garrison.owner);
    if (std::string_view enum_str = h3m::getEnumString(garrison.owner); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kCreatures, garrison.creatures);
    out.writeField(Fields::kCoordinates, garrison.coordinates);
    out.writeField(Fields::kCanRemoveUnits, garrison.can_remove_units);
  }

  void JsonObjectWriter<h3m::GuardiansSvg>::operator()(FieldsWriter& out, const h3m::GuardiansSvg& guardians) const
  {
    using Fields = h3m::FieldNames<h3m::GuardiansSvg>;
    out.writeField(Fields::kMessage, guardians.message);
    if (guardians.creatures)
    {
      out.writeField(Fields::kCreatures, *guardians.creatures);
    }
  }

  void JsonObjectWriter<h3m::MineSvg>::operator()(FieldsWriter& out, const h3m::MineSvg& mine) const
  {
    using Fields = h3m::FieldNames<h3m::MineSvg>;
    out.writeField(Fields::kOwner, mine.owner);
    if (std::string_view enum_str = h3m::getEnumString(mine.owner); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
    out.writeField(Fields::kUnknown, mine.unknown);
    out.writeField(Fields::kCreatures, mine.creatures);
    out.writeField(Fields::kCoordinates, mine.coordinates);
  }

  void JsonObjectWriter<h3m::MonsterSvg>::operator()(FieldsWriter& out, const h3m::MonsterSvg& monster) const
  {
    using Fields = h3m::FieldNames<h3m::MonsterSvg>;
    out.writeField(Fields::kMessage, monster.message);
    out.writeField(Fields::kResources, monster.resources);
    out.writeField(Fields::kArtifact, monster.artifact);
    if (std::string_view enum_str = h3m::getEnumString(monster.artifact); !enum_str.empty())
    {
      out.writeComment(enum_str, false);
    }
  }

  void JsonObjectWriter<h3m::ObeliskSvg>::operator()(FieldsWriter& out, const h3m::ObeliskSvg& obelisk) const
  {
    using Fields = h3m::FieldNames<h3m::ObeliskSvg>;
    out.writeField(Fields::kVisitedBy, obelisk.visited_by);
  }

  void JsonObjectWriter<h3m::QuestGuardSvg>::operator()(FieldsWriter& out,
                                                          const h3m::QuestGuardSvg& quest_guard) const
  {
    using Fields = h3m::FieldNames<h3m::QuestGuardSvg>;
    out.writeField(Fields::kQuest, quest_guard.quest);
    out.writeField(Fields::kVisitedBy, quest_guard.visited_by);
  }

  void JsonObjectWriter<h3m::SeersHutSvg>::operator()(FieldsWriter& out, const h3m::SeersHutSvg& seers_hut) const
  {
    using Fields = h3m::FieldNames<h3m::SeersHutSvg>;
    out.writeField(Fields::kQuest, seers_hut.quest);
    out.writeField(Fields::kReward, seers_hut.reward);
    out.writeField(Fields::kUnknown1, seers_hut.unknown1);
    out.writeField(Fields::kVisitedBy, seers_hut.visited_by);
    out.writeField(Fields::kUnknown2, seers_hut.unknown2);
  }

  void JsonObjectWriter<h3m::SignSvg>::operator()(FieldsWriter& out, const h3m::SignSvg& sign) const
  {
    using Fields = h3m::FieldNames<h3m::SignSvg>;
    out.writeField(Fields::kMessage, sign.message);
    out.writeField(Fields::kIsCustom, sign.is_custom);
  }

  void JsonObjectWriter<h3m::TimedEventSvg>::operator()(FieldsWriter& out,
                                                        const h3m::TimedEventSvg& event) const
  {
    using Fields = h3m::FieldNames<h3m::TimedEventSvg>;
    out.writeField(Fields::kMessage, event.message);
    out.writeField(Fields::kResources, event.resources);
    out.writeField(Fields::kAffectedPlayers, event.affected_players);
    out.writeField(Fields::kAppliesToHuman, event.applies_to_human);
    out.writeField(Fields::kAppliesToComputer, event.applies_to_computer);
    out.writeField(Fields::kDayOfFirstOccurence, event.day_of_first_occurence);
    out.writeField(Fields::kRepeatAfterDays, event.repeat_after_days);
  }

  void JsonObjectWriter<h3m::TownEventSvg>::operator()(FieldsWriter& out, const h3m::TownEventSvg& event) const
  {
    using Fields = h3m::FieldNames<h3m::TownEventSvg>;
    JsonObjectWriter<h3m::TimedEventSvg>{}(out, event);
    out.writeField(Fields::kUnknown1, event.unknown1);
    out.writeField(Fields::kBuildings, event.buildings);
    out.writeField(Fields::kUnknown2, event.unknown2);
    out.writeField(Fields::kCreatures, event.creatures);
  }

  void JsonObjectWriter<h3m::TroopsSvg>::operator()(FieldsWriter& out, const h3m::TroopsSvg& troops) const
  {
    using Fields = h3m::FieldNames<h3m::TroopsSvg>;
    out.writeField(Fields::kCreatureTypes, troops.creature_types);
    out.writeField(Fields::kCreatureCounts, troops.creature_counts);
  }

  void JsonObjectWriter<h3m::ObjectPropertiesTables>::operator()(FieldsWriter& out,
                                                                 const h3m::ObjectPropertiesTables& tables) const
  {
    using Fields = h3m::FieldNames<h3m::ObjectPropertiesTables>;
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
