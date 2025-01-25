#pragma once

#include <h3mtxt/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/SecondarySkillsBitmask.h>

namespace h3m
{
  template<>
  struct H3MWriter<SecondarySkillsBitmask>
  {
    void operator()(std::ostream& stream, const SecondarySkillsBitmask& value) const
    {
      writeData(stream, value.bitset);
    }
  };
}
