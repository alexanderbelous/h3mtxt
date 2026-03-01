#include <h3mtxt/H3SvgReader/H3ReaderBase.h>
#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/Map/Utils/SpriteTilesBitmask.h>
#include <h3mtxt/Map/MapAdditionalInfo.h>

#include <cstdint>

namespace h3m
{
  void H3ReaderBase::readBytes(std::span<std::byte> data) const
  {
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream_, data);
  }

  std::string H3ReaderBase::readString16() const
  {
    const std::uint16_t length = readInt<std::uint16_t>();
    std::string result;
    result.resize(length);
    readBytes(std::as_writable_bytes(std::span{ result }));
    return result;
  }

  Coordinates H3ReaderBase::readCoordinates() const
  {
    return H3Reader_NS::readCoordinates(stream_);
  }

  CustomHero H3ReaderBase::readCustomHero() const
  {
    return H3Reader_NS::readCustomHero(stream_);
  }

  SpriteTilesBitmask H3ReaderBase::readSpriteTilesBitmask() const
  {
    return H3Reader_NS::readSpriteTilesBitmask(stream_);
  }

  TeamsInfo H3ReaderBase::readTeamsInfo() const
  {
    return H3Reader_NS::readTeamsInfo(stream_);
  }
}
