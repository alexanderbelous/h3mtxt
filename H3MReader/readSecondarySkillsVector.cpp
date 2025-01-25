#include <h3mtxt/H3MReader/readSecondarySkillsVector.h>

#include <h3mtxt/H3MReader/Utils.h>

namespace h3m
{
  SecondarySkill readSecondarySkill(std::istream& stream)
  {
    SecondarySkill secondary_skill;
    secondary_skill.type = readEnum<SecondarySkillType>(stream);
    secondary_skill.level = readInt<std::uint8_t>(stream);
    return secondary_skill;
  }

  namespace Detail_NS
  {
    std::vector<SecondarySkill> readSecondarySkillsVectorImpl(std::istream& stream, IntegerWidth sizeof_num_elements)
    {
      const std::uintmax_t num_secondary_skills = readUintImpl(stream, sizeof_num_elements);
      std::vector<SecondarySkill> secondary_skills;
      secondary_skills.reserve(num_secondary_skills);
      for (std::uintmax_t i = 0; i < num_secondary_skills; ++i)
      {
        secondary_skills.push_back(readSecondarySkill(stream));
      }
      return secondary_skills;
    }
  }
}