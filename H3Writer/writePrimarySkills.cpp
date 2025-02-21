#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/H3Writer/Utils.h>
#include <h3mtxt/Map/PrimarySkills.h>

namespace h3m::H3Writer_NS
{
  void H3Writer<PrimarySkills>::operator()(std::ostream& stream, const PrimarySkills& primary_skills) const
  {
    writeData(stream, primary_skills.attack);
    writeData(stream, primary_skills.defense);
    writeData(stream, primary_skills.spell_power);
    writeData(stream, primary_skills.knowledge);
  }
}
