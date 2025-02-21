#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/Map/GlobalEvent.h>

namespace h3m::H3Writer_NS
{
  void H3Writer<GlobalEvent>::operator()(std::ostream& stream, const GlobalEvent& global_event) const
  {
    writeTimedEventBase(stream, global_event);
  }
}
