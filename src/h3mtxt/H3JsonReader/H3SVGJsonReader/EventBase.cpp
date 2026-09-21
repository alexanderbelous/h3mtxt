#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/EventBase.h>

namespace h3json
{
  template<>
  h3svg::Guardians
  JsonReader<h3svg::Guardians>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::Guardians>;
    h3svg::Guardians guardians;
    readField(guardians.message, value, Fields::kMessage);
    readField(guardians.creatures, value, Fields::kCreatures);
    return guardians;
  }

  template<>
  h3svg::EventBase
  JsonReader<h3svg::EventBase>::operator()(const Json::Value& value) const
  {
    using Fields = h3json::FieldNames<h3svg::EventBase>;
    h3svg::EventBase event;
    readField(event.guardians, value, Fields::kGuardians);
    readField(event.experience, value, Fields::kExperience);
    readField(event.spell_points, value, Fields::kSpellPoints);
    readField(event.morale, value, Fields::kMorale);
    readField(event.luck, value, Fields::kLuck);
    readField(event.resources, value, Fields::kResources);
    readField(event.primary_skills, value, Fields::kPrimarySkills);
    readField(event.secondary_skills, value, Fields::kSecondarySkills);
    readField(event.artifacts, value, Fields::kArtifacts);
    readField(event.spells, value, Fields::kSpells);
    readField(event.creatures, value, Fields::kCreatures);
    return event;
  }
}
