#pragma once

#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <iosfwd>

// API for reading various structures from an *UNCOMPRESSED* saved game file (i.e. .GM1, .GM2, ...).
namespace h3m::H3SvgReader_NS
{
  MapBasicInfo readMapBasicInfo(std::istream& stream);

  PlayerSpecsSvg readPlayerSpecsSvg(std::istream& stream);

  SavedGame readSavedGame(std::istream& stream);

  StartingHero readStartingHero(std::istream& stream);
}