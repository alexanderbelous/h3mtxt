#pragma once

#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/H3MJsonReader/readPrimarySkills.h>
#include <h3mtxt/H3MJsonReader/readSecondarySkill.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/HeroSettings.h>

namespace h3m
{
  template<>
  struct JsonReader<HeroSettings>
  {
    HeroSettings operator()(const Json::Value& value) const
    {
      using Fields = FieldNames<HeroSettings>;
      HeroSettings settings;
      readField(settings.experience, value, Fields::kExperience);
      readField(settings.secondary_skills, value, Fields::kSecondarySkills);
      //settings.artifacts = readOptionalField<HeroArtifacts>(value, Fields::kArtifacts);
      readField(settings.biography, value, Fields::kBiography);
      readField(settings.gender, value, Fields::kGender);
      //settings.spells = readOptionalField<SpellsBitmask>(value, Fields::kSpells);
      readField(settings.primary_skills, value, Fields::kPrimarySkills);
      return settings;
    }
  };
}
