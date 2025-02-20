#include <h3mtxt/H3MReader/parseh3c.h>

#include <h3mtxt/H3MReader/H3Reader.h>

#include <h3mtxt/thirdparty/zstr/src/zstr.hpp>

#include <istream>
#include <stdexcept>

namespace h3m::H3Reader_NS
{
  Campaign parseh3c(std::istream& stream)
  {
    constexpr char kGzipFirstByte = 0x1F;
    if (!stream)
    {
      throw std::runtime_error("parseh3c(): Bad istream.");
    }
    using Traits = std::istream::traits_type;
    // Check the first byte. If it's 0x1F, then it cannot be an uncompressed .h3c file,
    // so assume that it's a compressed one.
    const int first_byte = stream.peek();
    if (first_byte == Traits::eof())
    {
      throw std::runtime_error("parseh3c(): Empty stream passed.");
    }
    if (first_byte != kGzipFirstByte)
    {
      return readCampaign(stream);
    }
    else
    {
      zstr::istream zstr_stream(stream);
      return readCampaign(zstr_stream);
    }
  }
}
