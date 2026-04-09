#pragma once

#include <h3mtxt/Map/MapFwd.h>
#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <span>
#include <string>
#include <type_traits>

namespace h3m
{
  // Base class for classes that read various HoMM3 file formats (.h3m, .h3c, .GM1, ...).
  //
  // This provides API for reading "primitive" types that are serialized the same way in those formats.
  //
  // Each function in this class only reads the bytes necessary to decode the specified value,
  // i.e. the class doesn't maintain its own buffer. For example,
  //     std::uint32_t my_number = H3ReaderBase{my_stream}.readInt<std::uint32_t>();
  // will only read 4 bytes from my_stream.
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

    // Reads a length-prefixed string, whose length is serialized as a 32-bit little-endian integer.
    std::string readString32() const;

    // Reads ReservedData from the stream.
    // ReservedData<N> is serialized simply as an array of N bytes.
    template<std::size_t N>
    ReservedData<N> readReservedData() const;

    // Reads a BitSet from the stream.
    // BitSet<N> is serialized as an array N bytes that should be interpreted as an array of 8*N bits.
    template<std::size_t NumBytes>
    BitSet<NumBytes> readBitSet() const;

    // Reads a EnumBitmask from the stream.
    // EnumBitmask<T, N> is serialized as an array N bytes that should be interpreted as an array of 8*N bits,
    // where the i-th bit is the encoded boolean value for the enum value static_cast<T>(i).
    template<class Enum, std::size_t NumBytes>
    EnumBitmask<Enum, NumBytes> readEnumBitmask() const;

  private:
    // Type of the integer returned by readUintImpl().
    // FYI: technically, this can be replaced with an extended integer type like std::uint128_t. However,
    // such types are not required to be supported by the C++ Standard.
    // HoMM3 never uses integers wider than 32 bits, so this shouldn't be an issue anyway.
    using WidestUInt = std::uintmax_t;

    static_assert(std::is_integral_v<WidestUInt>, "WidestUInt must be an integer type.");
    static_assert(std::is_unsigned_v<WidestUInt>, "WidestUInt must be an unsigned integer type.");

    // Reads a single byte from the stream.
    std::byte readByte() const;

    // Reads a little-endian unsigned integer from the stream.
    // \param stream - input binary stream.
    // \param width - the width of the integer type in bytes.
    // \return the parsed integer.
    WidestUInt readUintImpl(std::size_t width) const;

  protected:
    // Stream to read the data from.
    std::istream& stream_;
  };

  template<std::size_t N>
  std::array<std::uint8_t, N> H3ReaderBase::readByteArray() const
  {
    std::array<std::uint8_t, N> result {};
    if constexpr (std::is_same_v<std::uint8_t, unsigned char>)
    {
      readBytes(std::as_writable_bytes(std::span{ result }));
    }
    else
    {
      // What kind of a platform is this?
      for (std::uint8_t& element : result)
      {
        element = readInt<std::uint8_t>();
      }
    }
    return result;
  }

  template<class T>
  T H3ReaderBase::readInt() const
  {
    static_assert(std::is_integral_v<T>, "T must be an integral type.");
    static_assert(sizeof(T) <= sizeof(WidestUInt), "The integer type T is too wide.");

    if constexpr (sizeof(T) == 1)
    {
      return static_cast<T>(readByte());
    }
    else
    {
      return static_cast<T>(readUintImpl(sizeof(T)));
    }
  }

  Bool H3ReaderBase::readBool() const
  {
    return static_cast<Bool>(readInt<std::uint8_t>());
  }

  template<class T>
  T H3ReaderBase::readEnum() const
  {
    return static_cast<T>(readInt<std::underlying_type_t<T>>());
  }

  template<std::size_t N>
  ReservedData<N> H3ReaderBase::readReservedData() const
  {
    std::array<std::byte, N> data;
    readBytes(std::span{data});
    if (h3m::Detail_NS::isAllZeros(data))
    {
      return ReservedData<N>();
    }
    return ReservedData<N>(data);
  }

  template<std::size_t NumBytes>
  BitSet<NumBytes> H3ReaderBase::readBitSet() const
  {
    return BitSet<NumBytes>{readByteArray<NumBytes>()};
  }

  template<class Enum, std::size_t NumBytes>
  EnumBitmask<Enum, NumBytes> H3ReaderBase::readEnumBitmask() const
  {
    return EnumBitmask<Enum, NumBytes>{readBitSet<NumBytes>()};
  }
}
