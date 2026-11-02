#pragma once

#include <json/forwards.h>

#include <string_view>

// API for deserializing H3 data from JSON.
namespace h3json
{
  // ============================================================
  // Old API.
  //
  // The old API will be removed in the future, and JsonReader2 will be renamed
  // to JsonReader. For now, both the old and the new API can be used.
  // ============================================================

  // Template class for deserializing Json::Value as the specified type.
  template<class T, class Enable = void>
  struct JsonReader
  {
    // Deserializes a value of type T from the input JSON.
    // The default implementation delegates to JsonReader2<T>.
    // \param value - input JSON value.
    // \return @value deserialized as an object of type T.
    T operator()(const Json::Value& value) const;
  };

  // Utility function for deserializing Json::Value as the specified type.
  //
  // This intentionally delegates to the old API for backward compatibility.
  // \param value - input Json::Value.
  // \return JsonReader<T>{}(value)
  template<class T>
  T fromJson(const Json::Value& value);

  // ============================================================
  // New API.
  // ============================================================

  // Non-template base class for JsonReader2<T>.
  //
  // Moving the common API to a base class allows reusing it when defining
  // partial specializations of JsonReader2.
  class JsonReader2Base
  {
  public:
    // Constructs a JsonObjectReaderBase that will read fields from the given Json::Value.
    // \param value - Json::Value to read the fields from.
    explicit constexpr JsonReader2Base(const Json::Value& value) noexcept;

    // \return the referenced Json::Value.
    constexpr const Json::Value& value() const noexcept;

    // Returns the value of the specified member.
    // \param field_name - name of the member to access.
    // \return the member @field_name of this->value(), or NULL if there is no such member.
    const Json::Value& getField(std::string_view field_name) const;

    // Same as
    //   fromJson<U>(getField(field_name));
    template<class U>
    U readField(std::string_view field_name) const;

    // Same as
    //   dest = readField<U>(field_name);
    template<class U>
    void readField(std::string_view field_name, U& dest) const;

  private:
    const Json::Value& value_;
  };

  // Class template for deserializing Json::Value as the specified type.
  //
  // Unlike JsonReader, this class aggregates a reference to the input Json::Value,
  // reducing boilerplate when calling readField() or getField().
  //
  // Most of the time, the user only needs to specialize operator() (which is deleted
  // by default). However, for partial specializations the user must specialize the
  // entire class, deriving the specialization from JsonReader2Base.
  template<class T, class Enable = void>
  struct JsonReader2 : JsonReader2Base
  {
    // Inherit the constructor from JsonReader2Base.
    using JsonReader2Base::JsonReader2Base;

    // Deserializes a value of type T from the input JSON.
    // \return this->value() deserialized as an object of type T.
    T operator()() const = delete;
  };

  template<class T, class Enable>
  T JsonReader<T, Enable>::operator()(const Json::Value& value) const
  {
    return JsonReader2<T>{ value }();
  }

  template<class T>
  T fromJson(const Json::Value& value)
  {
    return JsonReader<T>{}(value);
  }

  constexpr JsonReader2Base::JsonReader2Base(const Json::Value& value) noexcept :
    value_{ value }
  {}

  constexpr const Json::Value& JsonReader2Base::value() const noexcept
  {
    return value_;
  }

  template<class U>
  U JsonReader2Base::readField(std::string_view field_name) const
  {
    return fromJson<U>(getField(field_name));
  }

  template<class U>
  void JsonReader2Base::readField(std::string_view field_name, U& dest) const
  {
    dest = readField<U>(field_name);
  }
}
