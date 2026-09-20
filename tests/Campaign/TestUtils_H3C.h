#pragma once

// Common utilities to reduce boilerplate in test cases.

#include "../Utils.h"

#include <h3mtxt/H3JsonReader/H3CJsonReader/H3CJsonReader.h>
#include <h3mtxt/H3JsonWriter/H3CJsonWriter/H3CJsonWriter.h>
#include <h3mtxt/H3Writer/H3CWriter/H3CWriter.h>
#include <h3mtxt/H3Reader/H3CReader/H3CReader.h>

#include <sstream>
#include <string>
#include <string_view>
#include <utility>

namespace Testing_NS
{
  // Encodes the given value via H3MCriter::writeData().
  // \param value - value to encode.
  // \return a string containing the bytes serialized for @value.
  template<class T>
  std::string encodeViaH3CWriter(const T& value)
  {
    std::ostringstream stream;
    h3m::H3CWriter{ stream }.writeData(value);
    return std::move(stream).str();
  }

  // Adapter for H3CReader that reads the bytes from the given string.
  class H3CReaderAdapter : private IStringStreamWrapper,
                           public h3m::H3CReader
  {
  public:
    // Constructs H3CReader that will consume bytes from the given string.
    // \param encoded_data - bytes that will be used to initialize the stream
    //        passed to the constructor of H3CReader.
    H3CReaderAdapter(std::string_view encoded_data) :
      IStringStreamWrapper{ encoded_data },
      H3CReader{ IStringStreamWrapper::stream }
    {}
  };
}
