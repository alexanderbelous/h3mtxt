#pragma once

#include <h3mtxt/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/SpellsBitmask.h>

namespace h3m
{
  template<>
  struct H3MWriter<SpellsBitmask>
  {
    void operator()(std::ostream& stream, const SpellsBitmask& value) const
    {
      writeData(stream, value.bitset);
    }
  };
}
