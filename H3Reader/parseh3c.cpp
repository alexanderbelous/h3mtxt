#include <h3mtxt/H3Reader/parseh3c.h>

#include <h3mtxt/H3Reader/H3Reader.h>
#include <h3mtxt/H3Reader/Utils.h>
#include <h3mtxt/Campaign/Campaign.h>

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
    // Check that the stream starts with a gzip stream (containing CampaignHeader).
    const int first_byte = stream.peek();
    if (first_byte == Traits::eof())
    {
      throw std::runtime_error("parseh3c(): Empty stream passed.");
    }
    if (first_byte != kGzipFirstByte)
    {
      throw std::runtime_error("parseh3c(): Not a valid .h3c file.");
    }
    Campaign campaign;
    zstr::istream zstr_stream(stream);
    campaign.header = readCampaignHeader(zstr_stream);
    // TODO: add support for the case when one or more maps are not gzip-compressed.
    const std::size_t num_scenarios = countScenarios(campaign.header);
    campaign.maps.reserve(num_scenarios);
    for (std::size_t i = 0; i < num_scenarios; ++i)
    {
      campaign.maps.push_back(readMap(zstr_stream));
    }
    return campaign;
  }
}
