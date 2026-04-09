#pragma once

#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <limits>
#include <span>
#include <string_view>
#include <type_traits>

namespace h3mtxt
{
  // Base class for classes that write various HoMM3 file formats (.h3m, .h3c, .GM1, ...).
  //
  // This provides API for writing "primitive" types that are serialized the same way in those formats.
  //
  // FYI: originally, I used a single template H3Writer<T> for all types used in h3m::Map and
  // h3m::Campaign. This allowed nice partial specializations for std::optional and std::array, but
  // it didn't address the inconsistencies in the file formats used by the game:
  // * The number of bytes used to serialize the length of a dynamic array (i.e. std::vector) can be
  //   1, 2 or 4 depending on the context.
  // * In H3SVG the length of a string is sometimes serialized as 2 bytes and sometimes as 4 bytes.
  // * `MapBasicInfo` is serialized differently in H3M and H3SVG because strings are serialized
  //   differently.
  // * ...
  //
  // Because of this, I gave up on using a single template for everything. The new code relies on
  // function overloading instead.
  class H3WriterBase
  {
  public:
    explicit constexpr H3WriterBase(std::ostream& stream) noexcept:
      stream_{stream}
    {}

    // Appends a little-endian integer to the binary stream.
    //
    // This function only participates in the overload resolution if T is a (possibly
    // cvref-qualified) integer type other than bool.
    // \param number - integer value to append.
    template<class T>
    std::enable_if_t<std::is_integral_v<std::remove_cvref_t<T>> &&
                    !std::is_same_v<std::remove_cvref_t<T>, bool>>
    writeData(const T& number) const;

    // Appends an enum to the binary stream.
    //
    // This function only participates in the overload resolution if T is a (possibly
    // cvref-qualified) enum type.
    // \param value - value to append.
    template<class T>
    std::enable_if_t<std::is_enum_v<std::remove_cvref_t<T>>>
    writeData(const T& value) const;

    // Appends a fixed-size array to the binary stream.
    //
    // This function only participates in the overload resolution if T is a (possibly
    // cv-qualified) integer or enum type other than bool.
    template<class T, std::size_t N>
    std::enable_if_t<(std::is_integral_v<std::remove_cvref_t<T>> &&
                      !std::is_same_v<std::remove_cvref_t<T>, bool>) ||
                     std::is_enum_v<std::remove_cvref_t<T>>>
    writeData(const std::array<T, N>& value) const;

    // Appends an h3m::BitSet to the binary stream.
    template<std::size_t NumBytes>
    void writeData(const h3m::BitSet<NumBytes>& bitset) const;

    // Appends an h3m::EnumBitmask to the binary stream.
    template<class Enum, std::size_t NumBytes>
    void writeData(const h3m::EnumBitmask<Enum, NumBytes>& enum_bitmask) const;

    // Appends an h3m::EnumIndexedArray to the binary stream.
    //
    // This function only participates in the overload resolution if T is a (possibly
    // cv-qualified) integer or enum type other than bool.
    template<class Enum, class T, std::size_t NumElements>
    std::enable_if_t<(std::is_integral_v<std::remove_cvref_t<T>> &&
                      !std::is_same_v<std::remove_cvref_t<T>, bool>) ||
                     std::is_enum_v<std::remove_cvref_t<T>>>
    writeData(const h3m::EnumIndexedArray<Enum, T, NumElements>& enum_indexed_array) const;

    // Appends an h3m::ReservedData to the binary stream.
    template<std::size_t NumBytes>
    void writeData(const h3m::ReservedData<NumBytes>& reserved_data) const;

    void writeString16(std::string_view value) const;

    void writeString32(std::string_view value) const;

    // Appends an array of elements to the binary stream.
    //
    // This function only participates in the overload resolution if T is a (possibly
    // cv-qualified) integer or enum type other than bool.
    //
    // The function does NOT write the length of the array to the binary stream - it is the
    // responsibility of the user to do that (if needed at all).
    template<class T>
    std::enable_if_t<(std::is_integral_v<std::remove_cvref_t<T>> &&
                      !std::is_same_v<std::remove_cvref_t<T>, bool>) ||
                     std::is_enum_v<std::remove_cvref_t<T>>>
    writeSpan(std::span<const T> values) const;

  protected:
    // Converts the input std::size_t value to LengthType, raising an exception if it doesn't fit
    // into LengthType.
    // \param num_elements - the input value.
    // \return static_cast<LengthType>(num_elements)
    // \throw std::runtime_error if num_elements > std::numeric_limits<LengthType>::max().
    template<class LengthType>
    static LengthType safeCastVectorSize(std::size_t num_elements);

    std::ostream& stream_;

  private:
    static void checkVectorSize(std::size_t num_elements, std::size_t max_value_for_length_type);

    // Writes a single byte.
    void writeByte(std::byte value) const;

    // Writes a little-endian unsigned integer.
    void writeUintImpl(std::uintmax_t value, std::size_t num_bytes) const;

    // Writes a fixed-width array of bytes.
    void writeByteArrayImpl(std::span<const std::byte> data) const;

    // Writes ReservedData.
    // \param data - pointer to the 0th byte, or nullptr if the data is implicit.
    // \param num_bytes - the number of bytes to write.
    void writeReservedDataImpl(const std::byte* data, std::size_t num_bytes) const;
  };

  template<class T>
  std::enable_if_t<std::is_integral_v<std::remove_cvref_t<T>> &&
                   !std::is_same_v<std::remove_cvref_t<T>, bool>>
  H3WriterBase::writeData(const T& number) const
  {
    static_assert(sizeof(T) <= sizeof(std::uintmax_t), "Integer type T is too wide.");

    if constexpr (sizeof(T) == 1)
    {
      writeByte(static_cast<std::byte>(number));
    }
    else
    {
      // TODO: this is likely redundant, just cast to uintmax_t.
      // Widest integer type with the same signedness as T.
      using WidestInteger = std::conditional_t<std::is_signed_v<T>, std::intmax_t, std::uintmax_t>;
      // Cast the input number to WidestInteger first, then to uintmax_t.
      writeUintImpl(static_cast<std::uintmax_t>(static_cast<WidestInteger>(number)),
                    sizeof(T));
    }
  }

  template<class T>
  std::enable_if_t<std::is_enum_v<std::remove_cvref_t<T>>>
  H3WriterBase::writeData(const T& value) const
  {
    writeData(static_cast<std::underlying_type_t<T>>(value));
  }

  template<class T, std::size_t N>
  std::enable_if_t<(std::is_integral_v<std::remove_cvref_t<T>> &&
                    !std::is_same_v<std::remove_cvref_t<T>, bool>) ||
                    std::is_enum_v<std::remove_cvref_t<T>>>
  H3WriterBase::writeData(const std::array<T, N>& value) const
  {
    writeSpan(std::span<const T>{value});
  }

  template<std::size_t NumBytes>
  void H3WriterBase::writeData(const h3m::BitSet<NumBytes>& bitset) const
  {
    writeByteArrayImpl(std::as_bytes(std::span<const std::uint8_t, NumBytes>{bitset.data}));
  }

  template<class Enum, std::size_t NumBytes>
  void H3WriterBase::writeData(const h3m::EnumBitmask<Enum, NumBytes>& enum_bitmask) const
  {
    writeData(enum_bitmask.bitset);
  }

  template<class Enum, class T, std::size_t NumElements>
  std::enable_if_t<(std::is_integral_v<std::remove_cvref_t<T>> &&
                    !std::is_same_v<std::remove_cvref_t<T>, bool>) ||
                    std::is_enum_v<std::remove_cvref_t<T>>>
  H3WriterBase::writeData(const h3m::EnumIndexedArray<Enum, T, NumElements>& enum_indexed_array) const
  {
    writeData(enum_indexed_array.data);
  }

  template<std::size_t NumBytes>
  void H3WriterBase::writeData(const h3m::ReservedData<NumBytes>& reserved_data) const
  {
    writeReservedDataImpl(reserved_data.data(), NumBytes);
  }

  template<class T>
  std::enable_if_t<(std::is_integral_v<std::remove_cvref_t<T>> &&
                    !std::is_same_v<std::remove_cvref_t<T>, bool>) ||
                    std::is_enum_v<std::remove_cvref_t<T>>>
  H3WriterBase::writeSpan(std::span<const T> values) const
  {
    if constexpr (sizeof(T) == 1)
    {
      writeByteArrayImpl(std::as_bytes(values));
    }
    else
    {
      for (const T& element : values)
      {
        writeData(element);
      }
    }
  }

  template<class LengthType>
  LengthType H3WriterBase::safeCastVectorSize(std::size_t num_elements)
  {
    static_assert(std::is_integral_v<LengthType>, "LengthType must be an integer type.");
    checkVectorSize(num_elements, static_cast<std::size_t>(std::numeric_limits<LengthType>::max()));
    return static_cast<LengthType>(num_elements);
  }
}
