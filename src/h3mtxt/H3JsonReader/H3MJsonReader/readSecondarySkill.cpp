#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/SecondarySkill.h>

namespace h3json
{
  template<>
  h3m::SecondarySkill JsonReader2<h3m::SecondarySkill>::operator()() const
  {
    using Fields = FieldNames<h3m::SecondarySkill>;
    h3m::SecondarySkill skill;
    readField(Fields::kType, skill.type);
    readField(Fields::kLevel, skill.level);
    return skill;
  }
}
