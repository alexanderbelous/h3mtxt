#pragma once

#include <h3mparser/TextWriter/TextWriter.h>

#include <array>
#include <map>
#include <string>
#include <type_traits>
#include <vector>

namespace Util_NS
{
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
    IndentedTextWriter::ScopedFieldsWriter fields_writer = out.writeStruct();
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
      out.writeArray<T>(vec);
    }
  };

  // Partial specialization for std::vector.
  template<class T, class Alloc>
  struct ValueWriter<std::vector<T, Alloc>>
  {
    void operator()(IndentedTextWriter& out, const std::vector<T, Alloc>& vec) const
    {
      out.writeArray<T>(vec);
    }
  };

  // Partial specialization for std::map.
  template<class Key, class Value, class Cmp, class Alloc>
  struct ValueWriter<std::map<Key, Value, Cmp, Alloc>>
  {
    void operator()(IndentedTextWriter& out, const std::map<Key, Value, Cmp, Alloc>& map) const
    {
      out.writeMap(map);
    }
  };
}
