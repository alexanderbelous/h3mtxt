#pragma once

#include <json/forwards.h>

// API for deserializing H3 data from JSON.
namespace h3json
{
  // Template class for deserializing Json::Value as the specified type.
  template<class T, class Enable = void>
  struct JsonReader
  {
    // Deserializes a value of type T from the input JSON.
    // \param value - input JSON value.
    // \return @value deserialized as an object of type T.
    T operator()(const Json::Value& value) const;
  };
}
