#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>
#include <h3mtxt/JsonWriter/JsonArrayWriter.h>
#include <h3mtxt/JsonWriter/JsonWriterContext.h>
#include <h3mtxt/JsonWriter/JsonWriterTraits.h>
#include <h3mtxt/JsonWriter/ScopedArrayWriter.h>
#include <h3mtxt/JsonWriter/ScopedObjectWriter.h>

#include <string_view>
#include <type_traits>

namespace Medea_NS
{
  namespace Detail_NS
  {
    // Serializes the given value as JSON.
    // \param context - output JsonWriterContext.
    // \param value - input value.
    template<class T>
    void writeValue(JsonWriterContext& context, const T& value)
    {
      using Traits = JsonWriterTraits<T>;

      if constexpr (Traits::kValueType == JsonValueType::Bool)
      {
        using GetValueResultType = decltype(Traits::getValue(value));
        static_assert(std::is_same_v<GetValueResultType, bool>,
                      "JsonWriterTraits<T>::getValue(value) must return bool.");
        context.writeBool(Traits::getValue(value));
      }
      else if constexpr (Traits::kValueType == JsonValueType::Int)
      {
        using GetValueResultType = decltype(Traits::getValue(value));
        //static_assert(std::is_integeral_v<GetValueResultType> && std::is_signed_v<GetValueResultType>,
        //              "JsonWriterTraits<T>::getValue(value) must return a signed integer.");
        context.writeInt(static_cast<std::intmax_t>(Traits::getValue(value)));
      }
      else if constexpr (Traits::kValueType == JsonValueType::UInt)
      {
        using GetValueResultType = decltype(Traits::getValue(value));
        //static_assert(std::is_integeral_v<GetValueResultType> && std::is_unsigned_v<GetValueResultType>,
        //              "JsonWriterTraits<T>::getValue(value) must return an unsigned integer.");
        context.writeUInt(static_cast<std::uintmax_t>(Traits::getValue(value)));
      }
      else if constexpr (Traits::kValueType == JsonValueType::String)
      {
        using GetValueResultType = decltype(Traits::getValue(value));
        //static_assert(std::is_convertible_v<GetValueResultType, std::string_view>,
        //              "JsonWriterTraits<T>::getValue(value) must be convertible to std::string_view.");
        context.writeString(Traits::getValue(value));
      }
      else if constexpr (Traits::kValueType == JsonValueType::Array)
      {
        using ElementType = typename JsonArrayWriter<T>::ElementType;
        JsonArrayWriter<T> array_writer {};
        ScopedArrayWriter<ElementType> elements_writer{ context, JsonArrayWriterTraits<T>::kOneElementPerLine };
        array_writer(elements_writer, value);
      }
      else if constexpr (Traits::kValueType == JsonValueType::Object)
      {
        JsonObjectWriter<T> object_writer {};
        ScopedObjectWriter fields_writer{ context };
        object_writer(fields_writer, value);
      }
      else
      {
        static_assert(false, "Invalid JsonWriterTraits<T>::kValueType.");
      }
    }
  }
}
