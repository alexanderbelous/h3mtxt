#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/H3Writer/Utils.h>
#include <h3mtxt/Map/CreatureStack.h>

namespace h3m
{
  void H3Writer<CreatureStack>::operator()(std::ostream& stream, const CreatureStack& value) const
  {
    writeData(stream, value.type);
    writeData(stream, value.count);
  }
}
