#pragma once

#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/JsonWriter/JsonValueWriter.h>

namespace Medea_NS
{
  // Serialize h3m::ReservedData as a JSON array.
  template<std::size_t NumBytes>
  struct JsonArrayWriter<h3m::ReservedData<NumBytes>>
  {
    using ElementType = std::byte;

    void operator()(ScopedArrayWriter<std::byte>& elements_writer,
                    const h3m::ReservedData<NumBytes>& reserved_data) const
    {
      for (std::size_t i = 0; i < NumBytes; ++i)
      {
        elements_writer.writeElement(reserved_data[i]);
      }
    }
  };

  // Serialize h3m::BitSet as a JSON array.
  template<std::size_t NumBytes>
  struct JsonArrayWriter<h3m::BitSet<NumBytes>>
  {
    using ElementType = std::uint8_t;

    void operator()(ScopedArrayWriter<std::uint8_t>& elements_writer, const h3m::BitSet<NumBytes>& bitset) const
    {
      writeArray(bitset.data, elements_writer);
    }
  };
}
