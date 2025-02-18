#pragma once

#include <h3mtxt/JsonWriter/JsonDocumentWriter.h>
#include <h3mtxt/JsonWriter/ScopedArrayWriter.h>
#include <h3mtxt/JsonWriter/ScopedObjectWriter.h>

#include <array>
#include <span>
#include <string>
#include <type_traits>
#include <vector>

namespace Medea_NS
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
    FieldsWriter fields_writer = out.writeObject();
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
}
