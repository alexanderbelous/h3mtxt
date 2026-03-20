#include <h3mtxt/H3Writer/H3WriterBase/H3WriterBase.h>

#include <algorithm>
#include <climits>
#include <iterator>
#include <ostream>

namespace h3mtxt
{
  // Sanity check: h3mtxt needs to distinguish between the types that are serialized using 1, 2
  // and 4 bytes. It uses fixed-width integer types (e.g., std::uint8_t, std::uint16_t,
  // std::uint32_t) for that, which are only defined if CHAR_BIT == 8.
  static_assert(CHAR_BIT == 8, "Unsupported platform.");

  void H3WriterBase::checkVectorSize(std::size_t num_elements, std::size_t max_value_for_length_type)
  {
    if (num_elements > max_value_for_length_type)
    {
      throw std::runtime_error("safeCastVectorSize(): too many elements in the vector.");
    }
  }

  void H3WriterBase::writeByte(std::byte value) const
  {
    stream_.put(static_cast<char>(value));
  }

  void H3WriterBase::writeUintImpl(std::uintmax_t value, unsigned int num_bytes) const
  {
    constexpr std::uintmax_t kMask = 0xFF;
    for (unsigned int i = 0; i < num_bytes; ++i)
    {
      const std::uint8_t byte = static_cast<std::uint8_t>(value & kMask);
      writeByte(static_cast<std::byte>(byte));
      value >>= 8;
    }
  }

  void H3WriterBase::writeByteArrayImpl(std::span<const std::byte> data) const
  {
    stream_.write(reinterpret_cast<const char*>(data.data()), data.size());
  }

  void H3WriterBase::writeString16(std::string_view value) const
  {
    writeData(safeCastVectorSize<std::uint16_t>(value.size()));
    writeByteArrayImpl(std::as_bytes(std::span{ value }));
  }

  void H3WriterBase::writeString32(std::string_view value) const
  {
    writeData(safeCastVectorSize<std::uint32_t>(value.size()));
    writeByteArrayImpl(std::as_bytes(std::span{ value }));
  }

  void H3WriterBase::writeReservedDataImpl(const std::byte* data, std::size_t num_bytes) const
  {
    if (data)
    {
      writeByteArrayImpl(std::span<const std::byte>(data, num_bytes));
    }
    else
    {
      std::fill_n(std::ostreambuf_iterator<char>(stream_), num_bytes, char{0});
    }
  }
}
