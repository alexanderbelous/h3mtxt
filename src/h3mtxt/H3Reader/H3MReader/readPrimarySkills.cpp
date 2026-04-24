#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>

namespace h3m
{
  PrimarySkills H3MReader::readPrimarySkills() const
  {
    PrimarySkills primary_skills;
    for (std::int8_t& skill : primary_skills.data)
    {
      skill = readInt<std::int8_t>();
    }
    return primary_skills;
  }
}
