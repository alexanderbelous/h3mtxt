#include <h3mtxt/H3MWriter/H3Writer.h>
#include <h3mtxt/H3MWriter/Utils.h>
#include <h3mtxt/Map/CreatureStack.h>

namespace h3m
{
  void H3MWriter<CreatureStack>::operator()(std::ostream& stream, const CreatureStack& value) const
  {
    writeData(stream, value.type);
    writeData(stream, value.count);
  }
}
