#pragma once

namespace Medea_NS
{
  // Class for writing JSON documents.
  class JsonDocumentWriter;

  class ScopedArrayWriterBase;

  template<class T>
  class ScopedArrayWriter;

  class ScopedObjectWriter;

  using FieldsWriter = ScopedObjectWriter;

  // Class for writing JSON values.
  //
  // The default implementation assumes that T should be serialized as a JSON object and invokes JsonObjectWriter<T>.
  //
  // JsonValueWriter.h provides specializations for some types:
  // * All integral types
  // * All enum types
  // * std::string
  // * std::array
  // * std::vector
  //
  // This template can be specialized for user-defined types that
  // should not be serialized as JSON Objects (e.g., a custom array-like class).
  template<class T, class Enable = void>
  struct JsonValueWriter
  {
    void operator()(JsonDocumentWriter& out, const T& value) const;
  };

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
