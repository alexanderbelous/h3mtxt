#pragma once

// API + built-in support for some types.

#include <h3mtxt/Medea/MedeaFwd.h>
#include <h3mtxt/Medea/ArrayElementsWriter.h>
#include <h3mtxt/Medea/Core.h>
#include <h3mtxt/Medea/FieldsWriter.h>

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

  // Serialize the fundamental type `bool` as JsonDataType::Bool.
  template<>
  inline constexpr JsonDataType kJsonDataTypeFor<bool> = JsonDataType::Bool;

  template<>
  struct JsonScalarGetter<bool>
  {
    constexpr bool operator()(bool value) const noexcept
    {
      return value;
    }
  };

  // Serialize fundamental integral types (except bool) as either JsonDataType::Int or JsonDataType::UInt.
  template<class T>
  inline constexpr JsonDataType kJsonDataTypeFor<T, std::enable_if_t<std::is_integral_v<T>>> =
    std::is_signed_v<T> ? JsonDataType::Int : JsonDataType::UInt;

  template<class T>
  struct JsonScalarGetter<T, std::enable_if_t<std::is_integral_v<T>>>
  {
    using ResultType = std::conditional_t<std::is_signed_v<T>, std::intmax_t, std::uintmax_t>;

    constexpr ResultType operator()(T value) const noexcept
    {
      return static_cast<ResultType>(value);
    }
  };

  // Serialize enumeration types as either JsonDataType::Int or JsonDataType::UInt,
  // depending on their underlying type.
  template<class T>
  inline constexpr JsonDataType kJsonDataTypeFor<T, std::enable_if_t<std::is_enum_v<T>>> =
    std::is_signed_v<std::underlying_type_t<T>> ? JsonDataType::Int : JsonDataType::UInt;

  template<class T>
  struct JsonScalarGetter<T, std::enable_if_t<std::is_enum_v<T>>>
  {
    using UnderlyingType = std::underlying_type_t<T>;
    using ResultType = std::conditional_t<std::is_signed_v<UnderlyingType>, std::intmax_t, std::uintmax_t>;

    constexpr ResultType operator()(T value) const noexcept
    {
      return static_cast<ResultType>(value);
    }
  };

  // Serialize std::string as JsonDataType::String.
  template<>
  inline constexpr JsonDataType kJsonDataTypeFor<std::string> = JsonDataType::String;

  template<>
  struct JsonScalarGetter<std::string>
  {
    constexpr const std::string& operator()(const std::string& value) const noexcept
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
