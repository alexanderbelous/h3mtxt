#include <h3mtxt/H3MReader/parseh3c.h>

#include <h3mtxt/H3MReader/readCampaignScenario.h>
#include <h3mtxt/H3MReader/parseh3m.h>
#include <h3mtxt/H3MReader/Utils.h>

#include <h3mtxt/thirdparty/zstr/src/zstr.hpp>

#include <istream>
#include <stdexcept>

namespace h3m
{
  namespace
  {
    Campaign parseh3cUncompressed(std::istream& stream)
    {
      Campaign campaign;
      campaign.format = readEnum<CampaignFormat>(stream);
      campaign.id = readEnum<CampaignId>(stream);
      campaign.name = readString(stream);
      campaign.description = readString(stream);
      campaign.allow_selecting_difficulty = readBool(stream);
      campaign.theme_music = readEnum<CampaignMusic>(stream);
      const std::uint8_t max_num_scenarios = countMapRegions(campaign.id);
      campaign.scenarios.reserve(max_num_scenarios);
      for (std::uint8_t i = 0; i < max_num_scenarios; ++i)
      {
        campaign.scenarios.push_back(readCampaignScenario(stream, campaign.id));
      }
      const std::size_t num_scenarios = countScenarios(campaign);
      campaign.maps.reserve(num_scenarios);
      for (std::size_t i = 0; i < num_scenarios; ++i)
      {
        campaign.maps.push_back(parseh3m(stream));
      }
      return campaign;
    }
  }

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
      return parseh3cUncompressed(stream);
    }
    else
    {
      zstr::istream zstr_stream(stream);
      return parseh3cUncompressed(zstr_stream);
    }
  }
}
