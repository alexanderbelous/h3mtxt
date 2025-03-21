#include <h3mtxt/H3Reader/Utils.h>

#include <istream>
#include <stdexcept>

namespace h3m::H3Reader_NS
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

    std::uintmax_t readUintImpl(std::istream& stream, IntegerWidth width)
    {
      std::array<std::byte, sizeof(std::uintmax_t)> buffer {};
      const std::span<std::byte> data(buffer.data(), width.size());
      readByteArrayImpl(stream, data);

      std::uintmax_t result = 0;
      std::uintmax_t shift = 0;
      for (std::byte byte : data)
      {
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
  }

  std::string readString(std::istream& stream)
  {
    const std::uint32_t length = readInt<std::uint32_t>(stream);
    std::string result;
    result.resize(length);
    Detail_NS::readByteArrayImpl(stream, std::as_writable_bytes(std::span{ result }));
    return result;
  }
}
