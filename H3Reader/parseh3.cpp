#include <h3mtxt/H3Reader/parseh3.h>

#include <h3mtxt/H3Reader/H3CReader/H3CReader.h>
#include <h3mtxt/H3Reader/H3MReader/H3MReader.h>

#include <h3mtxt/thirdparty/zstr/src/zstr.hpp>

namespace h3m
{
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
    // If @stream doesn't start with a gzip stream, then it cannot be a *.h3c file.
    switch (first_byte)
    {
    case static_cast<std::uint8_t>(MapFormat::RestorationOfErathia):
    case static_cast<std::uint8_t>(MapFormat::ArmageddonsBlade):
    case static_cast<std::uint8_t>(MapFormat::ShadowOfDeath):
      return H3MReader{ stream }.readMap();
    case kGzipFirstByte:
      break;
    default:
      throw std::runtime_error("parseh3(): Unknown file format.");
    }
    // OK, the stream starts with a gzip stream.
    zstr::istream zstr_stream(stream);
    const int first_decompressed_byte = zstr_stream.peek();
    switch (first_decompressed_byte)
    {
    case static_cast<std::uint8_t>(MapFormat::RestorationOfErathia):
    case static_cast<std::uint8_t>(MapFormat::ArmageddonsBlade):
    case static_cast<std::uint8_t>(MapFormat::ShadowOfDeath):
      return H3MReader{ zstr_stream }.readMap();
    case static_cast<std::uint8_t>(CampaignFormat::RestorationOfErathia):
    case static_cast<std::uint8_t>(CampaignFormat::ArmageddonsBlade):
    case static_cast<std::uint8_t>(CampaignFormat::ShadowOfDeath):
    {
      Campaign campaign{ .header = H3CReader{zstr_stream}.readCampaignHeader() };
      const std::size_t num_scenarios = countScenarios(campaign.header);
      campaign.maps.reserve(num_scenarios);
      for (std::size_t i = 0; i < num_scenarios; ++i)
      {
        // TODO: add support for the case when one or more maps are not gzip-compressed.
        campaign.maps.push_back(H3MReader{ zstr_stream }.readMap());
      }
      return campaign;
    }
    default:
      throw std::runtime_error("parseh3(): Unknown file format.");
    }
  }
}
