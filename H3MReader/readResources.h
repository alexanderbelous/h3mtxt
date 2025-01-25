#pragma once

#include <h3mtxt/Map/Resources.h>
#include <h3mtxt/H3MReader/Utils.h>

#include <iosfwd>

namespace h3m
{
  template<class T>
  Resources<T> readResources(std::istream& stream)
  {
    Resources<T> resources;
    for (T& amount : resources.data)
    {
      amount = readInt<T>(stream);
    }
    return resources;
  }
}
