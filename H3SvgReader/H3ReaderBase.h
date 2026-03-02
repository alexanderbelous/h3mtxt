#pragma once

#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/H3Reader/Utils.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <string>

namespace h3m
{
  // Base class for classes that read various HoMM3 file formats (.h3m, .h3c, .GM1, ...)
  //
  // This provides API for reading types that are serialized the same way in those formats.
  //
  // TODO: reuse this for reading .h3m/.h3c files.
  class H3ReaderBase
  {
  public:
    // Constructs a H3ReaderBase that will read bytes from the specified istream.
    // \param stream - istream to read bytes from.
    explicit constexpr H3ReaderBase(std::istream& stream) noexcept :
      stream_{ stream }
    {}

    // Reads an array of bytes.
    // \param data - output span. The function will read data.size() bytes from the stream and write them to @data.
    void readBytes(std::span<std::byte> data) const;

    // Reads a fixed-length array of bytes from the stream.
    template<std::size_t N>
    std::array<std::uint8_t, N> readByteArray() const;

    // Reads a little-endian integer of the specified type.
    // \param stream - input stream.
    // \return the parsed integer.
    template<class T>
    T readInt() const;

    // Reads an 8-bit integer which should be interpreted as a boolean (0 - false, nonzero - true).
    inline Bool readBool() const;

    // Reads an enum.
    // The function assumes that the enum is serialized via its underlying integer value, i.e. as a
    // little-endian integer whose width is the same as sizeof(T).
    template<class T>
    T readEnum() const;

    // Reads a length-prefixed string, whose length is serialized as a 16-bit little-endian integer.
    std::string readString16() const;

    // Reads ReservedData from the stream.
    // ReservedData<N> is serialized simply as an array of N bytes.
    template<std::size_t N>
    ReservedData<N> readReservedData() const;

    // Reads a BitSet from the stream.
    // BitSet<N> is serialized as an array N bytes that should be interpreted as an array of 8*N bits.
    template<std::size_t NumBytes>
    BitSet<NumBytes> readBitSet();

    // Reads a EnumBitmask from the stream.
    // EnumBitmask<T, N> is serialized as an array N bytes that should be interpreted as an array of 8*N bits,
    // where the i-th bit is the encoded boolean value for the enum value static_cast<T>(i).
    template<class Enum, std::size_t NumBytes>
    EnumBitmask<Enum, NumBytes> readEnumBitmask() const;

    Coordinates readCoordinates() const;

    CreatureStack readCreatureStack() const;

    CustomHero readCustomHero() const;

    PrimarySkills readPrimarySkills() const;

    Resources readResources() const;

    SecondarySkill readSecondarySkill() const;

    SpriteTilesBitmask readSpriteTilesBitmask() const;

    TeamsInfo readTeamsInfo() const;

  protected:
    std::istream& stream_;
  };

  template<std::size_t N>
  std::array<std::uint8_t, N> H3ReaderBase::readByteArray() const
  {
    return H3Reader_NS::readByteArray<N>(stream_);
  }

  template<class T>
  T H3ReaderBase::readInt() const
  {
    return H3Reader_NS::readInt<T>(stream_);
  }

  Bool H3ReaderBase::readBool() const
  {
    return H3Reader_NS::readBool(stream_);
  }

  template<class T>
  T H3ReaderBase::readEnum() const
  {
    return H3Reader_NS::readEnum<T>(stream_);
  }

  template<std::size_t N>
  ReservedData<N> H3ReaderBase::readReservedData() const
  {
    return H3Reader_NS::readReservedData<N>(stream_);
  }

  template<std::size_t NumBytes>
  BitSet<NumBytes> H3ReaderBase::readBitSet()
  {
    return H3Reader_NS::readBitSet<NumBytes>(stream_);
  }

  template<class Enum, std::size_t NumBytes>
  EnumBitmask<Enum, NumBytes> H3ReaderBase::readEnumBitmask() const
  {
    return H3Reader_NS::readEnumBitmask<Enum, NumBytes>(stream_);
  }
}
