#pragma once

#include <h3mtxt/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/Resources.h>

namespace h3m
{
  template<>
  struct H3MWriter<Resources>
  {
    void operator()(std::ostream& stream, const Resources& resources) const
    {
      writeData(stream, resources.data);
    }
  };
}
