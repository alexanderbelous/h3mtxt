#pragma once

#include <h3mtxt/Map/HeroArtifacts.h>

#include <iosfwd>

namespace h3m
{
  HeroArtifacts readHeroArtifacts(std::istream& stream);
}
