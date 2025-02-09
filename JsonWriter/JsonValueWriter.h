#pragma once

#include <h3mtxt/JsonWriter/JsonDocumentWriter.h>
#include <h3mtxt/JsonWriter/ScopedArrayWriter.h>
#include <h3mtxt/JsonWriter/ScopedStructWriter.h>

#include <array>
#include <functional>
#include <map>
#include <span>
#include <string>
#include <type_traits>
#include <vector>

namespace Util_NS
{
  namespace Detail_NS
  {
    // Writes an array of elements into the specified JsonDocumentWriter.
    template<class T>
    void writeSpan(JsonDocumentWriter& out, std::span<const T> elements)
    {
      // Write an array of numbers or bytes on a single line, everything else - over multiple lines.
      constexpr bool kOneElementPerLine = !(std::is_arithmetic_v<T> || std::is_same_v<T, std::byte>);

      ScopedArrayWriter<T> scoped_array_writer = out.writeArray<T>(kOneElementPerLine);
      for (const T& element : elements)
      {
        scoped_array_writer.writeElement(element);
      }
    }

    template<class Key, class Value>
    struct KeyValCRef
    {
      std::reference_wrapper<const std::pair<const Key, Value>> data;
    };
  }

  // Class for writing *values* with indent.
  //
  // Native specializations support some common types (e.g., std::string, integer types, std::vector).
  // You can specialize it for other types.
  // The default implementation assumes that T is a structure and invokes JsonObjectWriter<T>.
  template<class T, class Enable>
  struct JsonValueWriter
  {
    void operator()(JsonDocumentWriter& out, const T& value) const;
  };

  // Writes the specified value using JsonValueWriter.
  //
  // This is simply a utility function for template argument deduction.
  //
  // \param out - output JsonDocumentWriter.
  // \param value - input value.
  template<class T>
  void writeValue(JsonDocumentWriter& out, const T& value)
  {
    JsonValueWriter<T> writer {};
    writer(out, value);
  }

  // The default implementation of JsonValueWriter.
  template<class T, class Enable>
  void JsonValueWriter<T, Enable>::operator()(JsonDocumentWriter& out, const T& value) const
  {
    JsonObjectWriter<T> struct_writer {};
    FieldsWriter fields_writer = out.writeStruct();
    struct_writer(fields_writer, value);
  }

  // Built-in specializations of JsonValueWriter.

  // Full specialization for std::string.
  template<>
  struct JsonValueWriter<std::string>
  {
    void operator()(JsonDocumentWriter& out, const std::string& value) const
    {
      out.writeString(value);
    }
  };

  // Full specialization for bool.
  template<>
  struct JsonValueWriter<bool>
  {
    void operator()(JsonDocumentWriter& out, bool value) const
    {
      out.writeBool(value);
    }
  };

  // Partial specialization for integer types.
  template<class T>
  struct JsonValueWriter<T, std::enable_if_t<std::is_integral_v<T>>>
  {
    void operator()(JsonDocumentWriter& out, T value) const
    {
      out.writeInteger(value);
    }
  };

  // Partial specialization for enum types.
  // Note that you can specialize JsonValueWriter for your enum type if you want to write
  // the names of enum constants instead of their integer values.
  template<class T>
  struct JsonValueWriter<T, std::enable_if_t<std::is_enum_v<T>>>
  {
    void operator()(JsonDocumentWriter& out, T value) const
    {
      out.writeInteger(static_cast<std::underlying_type_t<T>>(value));
    }
  };

  // Partial specialization for std::array.
  template<class T, std::size_t N>
  struct JsonValueWriter<std::array<T, N>>
  {
    void operator()(JsonDocumentWriter& out, const std::array<T, N>& vec) const
    {
      Detail_NS::writeSpan<T>(out, vec);
    }
  };

  // Partial specialization for std::vector.
  template<class T, class Alloc>
  struct JsonValueWriter<std::vector<T, Alloc>>
  {
    void operator()(JsonDocumentWriter& out, const std::vector<T, Alloc>& vec) const
    {
      Detail_NS::writeSpan<T>(out, vec);
    }
  };

  // Partial specialization for Detail_NS::KeyValCRef.
  template<class Key, class Value>
  struct JsonValueWriter<Detail_NS::KeyValCRef<Key, Value>>
  {
    void operator()(JsonDocumentWriter& out, const Detail_NS::KeyValCRef<Key, Value>& keyval) const
    {
      ScopedStructWriter fields_writer = out.writeStruct();
      fields_writer.writeField("key", keyval.data.get().first);
      fields_writer.writeField("value", keyval.data.get().second);
    }
  };

  // Partial specialization for std::map.
  // TODO: consider adding ScopedMapWriter with the printed text like:
  // my_map: {
  //   "Anna": 42,
  //   "John": 10,
  //   "Tom": 15
  // }
  // Note that entries are separated by commas unlike named fields in structures. Although, maybe
  // named fields should be separated by commas too.
  template<class Key, class Value, class Cmp, class Alloc>
  struct JsonValueWriter<std::map<Key, Value, Cmp, Alloc>>
  {
    void operator()(JsonDocumentWriter& out, const std::map<Key, Value, Cmp, Alloc>& map) const
    {
      using ElementType = Detail_NS::KeyValCRef<Key, Value>;

      ScopedArrayWriter<ElementType> scoped_array_writer = out.writeArray<ElementType>();
      for (const auto& keyval : map)
      {
        scoped_array_writer.writeElement(ElementType{keyval});
      }
    }
  };
}
