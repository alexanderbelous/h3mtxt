#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>

#include <string>
#include <type_traits>

namespace Medea_NS
{
  // Defines supported JSON value types.
  enum class JsonValueType
  {
    Bool,
    Int,
    UInt,
    String,
    Array,
    Object
  };

  // The default implementation of JsonWriterTraits assumes that the type T should be serialized as a JSON object.
  template<class T, class Enable>
  struct JsonWriterTraits
  {
    static constexpr JsonValueType kValueType = JsonValueType::Object;
  };

  // Traits class indicating whether arrays of elements of type T should be serialized
  // with one element per line or on a single line.
  //
  // The default implementation stores true for types that are serialized as Bool, Int or UInt,
  // false for everything else.
  template <class ElementType, class Enable>
  struct IsSingleLineArray : std::bool_constant<JsonWriterTraits<ElementType>::kValueType == JsonValueType::Bool ||
                                                JsonWriterTraits<ElementType>::kValueType == JsonValueType::Int ||
                                                JsonWriterTraits<ElementType>::kValueType == JsonValueType::UInt>
  {};

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

  // Partial specialization for types T for which JsonArrayWriter<T> has a nested ::ElementType member.
  template<class T>
  struct JsonWriterTraits<T, std::void_t<typename JsonArrayWriter<T>::ElementType>>
  {
    static constexpr JsonValueType kValueType = JsonValueType::Array;
  };
}
