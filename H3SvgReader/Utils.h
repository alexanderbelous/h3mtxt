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

  // Reads a string from the stream.
  // The string is deserialized as a null-terminated string:
  // bytes are read until a byte with the value 0x00 is encountered.
  // TODO: remove. This doesn't seem to be needed anywhere.
  std::string readStringNullTerminated(std::istream& stream);
}
