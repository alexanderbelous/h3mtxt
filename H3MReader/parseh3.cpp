#include <h3mtxt/H3MReader/parseh3.h>
#include <h3mtxt/H3MReader/parseh3c.h>
#include <h3mtxt/H3MReader/parseh3m.h>

#include <h3mtxt/thirdparty/zstr/src/zstr.hpp>

namespace h3m
{
  namespace
  {
    std::variant<Map, Campaign> parseh3Uncompressed(std::istream& stream)
    {
      const int first_byte = stream.peek();
      switch (first_byte)
      {
      case static_cast<std::uint8_t>(h3m::MapFormat::RestorationOfErathia):
      case static_cast<std::uint8_t>(h3m::MapFormat::ArmageddonsBlade):
      case static_cast<std::uint8_t>(h3m::MapFormat::ShadowOfDeath):
        return h3m::parseh3m(stream);
      case static_cast<std::uint8_t>(h3m::CampaignFormat::RestorationOfErathia):
      case static_cast<std::uint8_t>(h3m::CampaignFormat::ArmageddonsBlade):
      case static_cast<std::uint8_t>(h3m::CampaignFormat::ShadowOfDeath):
        return h3m::parseh3c(stream);
      default:
        throw std::runtime_error("parseh3(): Unknown file format.");
      }
    }
  }

  std::variant<Map, Campaign> parseh3(std::istream& stream)
  {
    constexpr char kGzipFirstByte = 0x1F;
    if (!stream)
    {
      throw std::runtime_error("parseh3(): Bad istream.");
    }
    using Traits = std::istream::traits_type;
    const int first_byte = stream.peek();
    if (first_byte == Traits::eof())
    {
      throw std::runtime_error("parseh3(): Empty stream passed.");
    }
    if (first_byte != kGzipFirstByte)
    {
      return parseh3Uncompressed(stream);
    }
    else
    {
      zstr::istream zstr_stream(stream);
      return parseh3Uncompressed(zstr_stream);
    }
  }
}