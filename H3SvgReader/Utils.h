#pragma once

#include <iosfwd>
#include <string>

namespace h3m::H3SvgReader_NS
{
  // Reads a string from the stream.
  // Strings in saved games are always written as Pascal strings: the string length N is
  // written as uint16, followed by N bytes.
  std::string readString16(std::istream& stream);
}
