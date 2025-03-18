#pragma once

#include <h3mtxt/JsonWriter/JsonWriterFwd.h>
#include <h3mtxt/JsonWriter/ScopedArrayWriter.h>

#include <array>
#include <span>
#include <type_traits>
#include <vector>

namespace Medea_NS
{
  namespace Detail_NS
  {
    // Writes an array of elements into the specified JsonWriterContext.
    template<class T>
    void writeSpan(ScopedArrayWriter<T>& scoped_array_writer, std::span<const T> elements)
    {
      for (const T& element : elements)
      {
        scoped_array_writer.writeElement(element);
      }
    }
  }

  // Traits class providing the default policy for ScopedArrayWriter when serializing Vec as a JSON array.
  template <class Vec, class Enable = void>
  struct JsonArrayWriterTraits;

  template<class Vec>
  struct JsonArrayWriterTraits<Vec, std::void_t<typename JsonArrayWriter<Vec>::ElementType>>
  {
    using ElementType = typename JsonArrayWriter<Vec>::ElementType;

    // Write an array of numbers or bytes on a single line, everything else - over multiple lines.
    static constexpr bool kOneElementPerLine =
      !(std::is_arithmetic_v<ElementType> || std::is_same_v<ElementType, std::byte>);
  };

  // Class for serializing values as JSON arrays.
  //
  // Medea only specializes this class for 2 templates: std::array and std::vector. If you
  // want to serialize some other type as a JSON array, you need to specialize this class like this:
  //
  // template<>
  // struct JsonArrayWriter<Foo>
  // {
  //   using ElementType = Bar;
  //
  //   void operator()(ScopedArrayWriter<Bar>& scoped_array_writer, const Foo& foo) const
  //   {
  //     for (const Bar& bar : foo.elements())
  //     {
  //       scoped_array_writer.writeElement(bar);
  //     }
  //   }
  // };
  // 
  template<class Vec, class Enable>
  struct JsonArrayWriter
  {};

  // Utility function for template argument deduction.
  template<class Vec>
  void writeArray(const Vec& vec, ScopedArrayWriter<typename JsonArrayWriter<Vec>::ElementType>& scoped_array_writer)
  {
    JsonArrayWriter<Vec>{}(scoped_array_writer, vec);
  }

  // Partial specialization for std::array.
  template<class T, std::size_t N>
  struct JsonArrayWriter<std::array<T, N>>
  {
    using ElementType = T;

    void operator()(ScopedArrayWriter<T>& scoped_array_writer, const std::array<T, N>& elements) const
    {
      Detail_NS::writeSpan<T>(scoped_array_writer, elements);
    }
  };

  // Partial specialization for std::vector.
  template<class T, class Alloc>
  struct JsonArrayWriter<std::vector<T, Alloc>>
  {
    using ElementType = T;

    void operator()(ScopedArrayWriter<T>& scoped_array_writer, const std::vector<T, Alloc>& elements) const
    {
      Detail_NS::writeSpan<T>(scoped_array_writer, elements);
    }
  };
}
