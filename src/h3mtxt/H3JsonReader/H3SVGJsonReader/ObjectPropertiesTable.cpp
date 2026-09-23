#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/ObjectPropertiesTables.h>

namespace h3json
{
  template<>
  h3svg::Artifact
  JsonReader<h3svg::Artifact>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::Artifact>;
    h3svg::Artifact artifact;
    readField(artifact.guardians, value, Fields::kGuardians);
    return artifact;
  }

  template<>
  h3svg::Boat
  JsonReader<h3svg::Boat>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::Boat>;
    h3svg::Boat boat;
    readField(boat.exists, value, Fields::kExists);
    readField(boat.id, value, Fields::kId);
    readField(boat.object_sublcass, value, Fields::kObjectSubclass);
    readField(boat.orientation, value, Fields::kDirection);
    readField(boat.owner, value, Fields::kOwner);
    readField(boat.owner_hero, value, Fields::kOwnerHero);
    readField(boat.is_occupied, value, Fields::kIsOccupied);
    readField(boat.x, value, Fields::kX);
    readField(boat.y, value, Fields::kY);
    readField(boat.z, value, Fields::kZ);
    readField(boat.is_visible, value, Fields::kIsVisible);
    readField(boat.coordinates_packed, value, Fields::kCoordinatesPacked);
    readField(boat.unknown, value, Fields::kUnknown);
    return boat;
  }

  template<>
  h3svg::Dwelling
  JsonReader<h3svg::Dwelling>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::Dwelling>;
    h3svg::Dwelling dwelling;
    readField(dwelling.owner, value, Fields::kOwner);
    readField(dwelling.object_class, value, Fields::kObjectClass);
    readField(dwelling.object_subclass, value, Fields::kObjectSubclass);
    readField(dwelling.creature_types, value, Fields::kCreatureTypes);
    readField(dwelling.creature_counts, value, Fields::kCreatureCounts);
    readField(dwelling.coordinates, value, Fields::kCoordinates);
    readField(dwelling.guardians, value, Fields::kGuardians);
    readField(dwelling.unknown, value, Fields::kUnknown);
    return dwelling;
  }

  template<>
  h3svg::Garrison
  JsonReader<h3svg::Garrison>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::Garrison>;
    h3svg::Garrison garrison;
    readField(garrison.owner, value, Fields::kOwner);
    readField(garrison.creatures, value, Fields::kCreatures);
    readField(garrison.coordinates, value, Fields::kCoordinates);
    readField(garrison.can_remove_units, value, Fields::kCanRemoveUnits);
    return garrison;
  }

  template<>
  h3svg::Mine
  JsonReader<h3svg::Mine>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::Mine>;
    h3svg::Mine mine;
    readField(mine.owner, value, Fields::kOwner);
    readField(mine.unknown, value, Fields::kUnknown);
    readField(mine.creatures, value, Fields::kCreatures);
    readField(mine.coordinates, value, Fields::kCoordinates);
    return mine;
  }

  template<>
  h3svg::Monster
  JsonReader<h3svg::Monster>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::Monster>;
    h3svg::Monster monster;
    readField(monster.message, value, Fields::kMessage);
    readField(monster.resources, value, Fields::kResources);
    readField(monster.artifact, value, Fields::kArtifact);
    return monster;
  }

  template<>
  h3svg::Obelisk
  JsonReader<h3svg::Obelisk>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::Obelisk>;
    h3svg::Obelisk obelisk;
    readField(obelisk.visited_by, value, Fields::kVisitedBy);
    return obelisk;
  }

  template<>
  h3svg::ObjectPropertiesTables
  JsonReader<h3svg::ObjectPropertiesTables>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::ObjectPropertiesTables>;
    h3svg::ObjectPropertiesTables tables;
    readField(tables.events_and_pandoras_boxes, value, Fields::kEventsAndPandorasBoxes);
    readField(tables.artifacts_and_spell_scrolls, value, Fields::kArtifactsAndSpellScrolls);
    readField(tables.monsters, value, Fields::kMonsters);
    readField(tables.seers_huts, value, Fields::kSeersHuts);
    readField(tables.quest_guards, value, Fields::kQuestGuards);
    readField(tables.global_events, value, Fields::kGlobalEvents);
    readField(tables.town_events, value, Fields::kTownEvents);
    readField(tables.signs_and_ocean_bottles, value, Fields::kSignsAndOceanBottles);
    readField(tables.mines_and_lighthouses, value, Fields::kMinesAndLighthouses);
    readField(tables.dwellings, value, Fields::kDwellings);
    readField(tables.garrisons, value, Fields::kGarrisons);
    readField(tables.boats, value, Fields::kBoats);
    readField(tables.num_obelisks, value, Fields::kNumObelisks);
    readField(tables.obelisks, value, Fields::kObelisks);
    return tables;
  }

  template<>
  h3svg::QuestGuard
  JsonReader<h3svg::QuestGuard>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::QuestGuard>;
    h3svg::QuestGuard quest_guard;
    readField(quest_guard.quest, value, Fields::kQuest);
    readField(quest_guard.visited_by, value, Fields::kVisitedBy);
    return quest_guard;
  }

  template<>
  h3svg::SeersHut
  JsonReader<h3svg::SeersHut>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::SeersHut>;
    h3svg::SeersHut seers_hut;
    readField(seers_hut.quest, value, Fields::kQuest);
    readField(seers_hut.reward, value, Fields::kReward);
    readField(seers_hut.reserved, value, Fields::kReserved);
    readField(seers_hut.visited_by, value, Fields::kVisitedBy);
    readField(seers_hut.name, value, Fields::kName);
    return seers_hut;
  }

  template<>
  h3svg::Sign
  JsonReader<h3svg::Sign>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::Sign>;
    h3svg::Sign sign;
    readField(sign.message, value, Fields::kMessage);
    readField(sign.is_custom, value, Fields::kIsCustom);
    return sign;
  }

  template<>
  h3svg::TimedEvent
  JsonReader<h3svg::TimedEvent>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::TimedEvent>;
    h3svg::TimedEvent event;
    readField(event.message, value, Fields::kMessage);
    readField(event.resources, value, Fields::kResources);
    readField(event.affected_players, value, Fields::kAffectedPlayers);
    readField(event.applies_to_human, value, Fields::kAppliesToHuman);
    readField(event.applies_to_computer, value, Fields::kAppliesToComputer);
    readField(event.day_of_first_occurence, value, Fields::kDayOfFirstOccurence);
    readField(event.repeat_after_days, value, Fields::kRepeatAfterDays);
    return event;
  }

  template<>
  h3svg::TownEvent
  JsonReader<h3svg::TownEvent>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::TownEvent>;
    h3svg::TownEvent event{ fromJson<h3svg::TimedEvent>(value) };
    readField(event.town_id, value, Fields::kTownId);
    readField(event.buildings, value, Fields::kBuildings);
    readField(event.reserved, value, Fields::kReserved);
    readField(event.creatures, value, Fields::kCreatures);
    return event;
  }
}
