#include <h3mtxt/H3SvgReader/Utils.h>
#include <h3mtxt/H3Reader/Utils.h>

#include <cstdint>

namespace h3m::H3SvgReader_NS
{
  std::string readString(std::istream& stream)
  {
    const std::uint16_t length = H3Reader_NS::readInt<std::uint16_t>(stream);
    std::string result;
    result.resize(length);
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::as_writable_bytes(std::span{ result }));
    return result;
  }
}
