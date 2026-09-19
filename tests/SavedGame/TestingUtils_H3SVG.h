#pragma once

// Common utilities to reduce boilerplate in test cases.

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
  namespace Detail_NS
  {
    // Owns std::istringstream.
    // The derived classes can use it together with the Base-from-Member idiom
    // to initialize the underlying stream before passing it to the constructor of another base class.
    class IStringStreamWrapper
    {
    public:
      IStringStreamWrapper(std::string_view data):
        stream{ std::string{data} }
      {}

      std::istringstream stream;
    };
  }

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
  class H3SVGReaderAdapter : private Detail_NS::IStringStreamWrapper,
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
