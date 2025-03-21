#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/readSecondarySkillsVector.h>
#include <h3mtxt/H3Reader/Utils.h>

namespace h3m::H3Reader_NS
{
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