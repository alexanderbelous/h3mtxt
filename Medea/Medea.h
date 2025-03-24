#pragma once

// API + built-in support for some types.

#include <h3mtxt/Medea/MedeaFwd.h>
#include <h3mtxt/Medea/ArrayElementsWriter.h>
#include <h3mtxt/Medea/FieldsWriter.h>
#include <h3mtxt/Medea/API.h>

#include <array>
#include <span>
#include <string>
#include <type_traits>
#include <vector>

namespace Medea_NS
{
  namespace Detail_NS
  {
    // Writes a span of elements without any comments.
    template<class T>
    void writeSpan(const ArrayElementsWriter& elements_writer, std::span<const T> elements)
    {
      for (const T& element : elements)
      {
        elements_writer.writeElement(element);
      }
    }
  }

  // Specialization for bool.
  template<>
  struct JsonWriterTraits<bool>
  {
    static constexpr JsonDataType kDataType = JsonDataType::Bool;

    static constexpr bool getValue(bool value) noexcept
    {
      return value;
    }
  };

  // Partial specialization for integer types.
  template<class T>
  struct JsonWriterTraits<T, std::enable_if_t<std::is_integral_v<T>>>
  {
    static constexpr JsonDataType kDataType = std::is_signed_v<T> ? JsonDataType::Int : JsonDataType::UInt;

    static constexpr T getValue(T value) noexcept
    {
      return value;
    }
  };

  // Partial specialization for enum types.
  template<class T>
  struct JsonWriterTraits<T, std::enable_if_t<std::is_enum_v<T>>>
  {
    static constexpr JsonDataType kDataType =
      std::is_signed_v<std::underlying_type_t<T>> ? JsonDataType::Int : JsonDataType::UInt;

    static constexpr std::underlying_type_t<T> getValue(T value) noexcept
    {
      return static_cast<std::underlying_type_t<T>>(value);
    }
  };

  // Specialization for std::string.
  template<>
  struct JsonWriterTraits<std::string>
  {
    static constexpr JsonDataType kDataType = JsonDataType::String;

    static const std::string& getValue(const std::string& value) noexcept
    {
      return value;
    }
  };

  // Partial specialization for std::array.
  template<class T, std::size_t N>
  struct JsonArrayWriter<std::array<T, N>>
  {
    void operator()(const ArrayElementsWriter& elements_writer, const std::array<T, N>& elements) const
    {
      Detail_NS::writeSpan<T>(elements_writer, elements);
    }
  };

  // Write std::array<T, N> on a single line by default if T is serialized as Bool, Int or UInt,
  // otherwise over multiple lines.
  template<class T, std::size_t N>
  inline constexpr bool kIsSingleLineByDefault<std::array<T, N>> = kJsonDataTypeFor<T> == JsonDataType::Bool ||
                                                                   kJsonDataTypeFor<T> == JsonDataType::Int ||
                                                                   kJsonDataTypeFor<T> == JsonDataType::UInt;

  // Partial specialization for std::vector.
  template<class T, class Alloc>
  struct JsonArrayWriter<std::vector<T, Alloc>>
  {
    void operator()(const ArrayElementsWriter& elements_writer, const std::vector<T, Alloc>& elements) const
    {
      Detail_NS::writeSpan<T>(elements_writer, elements);
    }
  };

  // Write std::vector<T, Alloc> on a single line by default if T is serialized as Bool, Int or UInt,
  // otherwise over multiple lines.
  template<class T, class Alloc>
  inline constexpr bool kIsSingleLineByDefault<std::vector<T, Alloc>> = kJsonDataTypeFor<T> == JsonDataType::Bool ||
                                                                        kJsonDataTypeFor<T> == JsonDataType::Int ||
                                                                        kJsonDataTypeFor<T> == JsonDataType::UInt;
}
