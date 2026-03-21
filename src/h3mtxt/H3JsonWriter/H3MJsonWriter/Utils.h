#pragma once

#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/getEnumString.h>
#include <h3mtxt/JsonCommon/getEnumFieldNames.h>
#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/Medea/Medea.h>

#include <span>
#include <string_view>
#include <type_traits>

namespace h3json::Detail_NS
{
  void printBitSetImpl(const Medea_NS::ArrayElementsWriter& elements_writer,
                       std::span<const std::uint8_t> bitset_bytes);

  void printEnumBitmaskImpl(Medea_NS::FieldsWriter& out,
                            std::span<const std::uint8_t> bitset_bytes,
                            const std::string_view* field_names);

  void printReservedDataImpl(const Medea_NS::ArrayElementsWriter& elements_writer,
                             const std::byte* data,
                             std::size_t num_bytes);
}

namespace Medea_NS
{
  // Serializes h3m::ReservedData as a JSON array.
  template<std::size_t NumBytes>
  void JsonArrayWriter<h3m::ReservedData<NumBytes>>::operator()(const ArrayElementsWriter& elements_writer,
                                                                const h3m::ReservedData<NumBytes>& reserved_data) const
  {
    h3json::Detail_NS::printReservedDataImpl(elements_writer, reserved_data.data(), NumBytes);
  }

  // Serializes h3m::BitSet as a JSON array.
  template<std::size_t NumBytes>
  void JsonArrayWriter<h3m::BitSet<NumBytes>>::operator()(const ArrayElementsWriter& elements_writer,
                                                          const h3m::BitSet<NumBytes>& bitset) const
  {
    h3json::Detail_NS::printBitSetImpl(elements_writer, bitset.data);
  }

  // Serializes h3m::EnumBitmask as a JSON object.
  // This template requires that h3m::FieldNames<h3m::EnumBitmask<Enum, NumBytes>> has a static data member
  // `kNames` of the type std::array<std::string_view, NumBytes * 8>.
  template<class Enum, std::size_t NumBytes>
  void JsonObjectWriter<h3m::EnumBitmask<Enum, NumBytes>>::operator()(
    FieldsWriter& out, const h3m::EnumBitmask<Enum, NumBytes>& bitmask) const
  {
    constexpr std::span<const std::string_view, NumBytes * 8> kNames =
      h3json::getEnumFieldNames<Enum, NumBytes * 8>();
    h3json::Detail_NS::printEnumBitmaskImpl(out, bitmask.bitset.data, kNames.data());
  }

  // Default implementation for h3m::EnumIndexedArray: serializes the value as a JSON object.
  template<class Enum, class T, std::size_t NumElements>
  void JsonObjectWriter<h3m::EnumIndexedArray<Enum, T, NumElements>>::operator()(
    FieldsWriter& out, const h3m::EnumIndexedArray<Enum, T, NumElements>& enum_indexed_array) const
  {
    constexpr std::span<const std::string_view, NumElements> kNames =
      h3json::getEnumFieldNames<Enum, NumElements>();
    for (std::size_t i = 0; i < NumElements; ++i)
    {
      const T& element = enum_indexed_array.data[i];
      out.writeField(kNames[i], element);
      // If T is an enum type, print a comment for it.
      // TODO: ideally, we should only print comments if getEnumString() is callable for T
      // (i.e. it shouldn't trigger a compilation error otherwise).
      if constexpr (std::is_enum_v<T>)
      {
        // Note that getEnumString() is not namespace-qualified - this is intentional to allow ADL
        // (argument-dependent lookup).
        // TODO: consider making getEnumString() a template instead.
        if (std::string_view enum_str = getEnumString(element); !enum_str.empty())
        {
          out.writeComment(enum_str, false);
        }
      }
    }
  }
}
