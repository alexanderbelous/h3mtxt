#pragma once

#include <h3mtxt/H3MWriter/H3MWriter.h>
#include <h3mtxt/Map/ObjectAttributes.h>

namespace h3m
{
  template<>
  struct H3MWriter<ObjectAttributes>
  {
    void operator()(std::ostream& stream, const ObjectAttributes& value) const
    {
      writeData(stream, value.def);
      writeData(stream, value.passability);
      writeData(stream, value.actionability);
      writeData(stream, value.allowed_landscapes);
      writeData(stream, value.landscape_group);
      writeData(stream, value.object_class);
      writeData(stream, value.object_number);
      writeData(stream, value.object_group);
      writeData(stream, value.is_ground);
      writeData(stream, value.unknown);
    }
  };
}
