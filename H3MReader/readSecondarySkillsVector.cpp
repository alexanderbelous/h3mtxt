#include <h3mtxt/H3MReader/readSecondarySkillsVector.h>

#include <h3mtxt/H3MReader/Utils.h>

namespace h3m
{
  namespace Detail_NS
  {
    static SecondarySkill readSecondarySkill(std::istream& stream)
    {
      SecondarySkill secondary_skill;
      secondary_skill.type = readEnum<SecondarySkillType>(stream);
      secondary_skill.level = readUint8(stream);
      return secondary_skill;
    }

    std::vector<SecondarySkill> readSecondarySkillsVectorImpl(std::istream& stream, unsigned int num_bytes)
    {
      const std::uintmax_t num_secondary_skills = readUintImpl(stream, num_bytes);
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