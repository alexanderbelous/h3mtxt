#pragma once

#include <h3mtxt/Map/Utils/BitSet.h>

#include <json/json.h>

#include <array>
#include <limits>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

namespace h3m
{
  // Template class for deserializing Json::Value into the specified type.
  template<class T, class Enable = void>
  struct JsonReader
  {
    static_assert(false, "NotImplemented.");
  };

  // Utility wrapper for JsonReader.
  // \param value - input JSON value.
  // \return the value of type T deserialized from @value using JsonReader<T>.
  template<class T>
  T fromJson(const Json::Value& value)
  {
    return JsonReader<T>{}(value);
  }

  // Utility function for parsing a single field of the input JSON value.
  // \param value - input JSON value.
  // \param field_name - name of the field.
  // \return the value of the specified field as T.
  // \throw std::runtime_error if @value doesn't have a field named @field_name.
  template<class T>
  T readField(const Json::Value& value, std::string_view field_name)
  {
    if (const Json::Value* field = value.find(field_name.data(), field_name.data() + field_name.size()))
    {
      return fromJson<T>(*field);
    }
    throw std::runtime_error("readH3mJson(): missing field " + std::string(field_name));
  }

  // Utility function for reading optional fields.
  template<class T>
  std::optional<T> readOptionalField(const Json::Value& value, std::string_view field_name)
  {
    if (const Json::Value* field = value.find(field_name.data(), field_name.data() + field_name.size()))
    {
      return fromJson<T>(*field);
    }
    return std::nullopt;
  }

  // Full specialization for bool.
  template<>
  struct JsonReader<bool>
  {
    bool operator()(const Json::Value& value) const
    {
      if (!value.isBool())
      {
        throw std::runtime_error("readH3mJson(): expected bool, got " + value.toStyledString());
      }
      return value.asBool();
    }
  };

  // Full specialization for std::string.
  template<>
  struct JsonReader<std::string>
  {
    std::string operator()(const Json::Value& value) const
    {
      if (!value.isString())
      {
        throw std::runtime_error("readH3mJson(): expected std::string, got " + value.toStyledString());
      }
      return value.asString();
    }
  };

  // Partial specialization for integer types.
  template<class T>
  struct JsonReader <T, std::enable_if_t<std::is_integral_v<T>>>
  {
    T operator()(const Json::Value& value) const
    {
      using LargestInt = std::conditional_t<std::is_signed_v<T>, Json::LargestInt, Json::LargestUInt>;
      if (!value.isIntegral())
      {
        throw std::runtime_error("readH3mJson(): expected an integral type, got " + value.toStyledString());
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
        throw std::runtime_error("readH3mJson(): value is out of range: " + std::to_string(integral_value));
      }
      return static_cast<T>(integral_value);
    }
  };

  // Partial specialization for enum types.
  template<class T>
  struct JsonReader <T, std::enable_if_t<std::is_enum_v<T>>>
  {
    T operator()(const Json::Value& value) const
    {
      return static_cast<T>(fromJson<std::underlying_type_t<T>>(value));
    }
  };

  // Partial specialization for std::array.
  template<class T, std::size_t N>
  struct JsonReader<std::array<T, N>>
  {
    std::array<T, N> operator()(const Json::Value& value) const
    {
      if (!value.isArray())
      {
        throw std::runtime_error("readH3mJson(): expected array, got " + value.toStyledString());
      }
      if (value.size() != N)
      {
        throw std::runtime_error("readH3mJson(): expected array of " + std::to_string(N) +
                                  " elements, got an array of " + std::to_string(value.size()) + " elements");
      }
      std::array<T, N> result;
      for (std::size_t i = 0; i < N; ++i)
      {
        result[i] = fromJson<T>(value[static_cast<Json::ArrayIndex>(i)]);
      }
      return result;
    }
  };

  // Partial specialization for std::vector.
  template<class T, class Alloc>
  struct JsonReader<std::vector<T, Alloc>>
  {
    std::vector<T, Alloc> operator()(const Json::Value& value) const
    {
      if (!value.isArray())
      {
        throw std::runtime_error("readH3mJson(): expected array, got " + value.toStyledString());
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
  };

  // Partial specialization for BitSet.
  template<std::size_t NumBytes>
  struct JsonReader<BitSet<NumBytes>>
  {
    BitSet<NumBytes> operator()(const Json::Value& value) const
    {
      return BitSet<NumBytes>(fromJson<std::array<std::uint8_t, NumBytes>>(value));
    }
  };
}
