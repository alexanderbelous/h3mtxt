#pragma once

#include <h3mtxt/Map/MapFwd.h>

#include <json/forwards.h>

namespace h3m::H3MJsonReader_NS
{
  void readTimedEventBase(TimedEventBase& event, const Json::Value& value);
}
