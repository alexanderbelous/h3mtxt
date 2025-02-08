#pragma once

#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/H3MJsonReader/readHeroArtifacts.h>
#include <h3mtxt/H3MJsonReader/readPrimarySkills.h>
#include <h3mtxt/H3MJsonReader/readSecondarySkill.h>
#include <h3mtxt/H3MJsonReader/readSpellsBitmask.h>
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
      readField(settings.artifacts, value, Fields::kArtifacts);
      readField(settings.biography, value, Fields::kBiography);
      readField(settings.gender, value, Fields::kGender);
      readField(settings.spells, value, Fields::kSpells);
      readField(settings.primary_skills, value, Fields::kPrimarySkills);
      return settings;
    }
  };
}
