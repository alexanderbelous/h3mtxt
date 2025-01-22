#pragma once

#include <h3mtxt/Map/VictoryCondition.h>

#include <iosfwd>

namespace h3m
{
  VictoryCondition readVictoryCondition(std::istream& stream);
}
