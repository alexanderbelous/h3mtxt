#pragma once

#include <json/forwards.h>

// API for deserializing H3 data from JSON.
namespace h3m::H3JsonReader_NS
{
  // Template class for deserializing Json::Value as the specified type.
  template<class T, class Enable = void>
  struct JsonReader
  {
    // \param value - input JSON value.
    // \return @value deserialized as an object of type T.
    T operator()(const Json::Value& value) const;
  };
}
