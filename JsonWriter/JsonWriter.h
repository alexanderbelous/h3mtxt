#pragma once

// API + built-in support for some types.

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>
#include <h3mtxt/JsonWriter/API.h>

#include <array>
#include <span>
#include <string>
#include <type_traits>
#include <vector>

namespace Medea_NS
{
  namespace Detail_NS
  {
    // Traits class indicating whether arrays of elements of type T should be serialized
    // with one element per line or on a single line.
    //
    // Stores true for types that are serialized as Bool, Int or UInt, false for everything else.
    template <class ElementType>
    struct IsSingleLineArray : std::bool_constant<JsonWriterTraits<ElementType>::kValueType == JsonValueType::Bool ||
                                                  JsonWriterTraits<ElementType>::kValueType == JsonValueType::Int ||
                                                  JsonWriterTraits<ElementType>::kValueType == JsonValueType::UInt>
    {};

    // Writes an array of elements into the specified JsonWriterContext.
    template<class T>
    void writeSpan(const ScopedArrayWriter& scoped_array_writer, std::span<const T> elements)
    {
      for (const T& element : elements)
      {
        scoped_array_writer.writeElement(element);
      }
    }
  }

  // Specialization for bool.
  template<>
  struct JsonWriterTraits<bool>
  {
    static constexpr JsonValueType kValueType = JsonValueType::Bool;

    static constexpr bool getValue(bool value) noexcept
    {
      return value;
    }
  };

  // Partial specialization for integer types.
  template<class T>
  struct JsonWriterTraits<T, std::enable_if_t<std::is_integral_v<T>>>
  {
    static constexpr JsonValueType kValueType = std::is_signed_v<T> ? JsonValueType::Int : JsonValueType::UInt;

    static constexpr T getValue(T value) noexcept
    {
      return value;
    }
  };

  // Partial specialization for enum types.
  template<class T>
  struct JsonWriterTraits<T, std::enable_if_t<std::is_enum_v<T>>>
  {
    static constexpr JsonValueType kValueType =
      std::is_signed_v<std::underlying_type_t<T>> ? JsonValueType::Int : JsonValueType::UInt;

    static constexpr std::underlying_type_t<T> getValue(T value) noexcept
    {
      return static_cast<std::underlying_type_t<T>>(value);
    }
  };

  // Specialization for std::string.
  template<>
  struct JsonWriterTraits<std::string>
  {
    static constexpr JsonValueType kValueType = JsonValueType::String;

    static const std::string& getValue(const std::string& value) noexcept
    {
      return value;
    }
  };

  // Partial specialization for std::array.
  template<class T, std::size_t N>
  struct JsonArrayWriter<std::array<T, N>>
  {
    static constexpr bool kOneElementPerLine = !Detail_NS::IsSingleLineArray<T>::value;

    void operator()(const ScopedArrayWriter& scoped_array_writer, const std::array<T, N>& elements) const
    {
      Detail_NS::writeSpan<T>(scoped_array_writer, elements);
    }
  };

  // Partial specialization for std::vector.
  template<class T, class Alloc>
  struct JsonArrayWriter<std::vector<T, Alloc>>
  {
    static constexpr bool kOneElementPerLine = !Detail_NS::IsSingleLineArray<T>::value;

    void operator()(const ScopedArrayWriter& scoped_array_writer, const std::vector<T, Alloc>& elements) const
    {
      Detail_NS::writeSpan<T>(scoped_array_writer, elements);
    }
  };
}
