#pragma once

#include <iosfwd>
#include <string>

namespace h3m::H3SvgReader_NS
{
  // Reads a string from the stream.
  // The string is deserialized as a Pascal string:
  // first, the string length N is decoded as as a 16-bit little-endian integer,
  // followed by N bytes representing the characters.
  std::string readString16(std::istream& stream);
}
