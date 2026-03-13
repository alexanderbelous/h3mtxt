#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/SecondarySkill.h>

namespace h3m
{
  SecondarySkill H3MReader::readSecondarySkill() const
  {
    SecondarySkill secondary_skill;
    secondary_skill.type = readEnum<SecondarySkillType>();
    secondary_skill.level = readInt<std::uint8_t>();
    return secondary_skill;
  }
}
