#pragma once

#include <h3mtxt/H3MReader/IntegerWidth.h>
#include <h3mtxt/Map/Base.h>
#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

#include <array>
#include <cstdint>
#include <iosfwd>
#include <span>
#include <string>
#include <type_traits>
#include <utility>

namespace h3m::H3Reader_NS
{
  namespace Detail_NS
  {
    // Reads a single byte from the stream.
    std::byte readByte(std::istream& stream);

    // Reads a little-endian unsigned integer from the stream.
    // \param stream - input binary stream.
    // \param width - the width of the integer type in bytes.
    // \return the parsed integer.
    std::uintmax_t readUintImpl(std::istream& stream, IntegerWidth width);

    // Reads an array of bytes from the given stream.
    void readByteArrayImpl(std::istream& stream, std::span<std::byte> data);

    // Checks if all bytes in the array are 0.
    // \param data - input array.
    // \return true if all bytes in @data are 0, false otherwise.
    bool isAllZeros(std::span<const std::byte> data);
  }

  // Reads a little-endian integer from the stream.
  // \param stream - input stream.
  // \return the parsed integer.
  template<class T>
  T readInt(std::istream& stream)
  {
    static_assert(std::is_integral_v<T>, "T must be an integral type.");
    if constexpr (sizeof(T) == 1)
    {
      return static_cast<T>(Detail_NS::readByte(stream));
    }
    else
    {
      return static_cast<T>(Detail_NS::readUintImpl(stream, Detail_NS::IntegerWidth(std::in_place_type<T>)));
    }
  }

  // Reads a boolean from the stream.
  inline Bool readBool(std::istream& stream)
  {
    return static_cast<Bool>(readInt<std::uint8_t>(stream));
  }

  // Reads an enum from the stream.
  template<class T>
  T readEnum(std::istream& stream)
  {
    return static_cast<T>(readInt<std::underlying_type_t<T>>(stream));
  }

  // Reads a string from the stream.
  // Strings in .h3m are always written as Pascal strings: the string length N is
  // written as uint32, followed by N bytes.
  std::string readString(std::istream& stream);

  // Reads a fixed-length array of bytes from the stream.
  template<std::size_t N>
  std::array<std::uint8_t, N> readByteArray(std::istream& stream)
  {
    std::array<std::uint8_t, N> result{};
    Detail_NS::readByteArrayImpl(stream, std::as_writable_bytes(std::span{ result }));
    return result;
  }

  // Reads a BitSet from the stream.
  template<std::size_t NumBytes>
  BitSet<NumBytes> readBitSet(std::istream& stream)
  {
    return BitSet<NumBytes>{readByteArray<NumBytes>(stream)};
  }

  // Reads a EnumBitmask from the stream.
  template<class Enum, std::size_t NumBytes>
  EnumBitmask<Enum, NumBytes> readEnumBitmask(std::istream& stream)
  {
    return EnumBitmask<Enum, NumBytes>{readBitSet<NumBytes>(stream)};
  }

  // Reads ReservedData from the stream.
  template<std::size_t N>
  ReservedData<N> readReservedData(std::istream& stream)
  {
    std::array<std::byte, N> data;
    Detail_NS::readByteArrayImpl(stream, std::span{data});
    if (Detail_NS::isAllZeros(data))
    {
      return ReservedData<N>();
    }
    return ReservedData<N>(data);
  }
}
