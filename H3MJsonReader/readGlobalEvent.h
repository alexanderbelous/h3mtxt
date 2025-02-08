#pragma once

#include <h3mtxt/H3MJsonReader/JsonReader.h>
#include <h3mtxt/H3MJsonReader/readTimedEventBase.h>
#include <h3mtxt/Map/GlobalEvent.h>

namespace h3m
{
  template<>
  struct JsonReader<GlobalEvent>
  {
    GlobalEvent operator()(const Json::Value& value) const
    {
      GlobalEvent event;
      H3MJsonReader_NS::readTimedEventBase(event, value);
      return event;
    }
  };
}
