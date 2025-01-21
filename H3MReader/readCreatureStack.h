#pragma once

#include <h3mtxt/Map/CreatureStack.h>

#include <iosfwd>

namespace h3m
{
  CreatureStack readCreatureStack(std::istream& stream);
}
