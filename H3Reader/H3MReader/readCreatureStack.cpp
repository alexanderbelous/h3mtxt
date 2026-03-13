#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/CreatureStack.h>

namespace h3m
{
  CreatureStack H3MReader::readCreatureStack() const
  {
    CreatureStack creature_stack;
    creature_stack.type = readEnum<CreatureType>();
    creature_stack.count = readInt<std::int16_t>();
    return creature_stack;
  }
}
