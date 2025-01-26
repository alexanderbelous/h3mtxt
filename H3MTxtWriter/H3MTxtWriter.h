#pragma once

#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/TextWriter/ValueWriter.h>

namespace Util_NS
{
  template<std::size_t NumBytes>
  struct ValueWriter<h3m::ReservedData<NumBytes>>
  {
    void operator()(IndentedTextWriter& out, const h3m::ReservedData<NumBytes>& reserved_data)
    {
      // Print all elements on the same line.
      ScopedArrayWriter<std::byte> array_writer = out.writeArray<std::byte>(false);
      for (std::size_t i = 0; i < NumBytes; ++i)
      {
        array_writer.writeElement(reserved_data[i]);
      }
    }
  };

  template<std::size_t NumBytes>
  struct ValueWriter<h3m::BitSet<NumBytes>>
  {
    void operator()(IndentedTextWriter& out, const h3m::BitSet<NumBytes>& value)
    {
      writeValue(out, value.data());
    }
  };
}
