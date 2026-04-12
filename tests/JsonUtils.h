#pragma once

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/Utils.h>
#include <h3mtxt/Medea/Medea.h>

#include <sstream>
#include <string>

namespace h3json
{
  // Serializes the input value as JSON.
  // \param value - input value.
  // \return std::string storing a JSON value that represents @value.
  template<class T>
  std::string writeH3JsonAsString(const T& value)
  {
    std::ostringstream stream;
    Medea_NS::writeJson(stream, value);
    return std::move(stream).str();
  }

  // Performs a round-trip conversion to JSON and then back.
  // \param value - input object of type T.
  // \return the value deserialized via h3json::JsonReader<T> from the string
  //         produced by Medea_NS::writeJson<T>().
  template<class T>
  T encodeAndDecodeJson(const T& value)
  {
    return fromJsonString<T>(writeH3JsonAsString(value));
  }
}
