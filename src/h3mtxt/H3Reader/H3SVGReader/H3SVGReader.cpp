#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>

#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>
#include <h3mtxt/Map/Utils/SpriteTilesBitmask.h>
#include <h3mtxt/Map/CreatureStack.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>
#include <h3mtxt/Map/SecondarySkill.h>

#include <cstdint>

namespace h3svg
{
  Coordinates H3SVGReader::readCoordinates() const
  {
    return h3m::H3MReader{stream_}.readCoordinates();
  }

  CreatureStack H3SVGReader::readCreatureStack() const
  {
    return h3m::H3MReader{stream_}.readCreatureStack();
  }

  CustomHero H3SVGReader::readCustomHero() const
  {
    return h3m::H3MReader{stream_}.readCustomHero();
  }

  PrimarySkills H3SVGReader::readPrimarySkills() const
  {
    return h3m::H3MReader{stream_}.readPrimarySkills();
  }

  Resources H3SVGReader::readResources() const
  {
    return h3m::H3MReader{stream_}.readResources();
  }

  SecondarySkill H3SVGReader::readSecondarySkill() const
  {
    return h3m::H3MReader{stream_}.readSecondarySkill();
  }

  SpriteTilesBitmask H3SVGReader::readSpriteTilesBitmask() const
  {
    return h3m::H3MReader{stream_}.readSpriteTilesBitmask();
  }

  Teams H3SVGReader::readTeams() const
  {
    return h3m::H3MReader{stream_}.readTeams();
  }
}
