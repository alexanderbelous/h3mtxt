#pragma once

#include <h3mtxt/Map/Reward.h>

#include <iosfwd>

namespace h3m
{
  Reward readReward(std::istream& stream);
}
