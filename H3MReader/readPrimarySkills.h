#pragma once

#include <h3mtxt/Map/PrimarySkills.h>

#include <iosfwd>

namespace h3m
{
  PrimarySkills readPrimarySkills(std::istream& stream);
}
