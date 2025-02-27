#include <h3mtxt/H3MJsonReader/Utils.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/PrimarySkills.h>

namespace h3m::H3JsonReader_NS
{
  PrimarySkills JsonReader<PrimarySkills>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<PrimarySkills>;
    PrimarySkills skills;
    readField(skills.attack, value, Fields::kAttack);
    readField(skills.defense, value, Fields::kDefense);
    readField(skills.spell_power, value, Fields::kSpellPower);
    readField(skills.knowledge, value, Fields::kKnowledge);
    return skills;
  }
}
