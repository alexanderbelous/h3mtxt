#include <h3mtxt/H3MReader/parseh3m.h>

#include <h3mtxt/H3MReader/H3Reader.h>

#include <h3mtxt/thirdparty/zstr/src/zstr.hpp>

#include <istream>
#include <stdexcept>

namespace h3m::H3Reader_NS
{
  Map parseh3m(std::istream& stream)
  {
    constexpr char kGzipFirstByte = 0x1F;
    if (!stream)
    {
      throw std::runtime_error("parseh3m(): Bad istream.");
    }
    using Traits = std::istream::traits_type;
    // Check the first byte. If it's 0x1F, then it cannot be an uncompressed .h3m file,
    // so assume that it's a compressed one.
    const int first_byte = stream.peek();
    if (first_byte == Traits::eof())
    {
      throw std::runtime_error("parseh3m(): Empty stream passed.");
    }
    if (first_byte != kGzipFirstByte)
    {
      return readMap(stream);
    }
    else
    {
      zstr::istream zstr_stream(stream);
      return readMap(zstr_stream);
    }
  }
}
