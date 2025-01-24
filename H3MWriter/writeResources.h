#pragma once

#include <h3mtxt/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/Resources.h>

namespace h3m
{
  template<class T>
  struct H3MWriter<Resources<T>>
  {
    void operator()(std::ostream& stream, const Resources<T>& resources) const
    {
      writeData(stream, resources.data);
    }
  };
}
