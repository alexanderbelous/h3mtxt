#include <h3mtxt/H3MReader/Utils.h>

#include <algorithm>
#include <istream>
#include <stdexcept>

namespace h3m
{
  namespace Detail_NS
  {
    std::byte readByte(std::istream& stream)
    {
      using Traits = std::istream::traits_type;
      if (!stream)
      {
        throw std::logic_error("Error in the input stream.");
      }
      const Traits::int_type character = stream.get();
      if (character == Traits::eof())
      {
        throw std::runtime_error("Unexpected end of stream.");
      }
      return static_cast<std::byte>(character);
    }

    std::uintmax_t readUintImpl(std::istream& stream, unsigned int num_bytes)
    {
      std::uintmax_t result = 0;
      std::uintmax_t shift = 0;
      for (unsigned int i = 0; i < num_bytes; ++i)
      {
        const std::uint8_t byte = readUint8(stream);
        result |= (static_cast<std::uintmax_t>(byte) << shift);
        shift += 8;
      }
      return result;
    }

    void readByteArrayImpl(std::istream& stream, std::span<std::byte> data)
    {
      if (!stream || !stream.read(reinterpret_cast<char*>(data.data()), data.size()))
      {
        throw std::runtime_error("Failed to read an array of bytes.");
      }
    }

    bool isAllZeros(std::span<const std::byte> data)
    {
      return std::all_of(data.begin(), data.end(), [](std::byte value)
        {
          return value == std::byte{ 0 };
        });
    }
  }

  std::string readString(std::istream& stream)
  {
    const std::uint32_t length = readUint<std::uint32_t>(stream);
    std::string result;
    result.resize(length);
    Detail_NS::readByteArrayImpl(stream, std::as_writable_bytes(std::span{ result }));
    return result;
  }
}
