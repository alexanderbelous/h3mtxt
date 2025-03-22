#pragma once

#include <h3mtxt/H3JsonWriter/H3JsonWriter.h>
#include <h3mtxt/JsonCommon/FieldName.h>
#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

#include <span>
#include <string_view>
#include <type_traits>

namespace Medea_NS
{
  namespace Detail_NS
  {
    void printBitSetImpl(const ScopedArrayWriter& elements_writer,
                         std::span<const std::uint8_t> bitset_bytes);

    void printEnumBitmaskImpl(FieldsWriter& out,
                              std::span<const std::uint8_t> bitset_bytes,
                              const std::string_view* field_names);

    void printReservedDataImpl(const ScopedArrayWriter& elements_writer,
                               const std::byte* data,
                               std::size_t num_bytes);
  }

  // Serializes h3m::ReservedData as a JSON array.
  template<std::size_t NumBytes>
  void JsonArrayWriter<h3m::ReservedData<NumBytes>>::operator()(const ScopedArrayWriter& elements_writer,
                                                                const h3m::ReservedData<NumBytes>& reserved_data) const
  {
    Detail_NS::printReservedDataImpl(elements_writer, reserved_data.data(), NumBytes);
  }

  // Serializes h3m::BitSet as a JSON array.
  template<std::size_t NumBytes>
  void JsonArrayWriter<h3m::BitSet<NumBytes>>::operator()(const ScopedArrayWriter& elements_writer,
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
    using Fields = h3m::FieldNames<h3m::EnumBitmask<Enum, NumBytes>>;
    static_assert(std::is_same_v<std::remove_cvref_t<decltype(Fields::kNames)>,
                                 std::array<std::string_view, NumBytes * 8>>,
                  "h3m::FieldNames<h3m::EnumBitmask<Enum, NumBytes>> must have a "
                  "static data member kNames of the type std::array<std::string_view, NumBytes * 8>.");
    Detail_NS::printEnumBitmaskImpl(out, bitmask.bitset.data, Fields::kNames.data());
  }
}
