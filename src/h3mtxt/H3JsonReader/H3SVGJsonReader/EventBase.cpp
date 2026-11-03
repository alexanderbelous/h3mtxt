#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/JsonCommon/FieldNamesH3SVG.h>
#include <h3mtxt/SavedGame/EventBase.h>

namespace h3json
{
  template<>
  h3svg::Guardians JsonReader2<h3svg::Guardians>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::Guardians>;
    h3svg::Guardians guardians;
    readField(Fields::kMessage, guardians.message);
    readField(Fields::kCreatures, guardians.creatures);
    return guardians;
  }

  template<>
  h3svg::EventBase JsonReader2<h3svg::EventBase>::operator()() const
  {
    using Fields = h3json::FieldNames<h3svg::EventBase>;
    h3svg::EventBase event;
    readField(Fields::kGuardians, event.guardians);
    readField(Fields::kExperience, event.experience);
    readField(Fields::kSpellPoints, event.spell_points);
    readField(Fields::kMorale, event.morale);
    readField(Fields::kLuck, event.luck);
    readField(Fields::kResources, event.resources);
    readField(Fields::kPrimarySkills, event.primary_skills);
    readField(Fields::kSecondarySkills, event.secondary_skills);
    readField(Fields::kArtifacts, event.artifacts);
    readField(Fields::kSpells, event.spells);
    readField(Fields::kCreatures, event.creatures);
    return event;
  }
}
