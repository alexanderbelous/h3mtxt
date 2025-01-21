#include <h3mtxt/H3MReader/readCreatureStack.h>

#include <h3mtxt/H3MReader/Utils.h>

namespace h3m
{
  CreatureStack readCreatureStack(std::istream& stream)
  {
    CreatureStack creature_stack;
    creature_stack.type = readEnum<CreatureType>(stream);
    creature_stack.count = readUint<std::uint16_t>(stream);
    return creature_stack;
  }
}
