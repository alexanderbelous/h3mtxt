#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>

#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>
#include <h3mtxt/Map/Utils/SpriteTilesBitmask.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>
#include <h3mtxt/Map/SecondarySkill.h>
#include <h3mtxt/SavedGame/CoordinatesPacked.h>
#include <h3mtxt/SavedGame/Date.h>

#include <cstdint>

namespace h3svg
{
  Coordinates H3SVGReader::readCoordinates() const
  {
    return h3m::H3MReader{stream_}.readCoordinates();
  }

  CoordinatesPacked H3SVGReader::readCoordinatesPacked() const
  {
    const std::uint32_t data = readInt<std::uint32_t>();
    CoordinatesPacked coordinates;
    coordinates.x = static_cast<std::uint16_t>(data & 0x3FFu);
    coordinates.padding1 = static_cast<std::uint16_t>((data >> 10) & 0x3Fu);
    coordinates.y = static_cast<std::uint16_t>((data >> 16) & 0x3FFu);
    coordinates.z = static_cast<std::uint16_t>((data >> 26) & 1u);
    coordinates.padding2 = static_cast<std::uint16_t>(data >> 27);
    return coordinates;
  }

  CustomHero H3SVGReader::readCustomHero() const
  {
    return h3m::H3MReader{stream_}.readCustomHero();
  }

  Date H3SVGReader::readDate() const
  {
    Date date;
    date.day = readInt<std::uint16_t>();
    date.week = readInt<std::uint16_t>();
    date.month = readInt<std::uint16_t>();
    return date;
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
