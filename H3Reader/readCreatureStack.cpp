#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/Map/CreatureStack.h>

namespace h3m::H3Reader_NS
{
  CreatureStack readCreatureStack(std::istream& stream)
  {
    CreatureStack creature_stack;
    creature_stack.type = readEnum<CreatureType>(stream);
    creature_stack.count = readInt<std::int16_t>(stream);
    return creature_stack;
  }
}
