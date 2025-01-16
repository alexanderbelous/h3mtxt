#pragma once

#include <h3mtxt/TextWriter/ScopedArrayWriter.h>
#include <h3mtxt/TextWriter/ScopedStructWriter.h>
#include <h3mtxt/TextWriter/TextWriter.h>

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
    // Writes an array of elements into the specified IndentedTextWriter.
    template<class T>
    void writeSpan(IndentedTextWriter& out, std::span<const T> elements)
    {
      ScopedArrayWriter<T> scoped_array_writer = out.writeArray<T>();
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
  // The default implementation assumes that T is a structure and invokes StructWriter<T>.
  template<class T, class Enable>
  struct ValueWriter
  {
    void operator()(IndentedTextWriter& out, const T& value) const;
  };

  // Writes the specified value using ValueWriter.
  //
  // This is simply a utility function for template argument deduction.
  //
  // \param out - output IndentedTextWriter.
  // \param value - input value.
  template<class T>
  void writeValue(IndentedTextWriter& out, const T& value)
  {
    ValueWriter<T> writer {};
    writer(out, value);
  }

  // The default implementation of ValueWriter.
  template<class T, class Enable>
  void ValueWriter<T, Enable>::operator()(IndentedTextWriter& out, const T& value) const
  {
    StructWriter<T> struct_writer {};
    FieldsWriter fields_writer = out.writeStruct();
    struct_writer(fields_writer, value);
  }

  // Built-in specializations of ValueWriter.

  // Full specialization for std::string.
  template<>
  struct ValueWriter<std::string>
  {
    void operator()(IndentedTextWriter& out, const std::string& value) const
    {
      out.writeString(value);
    }
  };

  // Partial specialization for integer types.
  template<class T>
  struct ValueWriter<T, std::enable_if_t<std::is_integral_v<T>>>
  {
    void operator()(IndentedTextWriter& out, T value) const
    {
      out.writeInteger(value);
    }
  };

  // Partial specialization for enum types.
  // Note that you can specialize ValueWriter for your enum type if you want to write
  // the names of enum constants instead of their integer values.
  template<class T>
  struct ValueWriter<T, std::enable_if_t<std::is_enum_v<T>>>
  {
    void operator()(IndentedTextWriter& out, T value) const
    {
      out.writeInteger(static_cast<std::underlying_type_t<T>>(value));
    }
  };

  // Partial specialization for std::array.
  template<class T, std::size_t N>
  struct ValueWriter<std::array<T, N>>
  {
    void operator()(IndentedTextWriter& out, const std::array<T, N>& vec) const
    {
      Detail_NS::writeSpan<T>(out, vec);
    }
  };

  // Partial specialization for std::vector.
  template<class T, class Alloc>
  struct ValueWriter<std::vector<T, Alloc>>
  {
    void operator()(IndentedTextWriter& out, const std::vector<T, Alloc>& vec) const
    {
      Detail_NS::writeSpan<T>(out, vec);
    }
  };

  // Partial specialization for Detail_NS::KeyValCRef.
  template<class Key, class Value>
  struct ValueWriter<Detail_NS::KeyValCRef<Key, Value>>
  {
    void operator()(IndentedTextWriter& out, const Detail_NS::KeyValCRef<Key, Value>& keyval) const
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
  struct ValueWriter<std::map<Key, Value, Cmp, Alloc>>
  {
    void operator()(IndentedTextWriter& out, const std::map<Key, Value, Cmp, Alloc>& map) const
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
