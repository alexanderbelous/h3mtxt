#pragma once

// TODO: rename to Medea_NS
namespace Util_NS
{
  // Class for writing JSON documents.
  class JsonDocumentWriter;

  class ScopedArrayWriterBase;

  template<class T>
  class ScopedArrayWriter;

  class ScopedStructWriter;

  using FieldsWriter = ScopedStructWriter;

  // Class for writing JSON values.
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
  struct JsonValueWriter;

  // Class for writing JSON objects.
  //
  // This template can be specialized for user-defined types that
  // should be serialized as JSON objects.
  template<class T, class Enable = void>
  struct JsonObjectWriter;
  // {
  //   void operator()(FieldsWriter& out, const T& value);
  // };
}
