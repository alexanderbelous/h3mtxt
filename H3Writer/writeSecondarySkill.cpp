#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/H3Writer/Utils.h>
#include <h3mtxt/Map/SecondarySkill.h>

namespace h3m::H3Writer_NS
{
  void H3Writer<SecondarySkill>::operator()(std::ostream& stream, const SecondarySkill& secondary_skill) const
  {
    writeData(stream, secondary_skill.type);
    writeData(stream, secondary_skill.level);
  }
}
