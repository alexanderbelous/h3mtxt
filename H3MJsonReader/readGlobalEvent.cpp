#include <h3mtxt/H3MJsonReader/H3JsonReader.h>
#include <h3mtxt/Map/GlobalEvent.h>

namespace h3m
{
  GlobalEvent JsonReader<GlobalEvent>::operator()(const Json::Value& value) const
  {
    GlobalEvent event;
    H3MJsonReader_NS::readTimedEventBase(event, value);
    return event;
  }
}
