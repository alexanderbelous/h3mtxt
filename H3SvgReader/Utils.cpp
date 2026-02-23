#include <h3mtxt/H3SvgReader/Utils.h>
#include <h3mtxt/H3Reader/Utils.h>

#include <cstdint>

namespace h3m::H3SvgReader_NS
{
  std::string readString16(std::istream& stream)
  {
    const std::uint16_t length = H3Reader_NS::readInt<std::uint16_t>(stream);
    std::string result;
    result.resize(length);
    H3Reader_NS::Detail_NS::readByteArrayImpl(stream, std::as_writable_bytes(std::span{ result }));
    return result;
  }

  std::string readStringNullTerminated(std::istream& stream)
  {
    std::string result;
    while (true)
    {
      const std::byte c = h3m::H3Reader_NS::Detail_NS::readByte(stream);
      if (c == std::byte{ 0 })
      {
        break;
      }
      result.push_back(static_cast<char>(c));
    }
    return result;
  }
}
