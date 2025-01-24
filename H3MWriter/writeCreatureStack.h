#pragma once

#include <h3mtxt/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/CreatureStack.h>

namespace h3m
{
  template<>
  struct H3MWriter<CreatureStack>
  {
    void operator()(std::ostream& stream, const CreatureStack& value) const
    {
      writeData(stream, value.type);
      writeData(stream, value.count);
    }
  };
}
