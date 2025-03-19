#pragma once

namespace Medea_NS
{
  namespace Detail_NS
  {
    // Internal class for writing formatted JSON.
    class JsonWriterContext;

    // Serializes the given value as formatted JSON.
    template<class T>
    void writeValueRaw(JsonWriterContext& context, const T& value);
  }

  // Defines supported JSON value types.
  enum class JsonValueType;

  // Type trait indicating how the given type should be serialized in JSON.
  //
  // Medea provides built-in specializations for a few types (e.g., std::string, std::vector)
  // and assumes that all other types should be serialized as JSON objects. If the type T
  // should not be serialized as a JSON object, this trait should be specialized for T.
  template<class T, class Enable = void>
  struct JsonWriterTraits;

  template<class T>
  class ScopedArrayWriter;

  class ScopedObjectWriter;

  using FieldsWriter = ScopedObjectWriter;

  // Class for writing JSON arrays.
  template<class T, class Enable = void>
  struct JsonArrayWriter;
  //{
  //  using ElementType = ...;
  //
  //  void operator()(ScopedArrayWriter<ElementType>& out, const T& elements) const;
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
}
