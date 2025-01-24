#pragma once

#include <h3mtxt/H3MWriter/writeTimedEventBase.h>
#include <h3mtxt/Map/GlobalEvent.h>

namespace h3m
{
  template<>
  struct H3MWriter<GlobalEvent>
  {
    void operator()(std::ostream& stream, const GlobalEvent& global_event) const
    {
      writeTimedEventBase(stream, global_event);
    }
  };
}
