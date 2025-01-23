#pragma once

#include <h3mtxt/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/SecondarySkill.h>

namespace h3m
{
  template<>
  struct H3MWriter<SecondarySkill>
  {
    void operator()(std::ostream& stream, const SecondarySkill& secondary_skill) const
    {
      writeData(stream, secondary_skill.type);
      writeData(stream, secondary_skill.level);
    }
  };
}
