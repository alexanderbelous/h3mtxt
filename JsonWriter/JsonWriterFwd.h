#pragma once

#include <type_traits>

namespace Medea_NS
{
  namespace Detail_NS
  {
    // Internal class for writing formatted JSON.
    class JsonWriterContext;
  }

  // Supported JSON value types.
  enum class JsonValueType
  {
    Bool,
    Int,
    UInt,
    String,
    Array,
    Object
  };

  class ScopedArrayWriter;

  class ScopedObjectWriter;

  using FieldsWriter = ScopedObjectWriter;

  // Class for writing JSON arrays.
  template<class T, class Enable = void>
  struct JsonArrayWriter {};
  //{
  //  // Optional; if missing, implies true.
  //  static constexpr bool kOneElementPerLine = false;
  //
  //  void operator()(const ScopedArrayWriter& out, const T& elements) const;
  //};

  // Class for writing JSON objects.
  //
  // This template can be specialized for user-defined types that
  // should be serialized as JSON objects.
  template<class T, class Enable = void>
  struct JsonObjectWriter
  {
    void operator()(FieldsWriter& out, const T& value) const;
  };

  // Type trait indicating how the given type should be serialized in JSON.
  //
  // The default implementation of JsonWriterTraits assumes that the type T should be serialized as a JSON object.
  //
  // BuilInTypes.h provides built-in specializations for a few types (e.g., bool, std::string, std::vector)
  // and assumes that all other types should be serialized as JSON objects. If the type T
  // should not be serialized as a JSON object, this trait should be specialized for T.
  template<class T, class Enable = void>
  struct JsonWriterTraits
  {
    static constexpr JsonValueType kValueType = JsonValueType::Object;
  };

  // Partial specialization for types for which JsonArrayWriter<T> can be invoked.
  template<class T>
  struct JsonWriterTraits<T, std::enable_if_t<std::is_invocable_v<JsonArrayWriter<T>, const ScopedArrayWriter&, const T&>>>
  {
    static constexpr JsonValueType kValueType = JsonValueType::Array;
  };
}
