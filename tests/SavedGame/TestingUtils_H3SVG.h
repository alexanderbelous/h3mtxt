#pragma once

// Common utilities to reduce boilerplate in test cases.

#include "../Utils.h"

#include <h3mtxt/H3JsonReader/H3SVGJsonReader/H3SVGJsonReader.h>
#include <h3mtxt/H3JsonWriter/H3SVGJsonWriter/H3SVGJsonWriter.h>
#include <h3mtxt/H3Writer/H3SVGWriter/H3SVGWriter.h>
#include <h3mtxt/H3Reader/H3SVGReader/H3SVGReader.h>

#include <sstream>
#include <string>
#include <string_view>
#include <utility>

namespace Testing_NS
{
  // Encodes the given value via H3SVGWriter::writeData().
  // \param value - value to encode.
  // \return a string containing the bytes serialized for @value.
  template<class T>
  std::string encodeViaH3SVGWriter(const T& value)
  {
    std::ostringstream stream;
    h3svg::H3SVGWriter{ stream }.writeData(value);
    return std::move(stream).str();
  }

  // Adapter for H3SVGReader that reads the bytes from the given string.
  class H3SVGReaderAdapter : private IStringStreamWrapper,
                             public h3svg::H3SVGReader
  {
  public:
    // Constructs H3SVGReader that will consume bytes from the given string.
    // \param encoded_data - bytes that will be used to initialize the stream
    //        passed to the constructor of H3SVGReader.
    H3SVGReaderAdapter(std::string_view encoded_data) :
      IStringStreamWrapper{ encoded_data },
      H3SVGReader{ IStringStreamWrapper::stream }
    {}
  };
}
