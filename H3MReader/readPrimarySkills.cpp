#include <h3mtxt/H3MReader/readPrimarySkills.h>

#include <h3mtxt/H3MReader/Utils.h>

namespace h3m
{
  PrimarySkills readPrimarySkills(std::istream& stream)
  {
    PrimarySkills primary_skills;
    primary_skills.attack = readUint8(stream);
    primary_skills.defense = readUint8(stream);
    primary_skills.spell_power = readUint8(stream);
    primary_skills.knowledge = readUint8(stream);
    return primary_skills;
  }
}
