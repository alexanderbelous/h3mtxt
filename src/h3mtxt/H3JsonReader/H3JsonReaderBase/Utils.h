#pragma once

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBaseFwd.h>

#include <json/json.h>

#include <iosfwd>
#include <string_view>

namespace h3json
{
  // Reads Json::Value from the specified stream.
  // \param stream - input stream.
  // \return Json::Value deserialized from @stream.
  Json::Value parseJsonFromStream(std::istream& stream);

  // Reads Json::Value from the specified string.
  // \param str - input string.
  // \return Json::Value deserialized from @str.
  Json::Value parseJsonFromString(std::string_view str);

  // Deserializes an object of type T from a JSON string loaded from the specified stream.
  // \param stream - input stream.
  // \return fromJson<T>(parseJsonFromStream(stream)).
  template<class T>
  T fromJsonStream(std::istream& stream)
  {
    return fromJson<T>(parseJsonFromStream(stream));
  }

  // Deserializes an object of type T from a JSON string loaded from the specified string.
  // \param str - input string.
  // \return fromJson<T>(parseJsonFromString(stream)).
  template<class T>
  T fromJsonString(std::string_view str)
  {
    return fromJson<T>(parseJsonFromString(str));
  }
}
