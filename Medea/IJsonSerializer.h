#pragma once

#include <h3mtxt/Medea/MedeaFwd.h>

#include <cstdint>
#include <memory>
#include <string_view>
#include <type_traits>

namespace Medea_NS
{
  // Interface for JSON serialization.
  //
  // IJsonSerializer is just an interface, it doesn't specify "what" the output is.
  // Concrete implementations can, for example:
  // * Print formatted JSON to std::ostream.
  // * Print minified JSON to std::ostream.
  // * Construct a Json::Value from JsonCpp library.
  // * Construct a nlohmann::json from nlohmann/json library.
  // * Convert a JSON object from one library into a JSON object from another library.
  // * ...
  //
  // This is convenient because the user only needs to provide specializations for
  // JsonObjectWriter / JsonArrayWriter, which can be reused by each implementation of IJsonSerializer..
  class IJsonSerializer
  {
  public:
    // Non-copyable, non-movable.
    IJsonSerializer(const IJsonSerializer&) = delete;
    IJsonSerializer(IJsonSerializer&&) = delete;
    IJsonSerializer& operator=(const IJsonSerializer&) = delete;
    IJsonSerializer& operator=(IJsonSerializer&&) = delete;

    virtual ~IJsonSerializer() = default;

    // Writes a comment.
    // \param comment - comment to write. Empty comments are ignored.
    // \param newline - if true, the comment will be written on a new line,
    //        otherwise on the same line as the last printed entry.
    //        This parameter is ignored if !comment_.empty() - in that case @comment will be appended to
    //        comment_ after a newline character.
    virtual void writeComment(std::string_view comment, bool newline) = 0;

    // Serializes an array element in the current context.
    template<class T>
    void writeArrayElement(const T& value, bool single_line);

    // Serializes an object field in the current context.
    template<class T>
    void writeField(std::string_view field_name, const T& value, bool single_line);

  protected:
    // Type-erased version of JsonArrayWriter<T>.
    using ArrayWriterPtr = void(*)(const ArrayElementsWriter&, const void*);
    // Type-erased version of JsonObjectWriter<T>.
    using ObjectWriterPtr = void(*)(FieldsWriter&, const void*);

    constexpr IJsonSerializer() noexcept = default;

    template<class T>
    void writeValueRaw(const T& value, bool single_line);

  private:
    // Signals that a new array element or a new object field is about to be serialized.
    // TODO: this is somewhat redundant - implementations can deduce this when any of the virtual
    // functions below is called. Consider removing.
    virtual void beforeWriteElementOrField() = 0;

    // Serializes a boolean value in the current context.
    virtual void writeBool(bool value) = 0;

    // Serializes a signed integer value in the current context.
    virtual void writeInt(std::intmax_t value) = 0;

    // Serializes an unsigned integer value in the current context.
    virtual void writeUInt(std::uintmax_t value) = 0;

    // Serializes a string value in the current context.
    virtual void writeString(std::string_view value) = 0;

    // Serializes an array value in the current context.
    virtual void writeArray(ArrayWriterPtr array_writer, const void* value, bool single_line) = 0;

    // Serializes an object value in the current context.
    virtual void writeObject(ObjectWriterPtr object_writer, const void* value, bool single_line) = 0;

    // Starts serializing an object field in the current context.
    virtual void writeFieldName(std::string_view field_name) = 0;
  };

  template<class T>
  void IJsonSerializer::writeValueRaw(const T& value, bool single_line)
  {
    constexpr JsonDataType kDataType = kJsonDataTypeFor<std::remove_cvref_t<T>>;

    if constexpr (kDataType == JsonDataType::Bool)
    {
      using ScalarGetter = JsonScalarGetter<std::remove_cvref_t<T>>;
      static_assert(std::is_invocable_v<ScalarGetter, const T&>,
                    "This type should be serialized as JsonDataType::Bool, but "
                    "JsonScalarGetter is not invokable for this type. Have you forgotten to specialize it?");
      static_assert(std::is_same_v<std::remove_cvref_t<std::invoke_result_t<ScalarGetter, const T&>>, bool>,
                    "This type should be serialized as JsonDataType::Bool, but "
                    "JsonScalarGetter returns a value that isn't bool.");
      writeBool(ScalarGetter{}(value));
    }
    else if constexpr (kDataType == JsonDataType::Int)
    {
      using ScalarGetter = JsonScalarGetter<std::remove_cvref_t<T>>;
      static_assert(std::is_invocable_v<ScalarGetter, const T&>,
                    "This type should be serialized as JsonDataType::Int, but "
                    "JsonScalarGetter is not invokable for this type. Have you forgotten to specialize it?");
      using ScalarGetterResult = std::remove_cvref_t<std::invoke_result_t<ScalarGetter, const T&>>;
      static_assert(std::is_integral_v<ScalarGetterResult> && std::is_signed_v<ScalarGetterResult>,
                    "This type should be serialized as JsonDataType::Int, but "
                    "JsonScalarGetter returns a value that isn't a signed integer.");
      writeInt(static_cast<std::intmax_t>(ScalarGetter{}(value)));
    }
    else if constexpr (kDataType == JsonDataType::UInt)
    {
      using ScalarGetter = JsonScalarGetter<std::remove_cvref_t<T>>;
      static_assert(std::is_invocable_v<ScalarGetter, const T&>,
                    "This type should be serialized as JsonDataType::UInt, but "
                    "JsonScalarGetter is not invokable for this type. Have you forgotten to specialize it?");
      using ScalarGetterResult = std::remove_cvref_t<std::invoke_result_t<ScalarGetter, const T&>>;
      static_assert(std::is_integral_v<ScalarGetterResult> && std::is_unsigned_v<ScalarGetterResult>,
                    "This type should be serialized as JsonDataType::UInt, but "
                    "JsonScalarGetter returns a value that isn't a unsigned integer.");
      writeUInt(static_cast<std::uintmax_t>(ScalarGetter{}(value)));
    }
    else if constexpr (kDataType == JsonDataType::String)
    {
      using ScalarGetter = JsonScalarGetter<std::remove_cvref_t<T>>;
      static_assert(std::is_invocable_v<ScalarGetter, const T&>,
                    "This type should be serialized as JsonDataType::String, but "
                    "JsonScalarGetter is not invokable for this type. Have you forgotten to specialize it?");
      using ScalarGetterResult = std::invoke_result_t<ScalarGetter, const T&>;
      static_assert(std::is_convertible_v<ScalarGetterResult, std::string_view>,
                    "This type should be serialized as JsonDataType::String, but "
                    "JsonScalarGetter returns a value that isn't convertible to std::string_view.");
      writeString(ScalarGetter{}(value));
    }
    else if constexpr (kDataType == JsonDataType::Array)
    {
      writeArray([](const ArrayElementsWriter& elements_writer, const void* value_ptr)
                  {
                    JsonArrayWriter<T>{}(elements_writer, *static_cast<const T*>(value_ptr));
                  },
                  std::addressof(value),
                  single_line);
    }
    else if constexpr (kDataType == JsonDataType::Object)
    {
      writeObject([](FieldsWriter& fields_writer, const void* value_ptr)
                  {
                    JsonObjectWriter<T>{}(fields_writer, *static_cast<const T*>(value_ptr));
                  },
                  static_cast<const void*>(std::addressof(value)),
                  single_line);
    }
    else
    {
      static_assert(false, "Invalid kJsonDataTypeFor<T>.");
    }
  }

  template<class T>
  void IJsonSerializer::writeArrayElement(const T& value, bool single_line)
  {
    beforeWriteElementOrField();
    writeValueRaw(value, single_line);
  }

  template<class T>
  void IJsonSerializer::writeField(std::string_view field_name, const T& value, bool single_line)
  {
    beforeWriteElementOrField();
    writeFieldName(field_name);
    writeValueRaw(value, single_line);
  }
}
