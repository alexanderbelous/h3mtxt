#pragma once

#include <h3mtxt/H3SvgReader/H3ReaderBase.h>
#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/SavedGame/SavedGameFwd.h>

namespace h3m
{
  // API for reading various structures from an *UNCOMPRESSED* saved game file (i.e. .GM1, .GM2, ...).
  //
  // FYI: originally, the functions in this class were declared as global functions. However, making
  // them member functions of a class has a few advantages:
  // 1) It reduces the risk of calling a "wrong" function, i.e. one intended for .h3m files.
  // 2) It doesn't pollute the namespace.
  // 3) It allows omitting the stream parameter.
  class H3SvgReader : public H3ReaderBase
  {
  public:
    // Inherit the constructor from H3ReaderBase.
    using H3ReaderBase::H3ReaderBase;

    ArtifactSvg readArtifact() const;

    BlackMarket readBlackMarket() const;

    EventBaseSvg readEventBase() const;

    GuardiansSvg readGuardians() const;

    MapBasicInfo readMapBasicInfo() const;

    ObjectSvg readObject() const;

    ObjectTemplateSvg readObjectTemplate() const;

    PlayerSpecsSvg readPlayerSpecs() const;

    RumorSvg readRumor() const;

    SavedGame readSavedGame() const;

    StartingHero readStartingHero() const;

    TileSvg readTile() const;

    TroopsSvg readTroops() const;
  };
}
