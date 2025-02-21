#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/Map/SecondarySkill.h>

namespace h3m::H3Reader_NS
{
  SecondarySkill readSecondarySkill(std::istream& stream)
  {
    SecondarySkill secondary_skill;
    secondary_skill.type = readEnum<SecondarySkillType>(stream);
    secondary_skill.level = readInt<std::uint8_t>(stream);
    return secondary_skill;
  }
}
