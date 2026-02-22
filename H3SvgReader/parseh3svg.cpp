#include <h3mtxt/H3SvgReader/parseh3svg.h>

#include <h3mtxt/H3SvgReader/H3SvgReader.h>

#include <h3mtxt/thirdparty/zstr/src/zstr.hpp>

#include <istream>
#include <stdexcept>

namespace h3m::H3SvgReader_NS
{
  SavedGame parseh3svg(std::istream& stream)
  {
    constexpr char kGzipFirstByte = 0x1F;
    if (!stream)
    {
      throw std::runtime_error("parseh3svg(): Bad istream.");
    }
    using Traits = std::istream::traits_type;
    // Check the first byte. If it's 0x1F, then it cannot be an uncompressed .h3m file,
    // so assume that it's a compressed one.
    const int first_byte = stream.peek();
    if (first_byte == Traits::eof())
    {
      throw std::runtime_error("parseh3svg(): Empty stream passed.");
    }
    if (first_byte != kGzipFirstByte)
    {
      return readSavedGame(stream);
    }
    else
    {
      zstr::istream zstr_stream(stream);
      return readSavedGame(zstr_stream);
    }
  }
}
