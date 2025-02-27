#include <h3mtxt/H3MJsonReader/H3JsonReader.h>
#include <h3mtxt/Map/GlobalEvent.h>

namespace h3m::H3JsonReader_NS
{
  GlobalEvent JsonReader<GlobalEvent>::operator()(const Json::Value& value) const
  {
    GlobalEvent event;
    readTimedEventBase(event, value);
    return event;
  }
}
