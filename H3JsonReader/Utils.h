#pragma once

#include <h3mtxt/H3JsonReader/H3JsonReader.h>
#include <h3mtxt/Map/Utils/BitSet.h>
#include <h3mtxt/Map/Utils/ReservedData.h>

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

namespace h3m::H3JsonReader_NS
{
  namespace Detail_NS
  {
    template<class T>
    struct IsOptionalImpl : std::false_type {};

    template<class T>
    struct IsOptionalImpl<std::optional<T>> : std::true_type {};

    template<class T>
    inline constexpr bool IsOptional = IsOptionalImpl<T>::value;

    template<class T>
    struct RemoveOptionalImpl
    {
      using type = T;
    };

    template<class T>
    struct RemoveOptionalImpl<std::optional<T>>
    {
      using type = T;
    };

    template<class T>
    using RemoveOptional = typename RemoveOptionalImpl<T>::type;

    template<class T>
    void readArrayImpl(const Json::Value& value, std::span<T> elements)
    {
      const std::size_t num_elements = elements.size();
      if (!value.isArray())
      {
        throw std::runtime_error("readH3mJson(): expected array, got " + value.toStyledString());
      }
      if (value.size() != num_elements)
      {
        throw std::runtime_error("readH3mJson(): expected array of " + std::to_string(num_elements) +
                                 " elements, got an array of " + std::to_string(value.size()) + " elements");
      }
      T* data = elements.data();
      for (std::size_t i = 0; i < num_elements; ++i)
      {
        data[i] = fromJson<T>(value[static_cast<Json::ArrayIndex>(i)]);
      }
    }
  }

  class MissingJsonFieldError : public std::runtime_error
  {
  public:
    explicit MissingJsonFieldError(std::string_view field_name):
      std::runtime_error("readH3mJson(): missing field " + std::string(field_name))
    {}
  };

  const Json::Value& getJsonField(const Json::Value& value, std::string_view field_name);

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
  // \return the field @field_name of @value deserialized as T,
  //         or std::nullopt if T is an instantiation of std::optional and
  //         @value doesn't have a field a named @field_name.
  // \throw MissingJsonFieldError if T is not an instantiation of std::optional and
  //        @value doesn't have a field a named @field_name.
  template<class T>
  T readField(const Json::Value& value, std::string_view field_name)
  {
    if (const Json::Value* field = value.find(field_name.data(), field_name.data() + field_name.size()))
    {
      return fromJson<Detail_NS::RemoveOptional<T>>(*field);
    }
    if constexpr (Detail_NS::IsOptional<T>)
    {
      return std::nullopt;
    }
    else
    {
      throw MissingJsonFieldError(field_name);
    }
  }

  // Same as above, but assigns the deserialized value to the output parameter.
  // This is useful for template argument deduction.
  template<class T>
  void readField(T& out, const Json::Value& value, std::string_view field_name)
  {
    out = readField<T>(value, field_name);
  }

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
  struct JsonReader<T, std::enable_if_t<std::is_enum_v<T>>>
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
      std::array<T, N> result;
      Detail_NS::readArrayImpl<T>(value, result);
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
      return BitSet<NumBytes>{fromJson<std::array<std::uint8_t, NumBytes>>(value)};
    }
  };

  // Partial specialization for ReservedData.
  template<std::size_t NumBytes>
  struct JsonReader<ReservedData<NumBytes>>
  {
    ReservedData<NumBytes> operator()(const Json::Value& value) const
    {
      std::array<std::byte, NumBytes> data = fromJson<std::array<std::byte, NumBytes>>(value);
      if (h3m::Detail_NS::isAllZeros(data))
      {
        return ReservedData<NumBytes>();
      }
      return ReservedData<NumBytes>(data);
    }
  };
}
