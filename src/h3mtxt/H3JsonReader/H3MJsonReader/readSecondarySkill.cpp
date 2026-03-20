#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/Map/SecondarySkill.h>

namespace h3json
{
  h3m::SecondarySkill JsonReader<h3m::SecondarySkill>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::SecondarySkill>;
    h3m::SecondarySkill skill;
    readField(skill.type, value, Fields::kType);
    readField(skill.level, value, Fields::kLevel);
    return skill;
  }
}
