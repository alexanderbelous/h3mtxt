#include <h3mtxt/H3MWriter/Utils.h>

#include <algorithm>
#include <iterator>
#include <ostream>
#include <stdexcept>

namespace h3m
{
  namespace Detail_NS
  {
    void writeUintImpl(std::ostream& stream, std::uintmax_t value, unsigned int num_bytes)
    {
      // h3mtxt uses int8_t and uint8_t, which are only defined if CHAR_BIT == 8.
      static_assert(CHAR_BIT == 8, "Unsupported platform.");
      constexpr std::uintmax_t kMask = 0xFF;
      for (unsigned int i = 0; i < num_bytes; ++i)
      {
        const std::uint8_t byte = static_cast<std::uint8_t>(value & kMask);
        stream.put(static_cast<char>(byte));
        value >>= 8;
      }
    }

    void writeByteArrayImpl(std::ostream& stream, std::span<const std::byte> data)
    {
      stream.write(reinterpret_cast<const char*>(data.data()), data.size());
    }

    void writeReservedDataImpl(std::ostream& stream, const std::byte* data, std::size_t num_bytes)
    {
      if (data)
      {
        writeByteArrayImpl(stream, std::span<const std::byte>(data, num_bytes));
      }
      else
      {
        std::fill_n(std::ostreambuf_iterator<char>(stream), num_bytes, char{0});
      }
    }

    void checkVectorSize(std::size_t num_elements, std::size_t max_value_for_type)
    {
      if (num_elements > max_value_for_type)
      {
        throw std::runtime_error("writeVector(): too many elements in the vector.");
      }
    }
  }

  void H3MWriter<std::byte>::operator()(std::ostream& stream, std::byte value) const
  {
    stream.put(static_cast<char>(value));
  }

  void H3MWriter<std::string>::operator()(std::ostream& stream, const std::string& value) const
  {
    if (value.size() > std::numeric_limits<std::uint32_t>::max())
    {
      throw std::runtime_error("The string is too long.");
    }
    writeData(stream, static_cast<std::uint32_t>(value.size()));
    stream.write(value.data(), value.size());
  }
}
