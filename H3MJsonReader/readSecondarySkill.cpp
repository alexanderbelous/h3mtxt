#include <h3mtxt/H3MJsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/SecondarySkill.h>

namespace h3m
{
  SecondarySkill JsonReader<SecondarySkill>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<SecondarySkill>;
    SecondarySkill skill;
    readField(skill.type, value, Fields::kType);
    readField(skill.level, value, Fields::kLevel);
    return skill;
  }
}
