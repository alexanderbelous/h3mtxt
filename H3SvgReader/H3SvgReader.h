#pragma once

#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/SavedGame/SavedGameFwd.h>

#include <iosfwd>

// API for reading various structures from an *UNCOMPRESSED* saved game file (i.e. .GM1, .GM2, ...).
namespace h3m::H3SvgReader_NS
{
  BlackMarket readBlackMarket(std::istream& stream);

  Coordinates readCoordinates(std::istream& stream);

  MapBasicInfo readMapBasicInfoSvg(std::istream& stream);

  ObjectTemplateSvg readObjectTemplateSvg(std::istream& stream);

  PlayerSpecsSvg readPlayerSpecsSvg(std::istream& stream);

  RumorSvg readRumorSvg(std::istream& stream);

  SavedGame readSavedGame(std::istream& stream);

  StartingHero readStartingHeroSvg(std::istream& stream);

  TileSvg readTileSvg(std::istream& stream);
}