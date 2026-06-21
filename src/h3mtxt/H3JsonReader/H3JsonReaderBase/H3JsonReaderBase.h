#pragma once

// Specializes JsonReader for common types and provides a few utility functions.

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBaseFwd.h>
#include <h3mtxt/JsonCommon/FieldNamesH3M.h>
#include <h3mtxt/JsonCommon/getEnumFieldNames.h>
#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Utils/EnumBitmask.h>
#include <h3mtxt/Map/Utils/EnumIndexedArray.h>
#include <h3mtxt/Map/Utils/ReservedData.h>
#include <h3mtxt/Map/Utils/TypedQuantity.h>

#include <json/json.h>

#include <array>
#include <limits>
#include <optional>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

namespace h3json
{
  // Returns the value of the specified field of the input Json::Value.
  // \param value - input Json::Value.
  // \param field_name - the name of the requested field.
  // \return a reference to the value of the field @field_name of @value,
  //         or a NULL value if there is no such field.
  const Json::Value& getJsonField(const Json::Value& value, std::string_view field_name);

  // Same as
  //     JsonReader<T>{}(value)
  template<class T>
  T fromJson(const Json::Value& value)
  {
    return JsonReader<T>{}(value);
  }

  // Same as
  //     fromJson<T>(getJsonField(value, field_name))
  template<class T>
  T readField(const Json::Value& value, std::string_view field_name)
  {
    return fromJson<T>(getJsonField(value, field_name));
  }

  // Same as
  //     out = fromJson<T>(getJsonField(value, field_name))
  // This is useful for template argument deduction.
  template<class T>
  void readField(T& out, const Json::Value& value, std::string_view field_name)
  {
    out = readField<T>(value, field_name);
  }

  // Full specialization for bool.
  template<>
  struct JsonReader<bool>
  {
    bool operator()(const Json::Value& value) const;
  };

  // Full specialization for std::string.
  template<>
  struct JsonReader<std::string>
  {
    std::string operator()(const Json::Value& value) const;
  };

  // Partial specialization for integer types.
  template<class T>
  struct JsonReader<T, std::enable_if_t<std::is_integral_v<T>>>
  {
    T operator()(const Json::Value& value) const;
  };

  // Partial specialization for enum types.
  template<class T>
  struct JsonReader<T, std::enable_if_t<std::is_enum_v<T>>>
  {
    T operator()(const Json::Value& value) const;
  };

  // Partial specialization for std::array.
  template<class T, std::size_t N>
  struct JsonReader<std::array<T, N>>
  {
    std::array<T, N> operator()(const Json::Value& value) const;
  };

  // Partial specialization for std::vector.
  template<class T, class Alloc>
  struct JsonReader<std::vector<T, Alloc>>
  {
    std::vector<T, Alloc> operator()(const Json::Value& value) const;
  };

  // Partial specialization for std::optional.
  template<class T>
  struct JsonReader<std::optional<T>>
  {
    std::optional<T> operator()(const Json::Value& value) const;
  };

  // Partial specialization for BitSet.
  template<std::size_t NumBytes>
  struct JsonReader<h3m::BitSet<NumBytes>>
  {
    h3m::BitSet<NumBytes> operator()(const Json::Value& value) const;
  };

  // Partial specialization for ReservedData.
  template<std::size_t NumBytes>
  struct JsonReader<h3m::ReservedData<NumBytes>>
  {
    h3m::ReservedData<NumBytes> operator()(const Json::Value& value) const;
  };

  // Partial specialization for EnumBitmask.
  template<class Enum, std::size_t NumBytes>
  struct JsonReader<h3m::EnumBitmask<Enum, NumBytes>>
  {
    h3m::EnumBitmask<Enum, NumBytes> operator()(const Json::Value& value) const;
  };

  // Partial specialization for EnumIndexedArray.
  template<class Enum, class T, std::size_t NumElements>
  struct JsonReader<h3m::EnumIndexedArray<Enum, T, NumElements>>
  {
    h3m::EnumIndexedArray<Enum, T, NumElements> operator()(const Json::Value& value) const;
  };

  // Partial specialization for TypedQuantity.
  template<class Enum, class Quantity>
  struct JsonReader<h3m::TypedQuantity<Enum, Quantity>>
  {
    h3m::TypedQuantity<Enum, Quantity> operator()(const Json::Value& value) const;
  };

  // ============================================================
  // All code below is implementation details.
  // ============================================================

  namespace Detail_NS
  {
    // Checks that the given JSON value is an array with the specified number of elements.
    // \param value - input JSON value.
    // \param n - expected number of elements.
    // \throw std::runtime_error if @value is not a JSON array with @n elements.
    void checkArraySize(const Json::Value& value, std::size_t n);

    template<class T>
    void readArrayImpl(const Json::Value& value, std::span<T> elements)
    {
      const std::size_t num_elements = elements.size();
      checkArraySize(value, num_elements);
      for (std::size_t i = 0; i < num_elements; ++i)
      {
        elements[i] = fromJson<T>(value[static_cast<Json::ArrayIndex>(i)]);
      }
    }

    void readEnumBitmaskImpl(const Json::Value& value,
                             std::span<std::uint8_t> bitset_bytes,
                             const std::string_view* field_names);

    template<class T>
    void readEnumIndexedArrayImpl(const Json::Value& value,
                                  std::span<T> elements,
                                  const std::string_view* field_names)
    {
      const std::size_t num_elements = elements.size();
      for (std::size_t i = 0; i < num_elements; ++i)
      {
        elements[i] = readField<T>(value, field_names[i]);
      }
    }
  }

  template<class T>
  T JsonReader<T, std::enable_if_t<std::is_integral_v<T>>>::operator()(const Json::Value& value) const
  {
    using LargestInt = std::conditional_t<std::is_signed_v<T>, Json::LargestInt, Json::LargestUInt>;
    if (!value.isIntegral())
    {
      throw std::runtime_error("JsonReader: expected an integral type, got " + value.toStyledString());
    }
    LargestInt integral_value{};
    if constexpr (std::is_signed_v<T>)
    {
      integral_value = value.asLargestInt();
    }
    else
    {
      integral_value = value.asLargestUInt();
    }
    // Check that the number fits in T.
    if (integral_value > std::numeric_limits<T>::max() || integral_value < std::numeric_limits<T>::min())
    {
      throw std::runtime_error("JsonReader: value is out of range: " + std::to_string(integral_value));
    }
    return static_cast<T>(integral_value);
  }

  template<class T>
  T JsonReader<T, std::enable_if_t<std::is_enum_v<T>>>::operator()(const Json::Value& value) const
  {
    return static_cast<T>(fromJson<std::underlying_type_t<T>>(value));
  }

  template<class T, std::size_t N>
  std::array<T, N> JsonReader<std::array<T, N>>::operator()(const Json::Value& value) const
  {
    std::array<T, N> result;
    Detail_NS::readArrayImpl<T>(value, result);
    return result;
  }

  template<class T, class Alloc>
  std::vector<T, Alloc> JsonReader<std::vector<T, Alloc>>::operator()(const Json::Value& value) const
  {
    if (!value.isArray())
    {
      throw std::runtime_error("JsonReader: expected array, got " + value.toStyledString());
    }
    const std::size_t num_elements = value.size();
    std::vector<T, Alloc> result;
    result.reserve(num_elements);
    for (std::size_t i = 0; i < num_elements; ++i)
    {
      result.push_back(fromJson<T>(value[static_cast<Json::ArrayIndex>(i)]));
    }
    return result;
  }

  template<class T>
  std::optional<T> JsonReader<std::optional<T>>::operator()(const Json::Value& value) const
  {
    if (value.isNull())
    {
      return std::nullopt;
    }
    return fromJson<T>(value);
  }

  template<std::size_t NumBytes>
  h3m::BitSet<NumBytes> JsonReader<h3m::BitSet<NumBytes>>::operator()(const Json::Value& value) const
  {
    return h3m::BitSet<NumBytes>{fromJson<std::array<std::uint8_t, NumBytes>>(value)};
  }

  template<std::size_t NumBytes>
  h3m::ReservedData<NumBytes> JsonReader<h3m::ReservedData<NumBytes>>::operator()(const Json::Value& value) const
  {
    std::array<std::byte, NumBytes> data = fromJson<std::array<std::byte, NumBytes>>(value);
    if (h3m::Detail_NS::isAllZeroes(data))
    {
      return h3m::ReservedData<NumBytes>();
    }
    return h3m::ReservedData<NumBytes>(data);
  }

  template<class Enum, std::size_t NumBytes>
  h3m::EnumBitmask<Enum, NumBytes>
  JsonReader<h3m::EnumBitmask<Enum, NumBytes>>::operator()(const Json::Value& value) const
  {
    constexpr std::span<const std::string_view, NumBytes * 8> kNames =
      getEnumFieldNames<Enum, NumBytes * 8>();

    h3m::EnumBitmask<Enum, NumBytes> bitmask;
    Detail_NS::readEnumBitmaskImpl(value, bitmask.bitset.data, kNames.data());
    return bitmask;
  }

  template<class Enum, class T, std::size_t NumElements>
  h3m::EnumIndexedArray<Enum, T, NumElements>
  JsonReader<h3m::EnumIndexedArray<Enum, T, NumElements>>::operator()(const Json::Value& value) const
  {
    constexpr std::span<const std::string_view, NumElements> kNames =
      getEnumFieldNames<Enum, NumElements>();

    h3m::EnumIndexedArray<Enum, T, NumElements> enum_indexed_array;
    Detail_NS::readEnumIndexedArrayImpl(value, std::span<T>{ enum_indexed_array.data }, kNames.data());
    return enum_indexed_array;
  }

  template<class Enum, class Quantity>
  h3m::TypedQuantity<Enum, Quantity>
  JsonReader<h3m::TypedQuantity<Enum, Quantity>>::operator()(const Json::Value& value) const
  {
    using Fields = FieldNames<h3m::TypedQuantity<Enum, Quantity>>;
    h3m::TypedQuantity<Enum, Quantity> result;
    readField(result.type, value, Fields::kType);
    readField(result.quantity, value, Fields::kQuantity);
    return result;
  }
}
