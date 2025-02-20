#include <h3mtxt/H3MReader/H3Reader.h>
#include <h3mtxt/H3MReader/Utils.h>
#include <h3mtxt/Map/PrimarySkills.h>

namespace h3m::H3Reader_NS
{
  PrimarySkills readPrimarySkills(std::istream& stream)
  {
    PrimarySkills primary_skills;
    primary_skills.attack = readInt<std::int8_t>(stream);
    primary_skills.defense = readInt<std::int8_t>(stream);
    primary_skills.spell_power = readInt<std::int8_t>(stream);
    primary_skills.knowledge = readInt<std::int8_t>(stream);
    return primary_skills;
  }
}
