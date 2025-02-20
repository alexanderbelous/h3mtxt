#include <h3mtxt/H3MWriter/H3Writer.h>
#include <h3mtxt/H3MWriter/Utils.h>
#include <h3mtxt/Map/SecondarySkill.h>

namespace h3m
{
  void H3Writer<SecondarySkill>::operator()(std::ostream& stream, const SecondarySkill& secondary_skill) const
  {
    writeData(stream, secondary_skill.type);
    writeData(stream, secondary_skill.level);
  }
}
