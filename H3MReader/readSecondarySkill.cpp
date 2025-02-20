#include <h3mtxt/H3MReader/H3Reader.h>
#include <h3mtxt/H3MReader/Utils.h>
#include <h3mtxt/Map/SecondarySkill.h>

namespace h3m
{
  SecondarySkill readSecondarySkill(std::istream& stream)
  {
    SecondarySkill secondary_skill;
    secondary_skill.type = readEnum<SecondarySkillType>(stream);
    secondary_skill.level = readInt<std::uint8_t>(stream);
    return secondary_skill;
  }
}
