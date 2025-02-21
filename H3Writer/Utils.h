#pragma once

#include <h3mtxt/H3Writer/H3Writer.h>
#include <h3mtxt/Map/Base.h>
#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

#include <array>
#include <cstdint>
#include <iosfwd>
#include <limits>
#include <optional>
#include <span>
#include <string>
#include <type_traits>
#include <vector>

namespace h3m::H3Writer_NS
{
  namespace Detail_NS
  {
    // Writes a little-endian unsigned integer.
    void writeUintImpl(std::ostream& stream, std::uintmax_t value, unsigned int num_bytes);

    // Writes a fixed-width array of bytes.
    void writeByteArrayImpl(std::ostream& stream, std::span<const std::byte> data);

    // Writes ReservedData.
    // \param data - pointer to the 0th byte, or nullptr if the data is implicit.
    // \param num_bytes - the number of bytes to write.
    void writeReservedDataImpl(std::ostream& stream, const std::byte* data, std::size_t num_bytes);

    // Checks if the size of the vector fits into the specified type.
    // \param num_elements - the number of elements in the vector.
    // \param max_value_for_type - the maximum value for the integer type
    //        that should be used to write the size of the vector as.
    // \throw std::runtime_error if num_elements > max_value_for_type.
    void checkVectorSize(std::size_t num_elements, std::size_t max_value_for_type);
  }

  // Full specialization for std::byte.
  template<>
  struct H3Writer<std::byte>
  {
    void operator()(std::ostream& stream, std::byte value) const;
  };

  // Partial specialization for integer types.
  template<class T>
  struct H3Writer<T, std::enable_if_t<std::is_integral_v<T>>>
  {
    void operator()(std::ostream& stream, T value) const
    {
      if constexpr (sizeof(T) == 1)
      {
        writeData(stream, static_cast<std::byte>(value));
      }
      else
      {
        // TODO: this is likely redundant, just cast to uintmax_t.
        // Widest integer type with the same signedness as T.
        using WidestInteger = std::conditional_t<std::is_signed_v<T>, std::intmax_t, std::uintmax_t>;
        // Cast the input value to WidestInteger first, then to uintmax_t.
        Detail_NS::writeUintImpl(stream,
                                 static_cast<std::uintmax_t>(static_cast<WidestInteger>(value)),
                                 sizeof(T));
       }
    }
  };

  // Partial specialization for enum types.
  template<class T>
  struct H3Writer<T, std::enable_if_t<std::is_enum_v<T>>>
  {
    void operator()(std::ostream& stream, T value) const
    {
      writeData(stream, static_cast<std::underlying_type_t<T>>(value));
    }
  };

  // Full specialization for std::string.
  template<>
  struct H3Writer<std::string>
  {
    void operator()(std::ostream& stream, const std::string& value) const;
  };

  // Partial specialization for std::array<T, N>.
  // In H3M arrays of known width are always encoded as a sequence of
  // individually encoded elements (the size of the array is not encoded).
  template<class T, std::size_t N>
  struct H3Writer<std::array<T, N>>
  {
    void operator()(std::ostream& stream, const std::array<T, N>& values) const
    {
      // Optimization for std::uint8_t and std::int8_t.
      // TODO: this can be used for enums whose underlying type is int8_t or uint8_t.
      if constexpr (std::is_same_v<T, std::uint8_t> || std::is_same_v<T, std::int8_t>)
      {
        Detail_NS::writeByteArrayImpl(stream, std::as_bytes(std::span{values}));
      }
      else
      {
        for (const T& element : values)
        {
          writeData(stream, element);
        }
      }
    }
  };

  // Partial specialization for std::optional.
  template<class T>
  struct H3Writer<std::optional<T>>
  {
    void operator()(std::ostream& stream, const std::optional<T>& value) const
    {
      writeData(stream, static_cast<Bool>(value.has_value()));
      if (value.has_value())
      {
        writeData(stream, *value);
      }
    }
  };

  // Partial specialization for ReservedData.
  template<std::size_t NumBytes>
  struct H3Writer<ReservedData<NumBytes>>
  {
    void operator()(std::ostream& stream, const ReservedData<NumBytes>& reserved_data) const
    {
      Detail_NS::writeReservedDataImpl(stream, reserved_data.data(), NumBytes);
    }
  };

  // Partial specialization for BitSet.
  template<std::size_t NumBytes>
  struct H3Writer<BitSet<NumBytes>>
  {
    void operator()(std::ostream& stream, const BitSet<NumBytes>& value) const
    {
      writeData(stream, value.data);
    }
  };

  // Partial specialization for EnumBitmask.
  template<class Enum, std::size_t NumBytes>
  struct H3Writer<EnumBitmask<Enum, NumBytes>>
  {
    void operator()(std::ostream& stream, const EnumBitmask<Enum, NumBytes>& value) const
    {
      writeData(stream, value.bitset);
    }
  };

  // Writes a vector of elements into a binary stream storing a .h3m map.
  // Dynamic-size array are written in H3M similar to Pascal strings: first,
  // the number of elements is written, then each element is written. However,
  // unlike strings in H3M, the size of the array isn't always serialized as uint32:
  // there are places where uint16 or even uint8 is used instead.
  //
  // \param stream - output stream.
  // \param vec - elements to write.
  // \throw std::runtime_error if vec.size() doesn't fit into VectorSizeType.
  template<class VectorSizeType, class T, class Alloc>
  void writeVector(std::ostream& stream, const std::vector<T, Alloc>& vec)
  {
    static_assert(std::is_integral_v<VectorSizeType> && std::is_unsigned_v<VectorSizeType>,
                  "VectorSizeType must be an unsigned integer type.");

    Detail_NS::checkVectorSize(vec.size(), std::numeric_limits<VectorSizeType>::max());
    writeData(stream, static_cast<VectorSizeType>(vec.size()));
    for (const T& element : vec)
    {
      writeData(stream, element);
    }
  }
}
