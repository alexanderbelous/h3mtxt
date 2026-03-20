#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/HeroSettings.h>

namespace h3json
{
  h3m::HeroSettings JsonReader<h3m::HeroSettings>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::HeroSettings>;
    h3m::HeroSettings settings;
    readField(settings.experience, value, Fields::kExperience);
    readField(settings.secondary_skills, value, Fields::kSecondarySkills);
    readField(settings.artifacts, value, Fields::kArtifacts);
    readField(settings.biography, value, Fields::kBiography);
    readField(settings.gender, value, Fields::kGender);
    readField(settings.spells, value, Fields::kSpells);
    readField(settings.primary_skills, value, Fields::kPrimarySkills);
    return settings;
  }
}
