#pragma once

#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

#include <array>
#include <span>
#include <string_view>
#include <type_traits>

namespace Medea_NS
{
  namespace Detail_NS
  {
    template<class T>
    struct IsStdArray : std::false_type {};

    template<class T, std::size_t N>
    struct IsStdArray<std::array<T, N>> : std::true_type {};

    void printBitSetImpl(const ArrayElementsWriter& elements_writer,
                         std::span<const std::uint8_t> bitset_bytes);

    void printEnumBitmaskImpl(FieldsWriter& out,
                              std::span<const std::uint8_t> bitset_bytes,
                              const std::string_view* field_names);

    void printReservedDataImpl(const ArrayElementsWriter& elements_writer,
                               const std::byte* data,
                               std::size_t num_bytes);
  }

  // Serializes h3m::ReservedData as a JSON array.
  template<std::size_t NumBytes>
  void JsonArrayWriter<h3m::ReservedData<NumBytes>>::operator()(const ArrayElementsWriter& elements_writer,
                                                                const h3m::ReservedData<NumBytes>& reserved_data) const
  {
    Detail_NS::printReservedDataImpl(elements_writer, reserved_data.data(), NumBytes);
  }

  // Serializes h3m::BitSet as a JSON array.
  template<std::size_t NumBytes>
  void JsonArrayWriter<h3m::BitSet<NumBytes>>::operator()(const ArrayElementsWriter& elements_writer,
                                                          const h3m::BitSet<NumBytes>& bitset) const
  {
    Detail_NS::printBitSetImpl(elements_writer, bitset.data);
  }

  // Serializes h3m::EnumBitmask as a JSON object.
  // This template requires that h3m::FieldNames<h3m::EnumBitmask<Enum, NumBytes>> has a static data member
  // `kNames` of the type std::array<std::string_view, NumBytes * 8>.
  template<class Enum, std::size_t NumBytes>
  void JsonObjectWriter<h3m::EnumBitmask<Enum, NumBytes>>::operator()(
    FieldsWriter& out, const h3m::EnumBitmask<Enum, NumBytes>& bitmask) const
  {
    // The type of h3json::kEnumFieldNames<Enum> without const, volatile and reference qualifiers.
    using EnumFieldNamesType = std::remove_cvref_t<decltype(h3json::kEnumFieldNames<Enum>)>;
    // Check that h3json::kEnumFieldNames<Enum> is an std::array.
    static_assert(Detail_NS::IsStdArray<EnumFieldNamesType>::value,
                  "h3json::kEnumFieldNames<Enum> must be an std::array.");
    // Check that its elements have the type std::string_view.
    static_assert(std::is_same_v<typename EnumFieldNamesType::value_type, std::string_view>,
                  "The type of elements in h3json::kEnumFieldNames<Enum> must be std::string_view.");
    // Check that the number of elements is greater than or equal to the number of bits in the bitmask.
    // TODO: consider auto-generating names for padding bits.
    static_assert(h3json::kEnumFieldNames<Enum>.size() >= NumBytes * 8,
                  "The number of elements in h3json::kEnumFieldNames<Enum> must be greater than or equal to "
                  "the number of bits in the bitmask");
    Detail_NS::printEnumBitmaskImpl(out, bitmask.bitset.data, h3json::kEnumFieldNames<Enum>.data());
  }
}
