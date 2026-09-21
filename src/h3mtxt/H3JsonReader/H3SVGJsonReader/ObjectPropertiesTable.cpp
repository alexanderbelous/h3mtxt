#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/ObjectPropertiesTables.h>

#include <stdexcept>

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
    throw std::logic_error("JsonReader<h3svg::Boat>: Not implemented.");
  }

  template<>
  h3svg::Dwelling
  JsonReader<h3svg::Dwelling>::operator()(const Json::Value& value) const
  {
    throw std::logic_error("JsonReader<h3svg::Dwelling>: Not implemented.");
  }

  template<>
  h3svg::Garrison
  JsonReader<h3svg::Garrison>::operator()(const Json::Value& value) const
  {
    throw std::logic_error("JsonReader<h3svg::Garrison>: Not implemented.");
  }

  template<>
  h3svg::Mine
  JsonReader<h3svg::Mine>::operator()(const Json::Value& value) const
  {
    throw std::logic_error("JsonReader<h3svg::Mine>: Not implemented.");
  }

  template<>
  h3svg::Monster
  JsonReader<h3svg::Monster>::operator()(const Json::Value& value) const
  {
    throw std::logic_error("JsonReader<h3svg::Monster>: Not implemented.");
  }

  template<>
  h3svg::Obelisk
  JsonReader<h3svg::Obelisk>::operator()(const Json::Value& value) const
  {
    throw std::logic_error("JsonReader<h3svg::Obelisk>: Not implemented.");
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
    throw std::logic_error("JsonReader<h3svg::QuestGuard>: Not implemented.");
  }

  template<>
  h3svg::SeersHut
  JsonReader<h3svg::SeersHut>::operator()(const Json::Value& value) const
  {
    throw std::logic_error("JsonReader<h3svg::SeersHut>: Not implemented.");
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
    throw std::logic_error("JsonReader<h3svg::TimedEvent>: Not implemented.");
  }

  template<>
  h3svg::TownEvent
  JsonReader<h3svg::TownEvent>::operator()(const Json::Value& value) const
  {
    throw std::logic_error("JsonReader<h3svg::TownEvent>: Not implemented.");
  }
}
