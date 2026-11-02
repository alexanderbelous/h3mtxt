#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/HeroSettings.h>

namespace h3json
{
  template<>
  h3m::HeroSettings JsonReader2<h3m::HeroSettings>::operator()() const
  {
    using Fields = FieldNames<h3m::HeroSettings>;
    h3m::HeroSettings settings;
    readField(Fields::kExperience, settings.experience);
    readField(Fields::kSecondarySkills, settings.secondary_skills);
    readField(Fields::kArtifacts, settings.artifacts);
    readField(Fields::kBiography, settings.biography);
    readField(Fields::kGender, settings.gender);
    readField(Fields::kSpells, settings.spells);
    readField(Fields::kPrimarySkills, settings.primary_skills);
    return settings;
  }
}
