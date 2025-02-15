#pragma once

#include <h3mtxt/Campaign/StartingBonus.h>

#include <iosfwd>

namespace h3m
{
  StartingBonus readStartingBonus(std::istream& stream);
}
