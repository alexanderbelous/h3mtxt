#include <h3mtxt/H3MWriter/H3Writer.h>
#include <h3mtxt/H3MWriter/Utils.h>
#include <h3mtxt/Map/PrimarySkills.h>

namespace h3m
{
  void H3MWriter<PrimarySkills>::operator()(std::ostream& stream, const PrimarySkills& primary_skills) const
  {
    writeData(stream, primary_skills.attack);
    writeData(stream, primary_skills.defense);
    writeData(stream, primary_skills.spell_power);
    writeData(stream, primary_skills.knowledge);
  }
}
