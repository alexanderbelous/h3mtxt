#pragma once

#include <h3mtxt/H3MJsonReader/JsonReader.h>
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
      settings.experience = readOptionalField<std::uint32_t>(value, Fields::kExperience);
      //settings.secondary_skills = readOptionalField<std::vector<SecondarySkill>>(value, Fields::kSecondarySkills);
      //settings.artifacts = readOptionalField<HeroArtifacts>(value, Fields::kArtifacts);
      settings.biography = readOptionalField<std::string>(value, Fields::kBiography);
      settings.gender = readField<Gender>(value, Fields::kGender);
      //settings.spells = readOptionalField<SpellsBitmask>(value, Fields::kSpells);
      //settings.primary_skills = readOptionalField<PrimarySkills>(value, Fields::kPrimarySkills);
      return settings;
    }
  };
}
