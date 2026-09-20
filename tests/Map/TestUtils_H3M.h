#pragma once

// Common utilities to reduce boilerplate in test cases.

#include "../Utils.h"

#include <h3mtxt/H3JsonReader/H3MJsonReader/H3MJsonReader.h>
#include <h3mtxt/H3JsonWriter/H3MJsonWriter/H3MJsonWriter.h>
#include <h3mtxt/H3Writer/H3MWriter/H3MWriter.h>
#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>

#include <sstream>
#include <string>
#include <string_view>
#include <utility>

namespace Testing_NS
{
  // Encodes the given value via H3MWriter::writeData().
  // \param value - value to encode.
  // \return a string containing the bytes serialized for @value.
  template<class T>
  std::string encodeViaH3MWriter(const T& value)
  {
    std::ostringstream stream;
    h3m::H3MWriter{ stream }.writeData(value);
    return std::move(stream).str();
  }

  // Adapter for H3MReader that reads the bytes from the given string.
  class H3MReaderAdapter : private IStringStreamWrapper,
                           public h3m::H3MReader
  {
  public:
    // Constructs H3MReader that will consume bytes from the given string.
    // \param encoded_data - bytes that will be used to initialize the stream
    //        passed to the constructor of H3MReader.
    H3MReaderAdapter(std::string_view encoded_data) :
      IStringStreamWrapper{ encoded_data },
      H3MReader{ IStringStreamWrapper::stream }
    {}
  };
}
