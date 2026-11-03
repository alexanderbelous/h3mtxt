#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/ObjectPropertiesTables.h>

namespace h3json
{
  template<>
  h3svg::Artifact JsonReader2<h3svg::Artifact>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::Artifact>;
    h3svg::Artifact artifact;
    readField(Fields::kGuardians, artifact.guardians);
    return artifact;
  }

  template<>
  h3svg::Boat JsonReader2<h3svg::Boat>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::Boat>;
    h3svg::Boat boat;
    readField(Fields::kExists, boat.exists);
    readField(Fields::kId, boat.id);
    readField(Fields::kObjectSubclass, boat.object_sublcass);
    readField(Fields::kDirection, boat.orientation);
    readField(Fields::kOwner, boat.owner);
    readField(Fields::kOwnerHero, boat.owner_hero);
    readField(Fields::kIsOccupied, boat.is_occupied);
    readField(Fields::kX, boat.x);
    readField(Fields::kY, boat.y);
    readField(Fields::kZ, boat.z);
    readField(Fields::kIsVisible, boat.is_visible);
    readField(Fields::kCoordinatesPacked, boat.coordinates_packed);
    readField(Fields::kUnknown, boat.unknown);
    return boat;
  }

  template<>
  h3svg::Dwelling JsonReader2<h3svg::Dwelling>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::Dwelling>;
    h3svg::Dwelling dwelling;
    readField(Fields::kOwner, dwelling.owner);
    readField(Fields::kObjectClass, dwelling.object_class);
    readField(Fields::kObjectSubclass, dwelling.object_subclass);
    readField(Fields::kCreatureTypes, dwelling.creature_types);
    readField(Fields::kCreatureCounts, dwelling.creature_counts);
    readField(Fields::kCoordinates, dwelling.coordinates);
    readField(Fields::kGuardians, dwelling.guardians);
    readField(Fields::kUnknown, dwelling.unknown);
    return dwelling;
  }

  template<>
  h3svg::Garrison JsonReader2<h3svg::Garrison>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::Garrison>;
    h3svg::Garrison garrison;
    readField(Fields::kOwner, garrison.owner);
    readField(Fields::kCreatures, garrison.creatures);
    readField(Fields::kCoordinates, garrison.coordinates);
    readField(Fields::kCanRemoveUnits, garrison.can_remove_units);
    return garrison;
  }

  template<>
  h3svg::MineLighthouse JsonReader2<h3svg::MineLighthouse>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::MineLighthouse>;
    h3svg::MineLighthouse mine;
    readField(Fields::kOwner, mine.owner);
    readField(Fields::kType, mine.type);
    readField(Fields::kIsAbandonedMine, mine.is_abandoned_mine);
    readField(Fields::kCreatures, mine.creatures);
    readField(Fields::kCoordinates, mine.coordinates);
    return mine;
  }

  template<>
  h3svg::Monster JsonReader2<h3svg::Monster>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::Monster>;
    h3svg::Monster monster;
    readField(Fields::kMessage, monster.message);
    readField(Fields::kResources, monster.resources);
    readField(Fields::kArtifact, monster.artifact);
    return monster;
  }

  template<>
  h3svg::Obelisk JsonReader2<h3svg::Obelisk>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::Obelisk>;
    h3svg::Obelisk obelisk;
    readField(Fields::kVisitedBy, obelisk.visited_by);
    return obelisk;
  }

  template<>
  h3svg::ObjectPropertiesTables JsonReader2<h3svg::ObjectPropertiesTables>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::ObjectPropertiesTables>;
    h3svg::ObjectPropertiesTables tables;
    readField(Fields::kEventsAndPandorasBoxes, tables.events_and_pandoras_boxes);
    readField(Fields::kArtifactsAndSpellScrolls, tables.artifacts_and_spell_scrolls);
    readField(Fields::kMonsters, tables.monsters);
    readField(Fields::kSeersHuts, tables.seers_huts);
    readField(Fields::kQuestGuards, tables.quest_guards);
    readField(Fields::kGlobalEvents, tables.global_events);
    readField(Fields::kTownEvents, tables.town_events);
    readField(Fields::kSignsAndOceanBottles, tables.signs_and_ocean_bottles);
    readField(Fields::kMinesAndLighthouses, tables.mines_and_lighthouses);
    readField(Fields::kDwellings, tables.dwellings);
    readField(Fields::kGarrisons, tables.garrisons);
    readField(Fields::kBoats, tables.boats);
    readField(Fields::kNumObelisks, tables.num_obelisks);
    readField(Fields::kObelisks, tables.obelisks);
    return tables;
  }

  template<>
  h3svg::QuestGuard JsonReader2<h3svg::QuestGuard>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::QuestGuard>;
    h3svg::QuestGuard quest_guard;
    readField(Fields::kQuest, quest_guard.quest);
    readField(Fields::kVisitedBy, quest_guard.visited_by);
    return quest_guard;
  }

  template<>
  h3svg::SeersHut JsonReader2<h3svg::SeersHut>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::SeersHut>;
    h3svg::SeersHut seers_hut;
    readField(Fields::kQuest, seers_hut.quest);
    readField(Fields::kReward, seers_hut.reward);
    readField(Fields::kReserved, seers_hut.reserved);
    readField(Fields::kVisitedBy, seers_hut.visited_by);
    readField(Fields::kName, seers_hut.name);
    return seers_hut;
  }

  template<>
  h3svg::Sign JsonReader2<h3svg::Sign>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::Sign>;
    h3svg::Sign sign;
    readField(Fields::kMessage, sign.message);
    readField(Fields::kIsCustom, sign.is_custom);
    return sign;
  }

  template<>
  h3svg::TimedEvent JsonReader2<h3svg::TimedEvent>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::TimedEvent>;
    h3svg::TimedEvent event;
    readField(Fields::kMessage, event.message);
    readField(Fields::kResources, event.resources);
    readField(Fields::kAffectedPlayers, event.affected_players);
    readField(Fields::kAppliesToHuman, event.applies_to_human);
    readField(Fields::kAppliesToComputer, event.applies_to_computer);
    readField(Fields::kDayOfFirstOccurence, event.day_of_first_occurence);
    readField(Fields::kRepeatAfterDays, event.repeat_after_days);
    return event;
  }

  template<>
  h3svg::TownEvent JsonReader2<h3svg::TownEvent>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::TownEvent>;
    h3svg::TownEvent event{ fromJson<h3svg::TimedEvent>(value()) };
    readField(Fields::kTownId, event.town_id);
    readField(Fields::kBuildings, event.buildings);
    readField(Fields::kReserved, event.reserved);
    readField(Fields::kCreatures, event.creatures);
    return event;
  }
}
