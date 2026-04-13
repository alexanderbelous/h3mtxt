#pragma once

#include <h3mtxt/H3JsonReader/H3JsonReaderBase/H3JsonReaderBase.h>
#include <h3mtxt/H3JsonReader/H3JsonReaderBase/Utils.h>
#include <h3mtxt/Medea/Medea.h>

#include <cstddef>
#include <span>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace Testing_NS
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
    return h3json::fromJsonString<T>(writeH3JsonAsString(value));
  }

  // Converts the input string to an array of bytes.
  //
  // Catch2 sometimes has issues when printing binary strings
  // (see https://github.com/catchorg/Catch2/issues/2960).
  // Until the issue is resolved, this workaround can be used.
  //
  // \param data - input string.
  // \return std::vector<std::byte> whose elements are equal to the elements of @data.
  inline std::vector<std::byte> asByteVector(std::string_view data)
  {
    const std::span<const std::byte> bytes = std::as_bytes(std::span<const char>(data));
    return std::vector<std::byte>{bytes.begin(), bytes.end()};
  }
}
