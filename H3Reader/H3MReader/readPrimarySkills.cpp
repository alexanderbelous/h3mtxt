#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/PrimarySkills.h>

namespace h3m
{
  PrimarySkills H3MReader::readPrimarySkills() const
  {
    PrimarySkills primary_skills;
    primary_skills.attack = readInt<std::int8_t>();
    primary_skills.defense = readInt<std::int8_t>();
    primary_skills.spell_power = readInt<std::int8_t>();
    primary_skills.knowledge = readInt<std::int8_t>();
    return primary_skills;
  }
}
