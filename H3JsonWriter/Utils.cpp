#include <h3mtxt/H3JsonWriter/Utils.h>
#include <h3mtxt/JsonWriter/JsonWriter.h>

namespace Medea_NS
{
  namespace Detail_NS
  {
    void printReservedDataImpl(const ScopedArrayWriter& elements_writer,
                               const std::byte* data,
                               std::size_t num_bytes)
    {
      for (std::size_t i = 0; i < num_bytes; ++i)
      {
        elements_writer.writeElement(data ? data[i] : std::byte{0});
      }
    }

    void printEnumBitmaskImpl(FieldsWriter& out,
                              std::span<const std::uint8_t> bitset_bytes,
                              const std::string_view* field_names)
    {
      for (std::size_t byte_idx = 0; byte_idx < bitset_bytes.size(); ++byte_idx)
      {
        for (std::uint8_t bit_index_in_byte = 0; bit_index_in_byte < 8; ++bit_index_in_byte)
        {
          const std::size_t bit_idx = byte_idx * 8 + bit_index_in_byte;
          const std::uint8_t mask = std::uint8_t{1} << bit_index_in_byte;
          const bool bit = bitset_bytes[byte_idx] & mask;
          out.writeField(field_names[bit_idx], bit);
        }
      }
    }

    void printBitSetImpl(const ScopedArrayWriter& elements_writer,
                         std::span<const std::uint8_t> bitset_bytes)
    {
      for (std::size_t byte_idx = 0; byte_idx < bitset_bytes.size(); ++byte_idx)
      {
        elements_writer.writeElement(bitset_bytes[byte_idx]);
      }
    }
  }
}
