#include <h3mtxt/H3MJsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/HeroSettings.h>

namespace h3m
{
  HeroSettings JsonReader<HeroSettings>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<HeroSettings>;
    HeroSettings settings;
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
