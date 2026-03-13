#include <h3mtxt/H3Reader/H3ReaderBase/H3ReaderBase.h>

#include <istream>
#include <stdexcept>

namespace h3m
{
  std::byte H3ReaderBase::readByte() const
  {
    using Traits = std::istream::traits_type;
    if (!stream_)
    {
      throw std::logic_error("Error in the input stream.");
    }
    const Traits::int_type character = stream_.get();
    if (character == Traits::eof())
    {
      throw std::runtime_error("Unexpected end of stream.");
    }
    return static_cast<std::byte>(character);
  }

  void H3ReaderBase::readBytes(std::span<std::byte> data) const
  {
    if (!stream_ || !stream_.read(reinterpret_cast<char*>(data.data()), data.size()))
    {
      throw std::runtime_error("Failed to read an array of bytes.");
    }
  }

  std::uintmax_t H3ReaderBase::readUintImpl(Detail_NS::IntegerWidth width) const
  {
    std::array<std::byte, sizeof(std::uintmax_t)> buffer {};
    const std::span<std::byte> data(buffer.data(), width.size());
    readBytes(data);

    std::uintmax_t result = 0;
    std::uintmax_t shift = 0;
    for (std::byte byte : data)
    {
      result |= (static_cast<std::uintmax_t>(byte) << shift);
      shift += 8;
    }
    return result;
  }

  std::string H3ReaderBase::readString16() const
  {
    const std::size_t length = readInt<std::uint16_t>();
    std::string result;
    result.resize(length);
    readBytes(std::as_writable_bytes(std::span{ result }));
    return result;
  }

  std::string H3ReaderBase::readString32() const
  {
    const std::size_t length = readInt<std::uint32_t>();
    std::string result;
    result.resize(length);
    readBytes(std::as_writable_bytes(std::span{ result }));
    return result;
  }
}
