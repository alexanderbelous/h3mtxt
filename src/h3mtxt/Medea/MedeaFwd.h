#pragma once

#include <type_traits>

namespace Medea_NS
{
  // Supported JSON data types.
  enum class JsonDataType
  {
    Bool,
    Int,
    UInt,
    String,
    Array,
    Object
  };

  class ArrayElementsWriter;

  class FieldsWriter;

  // Class for writing JSON arrays.
  //
  // This template can be specialized for types that should be serialized as JSON arrays.
  template<class T, class Enable = void>
  struct JsonArrayWriter
  {
    // The function doesn't have to be const-qualified.
    void operator()(const ArrayElementsWriter& out, const T& elements) const = delete;
  };

  // Class for writing JSON objects.
  //
  // This template can be specialized for types that should be serialized as JSON objects.
  template<class T, class Enable = void>
  struct JsonObjectWriter
  {
    // The function doesn't have to be const-qualified.
    void operator()(FieldsWriter& out, const T& value) const = delete;
  };

  // Class for getting the scalar value for types that should be serialized as a scalar JSON data type.
  //
  // This template can be specialized for types that should be serialized as neither Array nor Object.
  // See Medea.h for the examples.
  template<class T, class Enable = void>
  struct JsonScalarGetter
  {
    // The function doesn't have to be const-qualified.
    // The type of the returned value depends on kJsonDataTypeFor<T>:
    //   * For types serialized as JsonDataType::Bool, it must be (a possibly cvref-qualified) bool.
    //   * For types serialized as JsonDataType::Int, it must be a (possibly cvref-qualified) signed integral type.
    //   * For types serialized as JsonDataType::UInt, it must be a (possibly cvref-qualified) unsigned integral type.
    //   * For types serialized as JsonDataType::String, it must be some type convertible to std::string_view
    //     (it's not required to be std::string_view itself to support the case where the string is returned
    //     by value).
    // ResultType operator()(const T& value) const;
  };

  // Variable template storing JsonDataType for the specified type T.
  //
  // The default implementation assumes that all types should be serialized as JSON objects.
  // The partial specialization below overrides this for types for which JsonArrayWriter<T> can be invoked.
  //
  // Medea.h specializes this template for a few types (e.g., bool, integral types, enums, std::string),
  // but that header is optional.
  //
  // The user may add full or partial specializations for this variable template.
  template<class T, class Enable = void>
  inline constexpr JsonDataType kJsonDataTypeFor = JsonDataType::Object;

  // Partial specialization for types for which JsonArrayWriter<T> can be invoked.
  template<class T>
  inline constexpr JsonDataType kJsonDataTypeFor<T, std::enable_if_t<
    std::is_invocable_v<JsonArrayWriter<T>, const ArrayElementsWriter&, const T&>>> = JsonDataType::Array;

  // Stores true if values of type T should be serialized on a single line by default, false otherwise.
  //
  // The user may add full or partial specializations for this variable template.
  template<class T, class Enable = void>
  inline constexpr bool kIsSingleLineByDefault = false;
}
